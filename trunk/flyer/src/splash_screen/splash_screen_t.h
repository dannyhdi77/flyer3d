/*
 * splash_screen_t.h
 *
 *  Created on: 2010-05-16
 *      Author: krzychu
 */

#ifndef SPLASH_SCREEN_T_H_
#define SPLASH_SCREEN_T_H_

#include <SDL/SDL.h>
#include <game_system_t.h>

#define SPLASH_FADE_STEP 0.0005
#define SPLASH_TIME 2000

#define SPLASH_FADEIN 0
#define SPLASH_WAIT 1
#define SPLASH_FADEOUT 2

typedef struct {
	SDL_Surface* image;	//image to display
	int state;
	float brightness;
	float life_time;
	game_system_t* system;
} splash_screen_t;

void splash_screen_init(splash_screen_t*, const char* filename, game_system_t* sys);

void splash_screen_delete(splash_screen_t*);

void splash_screen_react(splash_screen_t*, SDL_Event*);

void splash_screen_refresh(splash_screen_t* , float time);

void splash_screen_render(splash_screen_t*);

#endif /* SPLASH_SCREEN_T_H_ */
