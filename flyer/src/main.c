#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>

#include <game_system_t.h>
#include <game_t.h>
#include <utilties.h>

int main(){

	//general game system initalization
	game_system_t system;
	game_system_init(&system);

	//initalize game
	game_t game;
	game_init(&game, &system);

	//main loop
	SDL_Event ev;
	int last_refresh_time = SDL_GetTicks();
	int last_fps = SDL_GetTicks();
	int nframes = 0;
	while(1){
		while(SDL_PollEvent(&ev)){
			if(ev.type == SDL_QUIT){
				game_system_quit(NULL);
			}
			else{
				game_react(&game, &ev);
			}
		}

		game_refresh(&game, SDL_GetTicks() - last_refresh_time);
		last_refresh_time = SDL_GetTicks();

		game_render(&game);
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
