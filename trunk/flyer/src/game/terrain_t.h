/*
 * terrain_t.h
 *
 *  Created on: 2010-04-13
 *      Author: krzychu
 */

#ifndef TERRAIN_T_H_
#define TERRAIN_T_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include <stdio.h>
#include <body_t.h>
#include <inttypes.h>

typedef struct {
	float *height_map; //height at each point

	//dimensions
	int x, y;

	body_t object;
} terrain_t;

//initalizes terrain with specified file
void terrain_init(terrain_t*, const char *);

//returns height at specified point
void terrain_get_height(terrain_t*, float, float);

//renders terrain on screen
void terrain_display(terrain_t*);

//displays terrain in text mode
void terrain_display_text(terrain_t*);

//deletes terrain
void terrain_delete(terrain_t*);

#endif /* TERRAIN_T_H_ */
