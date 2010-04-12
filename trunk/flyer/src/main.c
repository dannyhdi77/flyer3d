#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <math.h>

#include <game_system_t.h>
#include <game_t.h>
#include <vector3_t.h>

int main(){
	//vector test, for future removal
	vector3_t v;
	v[0] = 5;
	v[1] = 0;
	v[2] = 0;
	printf("len %f\n", vector3_length(v));
	vector3_normalize(v);
	printf("len %f\n", vector3_length(v));

	//general game system initalization
//	game_system_t system;
	game_system_init(NULL);

	//initalize game
	game_t game;
	game_init(&game);

	//main loop
	SDL_Event ev;
	int last_refresh_time = SDL_GetTicks();
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
	}

	//finish section
	game_system_quit(NULL);
}
