/*
 * utilties.c
 *
 *  Created on: 2010-04-19
 *      Author: krzychu
 */

#include <utilties.h>

//generate random number from range
float random_range(float down, float up){
	float r = ((float)(rand()%100000))/100000.0;
	return down*r+(1-r)*up;
}

