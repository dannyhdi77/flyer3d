/*
 * game_t.h
 *
 *  Created on: 2010-04-02
 *      Author: krzychu
 */

#ifndef GAME_T_H_
#define GAME_T_H_

#include <renderer_t.h>
#include <game_system_t.h>
#include <model_t.h>
#include <displayable_object_t.h>
#include <math.h>
#include <default_game_renderer_settings.h>
#include <body_t.h>
#include <aircraft_t.h>

#define ANGLE_STEP 0.005
#define FSPEED -0.1

typedef struct{
	renderer_t renderer;	//renderer for game graphics
	game_system_t *system;	//for state changes, etc.
//	control_handler_t control;	//key bindings

	float angle_step_x ;
	float angle_step_y ;
	float fspeed ;

	aircraft_t player;
	model_t* player_model;

	body_t terrain;
	body_t camera;
	light_t light;	//something to illuminate the scene
} game_t;

//initalizes game
int game_init(game_t *);

//guess what
void game_delete(game_t *);

//refreshes game content, physics is done here
//last parameter is time from start of app
void game_refresh(game_t*, int);

//react on event
void game_react(game_t*, SDL_Event *);

//displays game content on screen
void game_render(game_t*);

#endif /* GAME_T_H_ */
