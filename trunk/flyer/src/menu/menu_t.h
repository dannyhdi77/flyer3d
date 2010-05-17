/*
 * menu_t.h
 *
 *  Created on: 2010-05-17
 *      Author: krzychu
 */

#ifndef MENU_T_H_
#define MENU_T_H_

#include <game_system_t.h>
#include <body_t.h>
#include <SDL/SDL.h>
#include <renderer_t.h>

#define MENU_MAX_FILENAME 100
#define MENU_RADIUS 1.0

typedef struct {
	body_t obj;		//physical representation of item
	struct menu_s* parent;
	int texture;	//texture index, set by menu_init
	char image_file_name[MENU_MAX_FILENAME];	//guess what
	int w,h;	//width and height of manu image
} menu_item_t;

struct menu_s {
	body_t obj;	//as above
	body_t camera;
	game_system_t *system;
	menu_item_t *items;	//item table, allocated later
	int n_items;	//how many items do we have
	int index;	//index of active element
};

typedef struct menu_s menu_t;

//before initiation, menu should be created using relevant create function
void menu_init(menu_t*, game_system_t*);

void menu_refresh(menu_t*, float time);

void menu_react(menu_t*, SDL_Event*);

void menu_render(menu_t*);


void menu_item_init(menu_item_t*);

void menu_item_refresh(menu_item_t*, float time);

void menu_item_react(menu_item_t*, SDL_Event*);

void menu_item_render(menu_item_t*);


#endif /* MENU_T_H_ */
