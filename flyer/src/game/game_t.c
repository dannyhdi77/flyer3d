/*
 * game_t.c
 *
 *  Created on: 2010-04-02
 *      Author: krzychu
 */
#include "game_t.h"

//initalizes game
int game_init(game_t *g){
	//initalize game renderer
	renderer_init(&g->renderer);
	default_game_renderer_settings(&g->renderer);
	renderer_reload(&g->renderer);


	g->player_model = model_load("data/StarCruiser.obj");
	aircraft_init(&g->player, g->player_model);
	aircraft_load_test_settings(&g->player);

	body_init(&g->teren, NULL, DISP_TERRAIN);

	camera_init(&g->camera, &g->player.object, CAMERA_DYNAMIC);

	segment_init(&g->seg,100.0);
	vector3_set(g->seg.color, 1.0, 0.0,0.0);

	//turn on the light
	vector3_t pos = {0.0, 10.0, 0.0};
	light_set_index(&g->light, 0);
	light_set_position(&g->light, pos);
	color_t col = {1.0, 1.0, 1.0};
	light_set_color(&g->light,col);
	light_on(&g->light);


	return 0;
}

//deletes game structure
void game_delete(game_t* g){
	renderer_delete(&g->renderer);
	model_delete(g->player_model);
}

//displays game content on screen
void game_render(game_t* g){
	renderer_start(&g->renderer);
	//apply camera transform
	renderer_set_camera(&g->renderer, &g->camera.obj);
	aircraft_display(&g->player, &g->renderer);
	renderer_display(&g->renderer, &g->teren);
	renderer_display(&g->renderer, &g->seg.obj);
	renderer_finish(&g->renderer);
}

//react on event
void game_react(game_t* g, SDL_Event *ev){
	if(ev->type == SDL_VIDEORESIZE){
		renderer_resize(&g->renderer,ev->resize.w, ev->resize.h);
		renderer_reload(&g->renderer);
	}
	else if(ev->type == SDL_JOYAXISMOTION){
		if(ev->jaxis.axis == 3){
			if(ev->jaxis.value != 0 ){
				if(ev->jaxis.value < 0)
					g->player.tail = -ANGLE_STEP;
				else
					g->player.tail = ANGLE_STEP;
			}
			else{
				g->player.tail = 0.0;
			}
		}
		else if(ev->jaxis.axis == 4){
			if(ev->jaxis.value != 0 ){
				if(ev->jaxis.value < 0)
					g->player.elevator = ANGLE_STEP;
				else
					g->player.elevator = -ANGLE_STEP;
			}
			else{
				g->player.elevator = 0.0;
			}
		}
	}
	else if(ev->type == SDL_JOYBUTTONDOWN){
		if(ev->jbutton.button == 4){
			g->player.ailerons = -ANGLE_STEP;
		}
		else if(ev->jbutton.button == 6){
			g->player.ailerons = ANGLE_STEP;
		}
	}
	else if(ev->type == SDL_JOYBUTTONUP){
		if(ev->jbutton.button == 4 || ev->jbutton.button == 6){
			g->player.ailerons = 0.0;
		}
	}
	else if(ev->type == SDL_KEYDOWN){
		printf("screenshot!\n");
		renderer_screenshot(&g->renderer,"skrin.bmp");
	}
}

//refreshes game content, physics is done here
//last parameter is time from start of app
void game_refresh(game_t* g, int t){
	float dt = ((float)t)/100.0;
	aircraft_refresh(&g->player, dt);
	camera_refresh(&g->camera, dt);
}
