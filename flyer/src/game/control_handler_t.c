/*
 * control_handler.c
 *
 *  Created on: 2010-04-06
 *      Author: krzychu
 */

/*
 * functionality of translating SDL events into game events is
 * implemented as returninig content of specific table.
 */

#include <control_handler_t.h>

//finds event index
int control_event_index(SDL_Event *ev){
	if(ev->type == SDL_JOYAXISMOTION){
		if(ev->jaxis.value == 0)
			return CH_JOAXIS_0 + ev->jaxis.axis;
		else if(ev->jaxis.value > 0)
			return CH_JOAXIS_PLUS + ev->jaxis.axis;
		else if(ev->jaxis.value < 0)
			return CH_JOAXIS_MINUS + ev->jaxis.axis;
	}
	else if(ev->type == SDL_JOYBUTTONDOWN){
		return CH_JOYBUTTON_DOWN + ev->jbutton.button;
	}
	else if(ev->type == SDL_JOYBUTTONUP){
		return CH_JOYBUTTON_UP + ev->jbutton.button;
	}
}

//translates event to player action
char control_translate(control_handler_t h, SDL_Event *ev){
	return h[control_event_index(ev)];
}
