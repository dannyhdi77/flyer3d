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
	body_init(&m->camera);
	m->system = sys;
}

void menu_refresh(menu_t* m, float time){

}

void menu_react(menu_t* m, SDL_Event* e){

}

void menu_render(menu_t* m){
	renderer_set_camera(&m->system->renderer, &m->camera);
	renderer_start(&m->system->renderer);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
		glVertex3f(0.0,0.0, -10.0);
		glVertex3f(0.0,-1.0, 0.0);
	glEnd();
	renderer_finish(&m->system->renderer);
}


void menu_item_init(menu_item_t*);

void menu_item_refresh(menu_item_t*, float time);

void menu_item_react(menu_item_t*, SDL_Event*);

void menu_item_render(menu_item_t*);
