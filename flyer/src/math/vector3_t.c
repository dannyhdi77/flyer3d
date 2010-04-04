/*
 * vector3_t.c
 *
 *  Created on: 2010-04-03
 *      Author: krzychu
 */
#include <vector3_t.h>

//calculates vector length
float vector3_length(vector3_t v){
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

//scales vector to be unit length
void vector3_normalize(vector3_t v){
	float len = vector3_length(v);

	if(len == 0)
		return;	//vector of length 0, whatever we do it will be awkward

	//scaling vector coordinates
	v[0] /= len;
	v[1] /= len;
	v[2] /= len;
}

//calculates cross product
//c = a x b
void vector3_cross_product(vector3_t c, vector3_t a, vector3_t b){
	c[0] = a[1]*b[2] - a[2]*b[1];
	c[1] = a[0]*b[2] - a[2]*b[0];
	c[2] = a[0]*b[1] - a[1]*b[0];
}

//sets vector coordinates
void vector3_set(vector3_t v, float x, float y, float z){
	v[0] = x;
	v[1] = y;
	v[2] = z;
}
