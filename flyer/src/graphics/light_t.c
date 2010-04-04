/*
 * light_t.c
 *
 *  Created on: 2010-04-03
 *      Author: krzychu
 */

#include <light_t.h>

//initalizes light
void light_on(light_t* l){
	//diffuse part
	glLightfv(GL_LIGHT0 + l->index, GL_DIFFUSE, l->color);
	glEnable(GL_LIGHT0 + l->index);
}

//setters
void light_set_position(light_t* l, vector3_t p){
	float pos[] = {p[0], p[1], p[2], 1.0};
	glLightfv(GL_LIGHT0,GL_POSITION, pos);
}

void light_set_index(light_t* l, int i){
	l->index = i;
}

void light_set_color(light_t* l, color_t c){
	l->color[0] = c[0];
	l->color[1] = c[1];
	l->color[2] = c[2];
}

