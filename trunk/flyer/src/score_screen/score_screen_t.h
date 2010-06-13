/*
 * splash_screen_t.h
 *
 *  Created on: 2010-05-16
 *      Author: krzychu
 */

#ifndef SCORE_SCREEN_T_H_
#define SCORE_SCREEN_T_H_

#include <SDL/SDL.h>
#include <game_system_t.h>
#include <printw.h>
#include <math.h>

typedef struct {
	SDL_Surface* image;	//image to display
	int score;	//number to display
	game_system_t* system;
} score_screen_t;

void score_screen_init(score_screen_t*, const char* filename, game_system_t* sys);

void score_screen_delete(score_screen_t*);

void score_screen_react(score_screen_t*, SDL_Event*);

void score_screen_refresh(score_screen_t* , float time, int score);

void score_screen_render(score_screen_t*);

#endif /* score_SCREEN_T_H_ */
