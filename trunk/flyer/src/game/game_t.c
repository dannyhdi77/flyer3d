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

	//haha
	g->angle_step_x = 0.0;
	g->angle_step_y = 0.0;
	g->fspeed = 0.0;

	body_init(&g->air,model_load("data/StarCruiser.obj"), DISP_MODEL);
	vector3_t airpos = {1.0,0.0,-10.0};
	vector3_set_v(g->air.position, airpos);
	vector3_set_v(airpos, g->air.forward);
//	vector3_rotate(g->air.forward, g->air.up, 3.14159265/4.0);



	body_init(&g->terrain, NULL, DISP_TERRAIN);

	body_init(&g->camera,NULL, DISP_NONE);
	vector3_t posit = {-1.0, 1.0, 1.0};
	body_set_position(&g->camera,posit);


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
}

//displays game content on screen
void game_render(game_t* g){
	renderer_start(&g->renderer);
	//apply camera transform
	renderer_set_camera(&g->camera);
	renderer_display(&g->renderer,&g->air);
	renderer_display(&g->renderer,&g->terrain);
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
					g->angle_step_x = -ANGLE_STEP;
				else
					g->angle_step_x = ANGLE_STEP;
			}
			else{
				g->angle_step_x = 0.0;
			}
		}
		else if(ev->jaxis.axis == 4){
			if(ev->jaxis.value != 0 ){
				if(ev->jaxis.value < 0)
					g->angle_step_y = ANGLE_STEP;
				else
					g->angle_step_y = -ANGLE_STEP;
			}
			else{
				g->angle_step_y = 0.0;
			}
		}
	}
	else if(ev->type == SDL_JOYBUTTONDOWN){
		if(ev->jbutton.button == 4){
			g->fspeed = FSPEED;
		}
	}
	else if(ev->type == SDL_JOYBUTTONUP){
		if(ev->jbutton.button == 4){
			g->fspeed = 0;
		}
	}
}

//refreshes game content, physics is done here
//last parameter is time from start of app
void game_refresh(game_t* g, int t){
	body_rotate(&g->camera, B_OUT, g->angle_step_y);
	body_rotate(&g->camera, B_FORWARD, g->angle_step_x);
	body_move_forward(&g->camera, g->fspeed);
}
