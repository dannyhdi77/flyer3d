/*
 * game_system_t.h
 *
 *  Created on: 2010-04-02
 *      Author: krzychu
 */

#ifndef GAME_SYSTEM_T_H_
#define GAME_SYSTEM_T_H_

#include <SDL/SDL.h>
#include <stdio.h>
#include <messages.h>
#include <stdlib.h>
#include <time.h>

#include <renderer_t.h>
#include <default_game_renderer_settings.h>

//state of game definitions
#define STATE_GAME 0
#define STATE_MAIN_MENU 1
#define STATE_INTRO 2
#define STATE_BEST_SCORE 3
#define STATE_DEATH 5
#define STATE_QUIT 4

//general game system data
typedef struct{
	char state; //state of game

	char n_joysticks; //number of avaliable joysticks

	renderer_t renderer;	//renderer for everything

	int score; //score to display after death

	int best_score; //best score so far
} game_system_t;

//initalizes game systems
int game_system_init(game_system_t*);

//exits game
void game_system_quit(game_system_t*);

//writes message to a log
void game_system_log(const char*);

//takes care of state changes , etc
void game_system_communicate(game_system_t*, int);


#endif /* GAME_SYSTEM_T_H_ */
