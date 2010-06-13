/*
 * score_screen_t.c
 *
 *  Created on: 201.0-05-16
 *      Author: krzychu
 */

#include <score_screen_t.h>

void score_screen_init(score_screen_t* s, const char* filename, game_system_t* sys){
	s->system = sys;
	s->image = SDL_LoadBMP(filename);
	if(!s->image){
		game_system_log("Error while loading score screen bitmap\n");
		s->system->state = STATE_QUIT;
	}
}

void score_screen_delete(score_screen_t* s){
	SDL_FreeSurface(s->image);
}

void score_screen_react(score_screen_t* s, SDL_Event* e){
	//if key or joybutton is hit, we go to the game or something like it
	if(e->type == SDL_KEYDOWN || e->type == SDL_JOYBUTTONDOWN)
		game_system_communicate(s->system, 0);
	else if(e->type == SDL_VIDEORESIZE){
		renderer_resize(&s->system->renderer,e->resize.w, e->resize.h);
		renderer_reload(&s->system->renderer);
	}
}

void score_screen_refresh(score_screen_t* s, float time, int score){
	s->score = score;
}

void score_screen_render(score_screen_t* s){
	//clear context
	glClearColor(0.0,0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//reset matrix state
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRasterPos3f(-0.5, 0.6,-2.0);
	glPixelZoom(1.0, -1.0);
	glDrawPixels(s->image->w, s->image->h, GL_BGR, GL_UNSIGNED_BYTE, s->image->pixels);
	printw(0.02-floor(log10(s->score))*0.008,-0.23,-1.0,1.0,1.0,1.0,"%d",s->score);
	glPixelTransferf(GL_RED_SCALE, 1.0);
	glPixelTransferf(GL_GREEN_SCALE, 1.0);
	glPixelTransferf(GL_BLUE_SCALE, 1.0);

	glFlush();
	SDL_GL_SwapBuffers();
}
