/*
 * menu_t.h
 *
 *  Created on: 2010-05-17
 *      Author: krzychu
 */

#ifndef MENU_T_H_
#define MENU_T_H_

#include <game_system_t.h>
#include <load_texture.h>
#include <body_t.h>
#include <SDL/SDL.h>
#include <renderer_t.h>
#include <math.h>
#include <aircraft_t.h>
#include <light_t.h>

#define PI2 6.28

#define MENU_MAX_FILENAME 100
#define MENU_RADIUS 1.0
#define MENU_ROTATION_SPEED 0.005
#define MENU_BASE_HEIGHT 0.2

typedef struct {
	body_t obj;		//physical representation of item
	struct menu_s* parent;
	int texture;	//texture index, set by menu_init
	char image_file_name[MENU_MAX_FILENAME];	//guess what
	int w,h;	//width and height of menu image
} menu_item_t;

struct menu_s {
	body_t obj;	//as above
	body_t camera;
	game_system_t *system;
	menu_item_t *items;	//item table, allocated later
	int n_items;	//how many items do we have
	int textures[10];
	int index;	//index of active element

	float rotation; //we store menu rotation in radians, becouse frame doesn't provide such information
	aircraft_t skull;
	model_t* skull_model;
	light_t light;
};

typedef struct menu_s menu_t;

//before initiation, menu should be created using relevant create function
void menu_init(menu_t*, game_system_t*);

void menu_refresh(menu_t*, float time);

void menu_react(menu_t*, SDL_Event*);

void menu_render(menu_t*);


void menu_item_init(menu_item_t*);

void menu_item_render(menu_item_t*);

void menu_delete(menu_t*);

#endif /* MENU_T_H_ */
