/*
 * light_t.h
 *
 *  Created on: 2010-04-03
 *      Author: krzychu
 */
#ifndef LIGHT_T_H_
#define LIGHT_T_H_

#include <GL/glew.h>
#include <SDL/SDL.h>

#include <body_t.h>
#include <vector3_t.h>

typedef float color_t[4];

typedef struct {
	int index;
	color_t color;
	body_t model;
} light_t;

//initalizes light
void light_init(light_t*);

//enables the light
void light_on(light_t*);

//moves light
void light_refresh(light_t* l, float dt, body_t* player);

//setters
void light_set_position(light_t*, vector3_t);
void light_set_index(light_t*, int);
void light_set_color(light_t*, color_t);

#endif /* LIGHT_T_H_ */
