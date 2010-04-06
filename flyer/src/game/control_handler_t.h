/*
 * control_handler.h
 *
 *  Created on: 2010-04-06
 *      Author: krzychu
 */

#ifndef CONTROL_HANDLER_H_
#define CONTROL_HANDLER_H_

#include <SDL/SDL.h>

#define CONROL_HANDLER_SIZE 50

typedef char control_handler_t[CONTROL_HANDLER_SIZE];

//player action definitions

//translates event into player action
char control_translate(control_handler_t, SDL_Event *ev);


#endif /* CONTROL_HANDLER_H_ */
