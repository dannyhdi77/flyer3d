/*
 * menu_t.c
 *
 *  Created on: 2010-05-17
 *      Author: krzychu
 */

#include <menu_t.h>

void menu_init(menu_t* m, game_system_t* sys){
	m->index = 0;

	body_init(&m->obj);
	m->rotation = 0.0;

	body_init(&m->camera);
	body_rotate(&m->camera,B_UP, 0.1);
	body_move_forward(&m->camera, 4.0);
	m->camera.position[1] = 0.5;
	m->system = sys;


	light_set_index(&m->light, 0);
	vector3_t pos = {0.0, 10.0, 0.0};
	light_set_position(&m->light, pos);
	color_t col = {1.0, 1.0, 1.0};
	light_set_color(&m->light,col);
	light_on(&m->light);


	float angle_step = PI2/((float)m->n_items);
	float angle = 0.0;

	int i;
	for(i = 0; i<m->n_items; i++){
		menu_item_init(&m->items[i]);
		m->items[i].h = 100;
		m->items[i].w = 300;
		body_rotate(&(m->items[i].obj), B_UP, angle);
		body_move_forward(&m->items[i].obj, MENU_RADIUS);
		angle += angle_step;
	}

	m->skull_model = model_load("data/skull.obj");
	aircraft_init(&m->skull, m->skull_model);
	m->skull.object.position[1] = 2.0;
	m->skull.fire.normal_direction = -1.0;
	vector3_set(m->skull.object.forward,0.0,0.0,-1.0);

	body_rotate(&m->skull.object,B_UP,-0.1);
}

void menu_refresh(menu_t* m, float time){
	body_do_kinematics(&m->obj, time);
	m->rotation += time*m->obj.up_v; //ugly but works
	if(m->rotation >= PI2/((float)m->n_items)){
		m->index ++;
		m->index %= m->n_items;
		m->rotation = 0.0;
		m->obj.up_v = 0.0;
	}
	else if(m->rotation <= -PI2/((float)m->n_items)){
		m->index --;
		if(m->index < 0)
			m->index += m->n_items;
		m->rotation = 0.0;
		m->obj.up_v = 0.0;
	}
	aircraft_refresh(&m->skull, time/100.0);
}

void menu_react(menu_t* m, SDL_Event* e){
	if(e->type == SDL_VIDEORESIZE){
		renderer_resize(&m->system->renderer,e->resize.w, e->resize.h);
		renderer_reload(&m->system->renderer);
	}
	else if(e->type == SDL_KEYDOWN){
		if(e->key.keysym.sym == SDLK_LEFT){
			m->obj.up_v = MENU_ROTATION_SPEED;
		}
		else if(e->key.keysym.sym == SDLK_RIGHT){
			m->obj.up_v = -MENU_ROTATION_SPEED;
		}

	}
}

#define SKULL_SCALE 0.3
void menu_render(menu_t* m){
	vector3_t pos = {0.0, 10.0, 0.0};
	light_set_position(&m->light, pos);

	renderer_set_camera(&m->system->renderer, &m->camera);
	renderer_start(&m->system->renderer);

	glPushMatrix();
	//apply menu transform
	body_apply_transform(&m->obj);

	//display all menu items
	int i;
	for(i=0; i<m->n_items ; i++){
		menu_item_render(&(m->items[i]));
	}
	glPopMatrix();
	//display skull
	glScalef(SKULL_SCALE,SKULL_SCALE,SKULL_SCALE);
	aircraft_display(&m->skull);

	renderer_finish(&m->system->renderer);
}


void menu_item_init(menu_item_t* item){
	body_init(&item->obj);
}


void menu_item_render(menu_item_t* item){
	float ratio = ((float)item->w)/((float)item->h);
	float dx = (MENU_BASE_HEIGHT*ratio)/2.0;
	float dy = MENU_BASE_HEIGHT/2.0;
	glPushMatrix();
	body_apply_transform(&item->obj);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);
		glVertex3f(-dx, -dy ,0.0);
		glVertex3f(-dx, dy ,0.0);
		glVertex3f( dx, dy ,0.0);
		glVertex3f( dx, -dy ,0.0);
/*
		glVertex3f(-dx, -dy ,0.1);
		glVertex3f(-dx, dy ,0.1);
		glVertex3f( dx, dy ,0.1);
		glVertex3f( dx, -dy ,0.1);*/
	glEnd();
	glPopMatrix();
}

void menu_delete(menu_t* m){
	model_delete(&m->skull_model);
	aircraft_delete(&m->skull);
}
