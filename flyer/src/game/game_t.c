/*
 * game_t.c
 *
 *  Created on: 2010-04-02
 *      Author: krzychu
 */
#include "game_t.h"

//initalizes game
int game_init(game_t *g){
	//initalize game renderer
	renderer_init(&g->renderer);
	default_game_renderer_settings(&g->renderer);
	renderer_reload(&g->renderer);

	//haha
	g->angle_step_x = 0.0;
	g->angle_step_y = 0.0;

	g->model.type = DISP_MODEL;
	d_object_init(&g->model,model_load("data/StarCruiser.obj"));
	g->model.position[2] = -10.0;

//	float color[] = {1.0, 1.0, 1.0, 1.0};
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
/*	float position[] = {10.0, 10.0, 0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
*/

	//turn on the light
	vector3_t pos = {0.0, 10.0, 0.0};
	light_set_index(&g->light, 0);
	light_set_position(&g->light, pos);
	color_t col = {1.0, 1.0, 1.0};
	light_set_color(&g->light,col);
	light_on(&g->light);


	return 0;
}

//deletes game structure
void game_delete(game_t* g){
	renderer_delete(&g->renderer);
}

//displays game content on screen
void game_render(game_t* g){
	renderer_start(&g->renderer);
	renderer_display(&g->renderer,&g->model);
	renderer_finish(&g->renderer);
}

//react on event
void game_react(game_t* g, SDL_Event *ev){
	if(ev->type == SDL_VIDEORESIZE){
		renderer_resize(&g->renderer,ev->resize.w, ev->resize.h);
		renderer_reload(&g->renderer);
	}
	else if(ev->type == SDL_JOYAXISMOTION){
		if(ev->jaxis.axis == 3){
			if(ev->jaxis.value != 0 ){
				if(ev->jaxis.value < 0)
					g->angle_step_x = -ANGLE_STEP;
				else
					g->angle_step_x = ANGLE_STEP;
			}
			else{
				g->angle_step_x = 0.0;
			}
		}
		else if(ev->jaxis.axis == 4){
			if(ev->jaxis.value != 0 ){
				if(ev->jaxis.value < 0)
					g->angle_step_y = ANGLE_STEP;
				else
					g->angle_step_y = -ANGLE_STEP;
			}
			else{
				g->angle_step_y = 0.0;
			}
		}
	}
}

//refreshes game content, physics is done here
//last parameter is time from start of app
void game_refresh(game_t* g, int t){
	g->model.x_angle += g->angle_step_x;
	g->model.y_angle += g->angle_step_y;
}
