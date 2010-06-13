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
#include <score_screen_t.h>

//command line parameters definition
#define SHOWFPS 0
#define NOACTION 1
#define HELP 2

int main(int argc, char** argv){
	//parse command line arguments
	int i;
	char params[4] = {0,0,0,0};
	for(i=1; i<argc; i++){
		if(strcmp("help",argv[i]) == 0){
			params[HELP] = 1;
		}
		else if(strcmp("noaction",argv[i]) == 0){
			params[NOACTION] = 1;
		}
		else if(strcmp("showfps",argv[i]) == 0){
			params[SHOWFPS] = 1;
		}
	}

	if(params[HELP]){
		printf("Czerep \n\n opcje linii komend:\n noaction - nic nie jest renderowane\n showfps - pokazuje fps");
		return 0;
	}


	//initalize glut library, which provides
	//function for text display
	glutInit(&argc, argv);

	//general game system initalization
	game_system_t system;
	game_system_init(&system);

	//initalize game
	game_t game;
	game_init(&game, &system);

	//create intro splash screen
	splash_screen_t intro;
	splash_screen_init(&intro, "data/czerep.bmp" ,&system);

	//create main menu
	menu_t main_menu;
	main_menu_create(&main_menu);	//load menu data
	menu_init(&main_menu, &system);

	//create death and score screeens
	score_screen_t death_screen, best_screen;
	score_screen_init(&death_screen,"data/koniec_gry.bmp" ,&system);
	score_screen_init(&best_screen,"data/najlepszy_wynik.bmp" ,&system);

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

					case STATE_INTRO:
						splash_screen_react(&intro, &ev);
					break;

					case STATE_MAIN_MENU:
						menu_react(&main_menu, &ev);
					break;

					case STATE_BEST_SCORE:
						score_screen_react(&best_screen, &ev);
					break;

					case STATE_DEATH:
						score_screen_react(&death_screen, &ev);
					break;
				}
			}
		}

		if(!params[NOACTION])
		switch(system.state){
			case STATE_GAME:
				game_refresh(&game, SDL_GetTicks() - last_refresh_time);
				last_refresh_time = SDL_GetTicks();
				game_render(&game);
			break;

			case STATE_INTRO:
				splash_screen_refresh(&intro, SDL_GetTicks() - last_refresh_time);
				last_refresh_time = SDL_GetTicks();
				splash_screen_render(&intro);
			break;

			case STATE_MAIN_MENU:
				menu_refresh(&main_menu, SDL_GetTicks() - last_refresh_time);
				last_refresh_time = SDL_GetTicks();
				menu_render(&main_menu);
			break;

			case STATE_DEATH:
				score_screen_refresh(&death_screen, SDL_GetTicks() - last_refresh_time, system.score);
				last_refresh_time = SDL_GetTicks();
				score_screen_render(&death_screen);
			break;

			case STATE_BEST_SCORE:
				score_screen_refresh(&best_screen, SDL_GetTicks() - last_refresh_time, system.best_score);
				last_refresh_time = SDL_GetTicks();
				score_screen_render(&best_screen);
			break;
		}



		//calculate fps
		if(params[SHOWFPS]){
			nframes++;
			if(SDL_GetTicks() - last_fps >= 1000){
				printf("fps: %f\n", ((float)nframes));
				nframes = 0;
				last_fps = SDL_GetTicks();
			}
		}
	}

	//finish section
	game_delete(&game);
	splash_screen_delete(&intro);
	menu_delete(&main_menu);
	score_screen_delete(&best_screen);
	score_screen_delete(&death_screen);
	game_system_quit(NULL);

}
