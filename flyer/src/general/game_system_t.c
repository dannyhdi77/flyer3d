/*
 * game_system_t.c
 *
 *  Created on: 2010-04-02
 *      Author: krzychu
 */
#include "game_system_t.h"

//initalizes all game systems
int game_system_init(game_system_t* sys){
	//initalization
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0){
		printf(M_SDL_INIT_ERROR);
		exit(0);
	}

	//depth and color buffer properities
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	//joystick initalization
	if(SDL_NumJoysticks() < 1){
		printf("No joysticks found\n");
	}

	SDL_Joystick *joy = SDL_JoystickOpen(0);
	if(joy != NULL){
		printf("Opened Joystick 0\n");
		printf("Name: %s\n", SDL_JoystickName(0));
		printf("Number of Axes: %d\n", SDL_JoystickNumAxes(0));
		printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
		printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
	}

	//init random number generator
	srand(time(0));

	//renderer
	renderer_init(&sys->renderer);
	default_game_renderer_settings(&sys->renderer);	//load default settings
	renderer_reload(&sys->renderer);

	//set inital state
	sys->state = STATE_MAIN_MENU;

	sys->score = 0;
	return 0;
}

//exits game
void game_system_quit(game_system_t* sys){
	//delete renderer
	renderer_delete(&sys->renderer);
	SDL_Quit();
	exit(0);
}

//writes message to log
void game_system_log(const char* message){
	printf("%s\n", message);
}

void game_system_communicate(game_system_t* s, int n){
	if(s->state == STATE_INTRO){
		printf("switching to MENU\n");
		s->state = STATE_MAIN_MENU;
	}
	else if(s->state == STATE_MAIN_MENU){
		printf("%d\n",n);
		switch(n){
			case 1:
				s->state = STATE_QUIT;
				break;
			case 0:
				s->state = STATE_GAME;
				break;
			case 3:
				s->state = STATE_GAME;
				break;
			case 2:
				s->state = STATE_GAME;
				break;
		}
		//s->state = STATE_GAME;
	}
	else if(s->state == STATE_GAME){
		if(n == 0){
			s->state = STATE_MAIN_MENU;
		}
	}
}

//returns current score
int game_system_score(game_system_t* s){
	return s->score;
}

//adds x to score
void game_system_score_add(game_system_t* s, int x){
	s->score += x;
}
