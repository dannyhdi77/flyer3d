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
#include <math.h>
#include <default_game_renderer_settings.h>
#include <body_t.h>
#include <aircraft_t.h>
#include <camera_t.h>
#include <segment_t.h>
#include <pipe_t.h>
#include <printw.h>

#define ANGLE_STEP 0.005
#define FSPEED -0.1
#define POINT_WAIT 100

#define SPEED_STEP 0.1
#define SPEED_WAIT 1000

typedef struct{
	renderer_t renderer;	//renderer for game graphics
	game_system_t *system;	//for state changes, etc.gs


	aircraft_t player;
	model_t* player_model;

	segment_t seg;
	pipe_t pipe;

	camera_t camera;
	body_t teren;
	light_t light;	//something to illuminate the scene

	int score;
} game_t;

//initalizes game
int game_init(game_t *, game_system_t*);

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
