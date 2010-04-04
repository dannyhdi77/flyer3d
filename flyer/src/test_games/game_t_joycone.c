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

	//hahaha
	g->rotation_angle_x = 40.0;
	g->rotation_angle_y = 40.0;
	g->n_points = 10;
	g->rotation_speed = 1.0;
	g->last_refresh = 0.0;

	return 0;
}

//displays game content on screen
void game_render(game_t* g){

	glClearColor(0.1,0.1, 0.1, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(g->rotation_angle_x, 0.0, 1.0, 0.0);
	glRotatef(g->rotation_angle_y, 1.0, 0.0, 0.0);

	//cone
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0,0.0,-40.0);
		int i;
		float angle = 0.0;
		float r = 20.0;
		for(i = 0; i<= g->n_points ; i++){
			if(i%2)
				glColor3f(1.0, 0.0, 0.0);
			else
				glColor3f(0.0, 1.0, 0.0);
			glVertex3f(cos(angle)*r, sin(angle)*r, 0.0);
			angle += 2.0*3.1415/(float)g->n_points;
		}
	glEnd();

	//bottom
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_TRIANGLE_FAN);
			glVertex3f(0.0,0.0, 0.0);
			angle = 0.0;
			for(i = 0; i<=g->n_points ; i++){
				glVertex3f(cos(angle)*r, sin(angle)*r, 0.0);
				angle -= 2.0*3.1415/(float)g->n_points;
			}
	glEnd();

	glPopMatrix();

	glFlush();
	SDL_GL_SwapBuffers();
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
				//printf("axis: %d\n value: %d\n",ev.jaxis.axis, ev.jaxis.value);
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
				//printf("axis: %d\n value: %d\n",ev.jaxis.axis, ev.jaxis.value);
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
}

//refreshes game content, physics is done here
//last parameter is time from start of app
void game_refresh(game_t* g, int t){
	g->rotation_angle_x += g->angle_step_x;//*(t-g->last_refresh);
	g->rotation_angle_y += g->angle_step_y;//*(t-g->last_refresh);
	g->last_refresh = t;
}
