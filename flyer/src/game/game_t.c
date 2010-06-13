/*
 * game_t.c
 *
 *  Created on: 2010-04-02
 *      Author: krzychu
 */
#include "game_t.h"

//Initializes game
int game_init(game_t *g, game_system_t* sys){
	g->system = sys;

	g->player_model = model_load("data/skull.obj");
	aircraft_init(&g->player, g->player_model);
	aircraft_load_test_settings(&g->player);

	body_init(&g->teren);

	camera_init(&g->camera, &g->player.object, CAMERA_DYNAMIC);

	//segment_init(&g->seg,100.0);
	//vector3_set(g->seg.color, 1.0, 0.0,0.0);
	pipe_init(&g->pipe, 5);


	//turn on the light
	vector3_t pos = {0.0, 10.0, 0.0};
	light_set_index(&g->light, 0);
	light_set_position(&g->light, pos);
	color_t col = {1.0, 1.0, 1.0};
	light_set_color(&g->light,col);
	light_on(&g->light);

	g->score = 0;
	return 0;
}

//deletes game structure
void game_delete(game_t* g){
	model_delete(g->player_model);
}

//displays game content on screen
void game_render(game_t* g){
	renderer_set_camera(&g->system->renderer, &g->camera.obj);
	renderer_start(&g->system->renderer);
	aircraft_display(&g->player);
	pipe_display(&g->pipe);

	//display point counter
	vector3_t rel = {-((float)((int)log10(g->score)))*0.1,1.0,2.0};
	matrix44_t transform;
	body_get_transformation_matrix(&g->player.object, transform);
	matrix44_mul_vector(transform, rel);
	printw(rel[0],rel[1],rel[2],0,0,0,"%d",g->score);

	renderer_finish(&g->system->renderer);
}

//react on event
void game_react(game_t* g, SDL_Event *ev){
	if(ev->type == SDL_VIDEORESIZE){
		renderer_resize(&g->system->renderer,ev->resize.w, ev->resize.h);
		renderer_reload(&g->system->renderer);
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
		//printf("screenshot!\n");
		//renderer_screenshot(&g->system->renderer,"skrin.bmp");
		switch(ev->key.keysym.sym){
			case SDLK_RIGHT:
				g->player.tail = ANGLE_STEP;
			break;

			case SDLK_LEFT:
				g->player.tail = -ANGLE_STEP;
			break;

			case SDLK_UP:
				g->player.elevator = ANGLE_STEP;
			break;

			case SDLK_DOWN:
				g->player.elevator = -ANGLE_STEP;
			break;
		}
	}
	else if(ev->type == SDL_KEYUP){
		switch(ev->key.keysym.sym){
			case SDLK_RIGHT:
				g->player.tail = 0;
			break;

			case SDLK_LEFT:
				g->player.tail = 0;
			break;

			case SDLK_UP:
				g->player.elevator = 0;
			break;

			case SDLK_DOWN:
				g->player.elevator = 0;
			break;
		}
	}
}

//refreshes game content, physics is done here
//last parameter is time from start of app
void game_refresh(game_t* g, int t){
	float dt = ((float)t)/100.0;
	aircraft_refresh(&g->player, dt);
	camera_refresh(&g->camera, dt);
	light_refresh(&g->light, dt, &g->player.object);
	pipe_refresh(&g->pipe, dt, &g->player.object);

	//perform collision check
	if(pipe_collision(&g->pipe,&g->player.object.position)){
		game_system_communicate(g->system,g->score);
		game_system_t* tmp;
		//restart game
		tmp = g->system;
		game_delete(g);
		game_init(g,tmp);
	}

	//increase score
	static int last_score = 0;
	last_score += t;
	if(last_score > POINT_WAIT){
		last_score = 0;
		g->score++;
	}

	//increase speed
	static int last_speed = 0;
	last_speed += t;
	if(last_speed > SPEED_WAIT){
		last_speed = 0;
		g->player.speed += SPEED_STEP;
	}
}
