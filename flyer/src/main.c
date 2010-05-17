#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>

#include <game_system_t.h>
#include <game_t.h>
#include <splash_screen_t.h>
#include <main_menu_create.h>
#include <menu_t.h>
#include <utilties.h>

int main(){

	//general game system initalization
	game_system_t system;
	game_system_init(&system);

	//initalize game
	game_t game;
	game_init(&game, &system);

	//create intro splash screen
	splash_screen_t intro;
	splash_screen_init(&intro, "data/pi.bmp" ,&system);

	//create main menu
	menu_t main_menu;
	main_menu_create(&main_menu);	//load menu data
	menu_init(&main_menu, &system);

	//main loop
	SDL_Event ev;
	int last_refresh_time = SDL_GetTicks();
	int last_fps = SDL_GetTicks();
	int nframes = 0;
	while(system.state != STATE_QUIT){
		while(SDL_PollEvent(&ev)){
			if(ev.type == SDL_QUIT){
				game_system_quit(NULL);
			}
			else{
				switch(system.state){
					case STATE_GAME:
						game_react(&game, &ev);
					break;

					case STATE_SPLASH_SCREEN:
						splash_screen_react(&intro, &ev);
					break;

					case STATE_MAIN_MENU:
						menu_react(&main_menu, &ev);
					break;
				}
			}
		}

		switch(system.state){
			case STATE_GAME:
				game_refresh(&game, SDL_GetTicks() - last_refresh_time);
				last_refresh_time = SDL_GetTicks();
				game_render(&game);
			break;

			case STATE_SPLASH_SCREEN:
				splash_screen_refresh(&intro, SDL_GetTicks() - last_refresh_time);
				last_refresh_time = SDL_GetTicks();
				splash_screen_render(&intro);
			break;

			case STATE_MAIN_MENU:
				menu_refresh(&main_menu, SDL_GetTicks() - last_refresh_time);
				last_refresh_time = SDL_GetTicks();
				menu_render(&main_menu);
			break;
		}



		//calculate fps
		nframes++;
		if(SDL_GetTicks() - last_fps >= 1000){
			printf("fps: %f\n", ((float)nframes));
			nframes = 0;
			last_fps = SDL_GetTicks();
		}
	}

	//finish section
	game_system_quit(NULL);

}
