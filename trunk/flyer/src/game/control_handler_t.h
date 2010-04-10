/*
 * control_handler.h
 *
 *  Created on: 2010-04-06
 *      Author: krzychu
 */

#ifndef CONTROL_HANDLER_H_
#define CONTROL_HANDLER_H_

#include <SDL/SDL.h>

#define CONTROL_HANDLER_SIZE 50

typedef char control_handler_t[CONTROL_HANDLER_SIZE];

//player action definitions


//event indexes
#define CH_JOYAXIS_0 0
#define CH_JOYAXIS_PLUS 10
#define CH_JOYAXIS_MINUS 20

#define CH_JOYBUTTON_DOWN 30
#define CH_JOYBUTTON_UP 45

//translates event into player action
char control_translate(control_handler_t, SDL_Event *ev);


#endif /* CONTROL_HANDLER_H_ */
