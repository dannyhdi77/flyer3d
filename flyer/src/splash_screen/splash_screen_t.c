/*
 * splash_screen_t.c
 *
 *  Created on: 201.0-05-16
 *      Author: krzychu
 */

#include <splash_screen_t.h>

void splash_screen_init(splash_screen_t* s, const char* filename, game_system_t* sys){
	s->system = sys;
	s->image = SDL_LoadBMP(filename);
	if(!s->image){
		game_system_log("Error while loading splash screen bitmap\n");
		s->system->state = STATE_QUIT;
	}
	s->brightness = 0.0;
	s->life_time = 0.0;
	s->state = SPLASH_FADEIN;
}

void splash_screen_delete(splash_screen_t* s){
	SDL_FreeSurface(s->image);
}

void splash_screen_react(splash_screen_t* s, SDL_Event* e){
	//if key or joybutton is hit, we go to the game or something like it
	if(e->type == SDL_KEYDOWN || e->type == SDL_JOYBUTTONDOWN)
		s->state = SPLASH_FADEOUT;
	else if(e->type == SDL_VIDEORESIZE){
		renderer_resize(&s->system->renderer,e->resize.w, e->resize.h);
		renderer_reload(&s->system->renderer);
	}
}

void splash_screen_refresh(splash_screen_t* s, float time){
	switch(s->state){
		case SPLASH_FADEIN:
			s->brightness += SPLASH_FADE_STEP*time;
			if(s->brightness >= 1.0){
				s->brightness = 1.0;
				s->state = SPLASH_WAIT;
			}
		break;

		case SPLASH_FADEOUT:
			s->brightness -= SPLASH_FADE_STEP*time;
			if(s->brightness <= 0.0){
				game_system_communicate(s->system, 0);
			}
		break;

		case SPLASH_WAIT:
			s->life_time += time;
			if(s->life_time > SPLASH_TIME)
				s->state = SPLASH_FADEOUT;
		break;
	}
}

void splash_screen_render(splash_screen_t* s){
	//clear context
	glClearColor(0.0,0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//reset matrix state
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRasterPos3f(-0.4, 0.4,-2.0);
	glPixelZoom(1.0, -1.0);
	glPixelTransferf(GL_RED_SCALE, s->brightness);
	glPixelTransferf(GL_GREEN_SCALE, s->brightness);
	glPixelTransferf(GL_BLUE_SCALE, s->brightness);
	glDrawPixels(s->image->w, s->image->h, GL_BGR, GL_UNSIGNED_BYTE, s->image->pixels);
	glPixelTransferf(GL_RED_SCALE, 1.0);
	glPixelTransferf(GL_GREEN_SCALE, 1.0);
	glPixelTransferf(GL_BLUE_SCALE, 1.0);

	glFlush();
	SDL_GL_SwapBuffers();
}
