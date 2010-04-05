/*
 * vector3_t.h
 *
 *  Created on: 2010-04-03
 *      Author: krzychu
 */

#ifndef VECTOR3_T_H_
#define VECTOR3_T_H_

#include <math.h>

//not a structure, only a typedef
typedef float vector3_t[3];

//calculates vector length
float vector3_length(vector3_t);

//scales vector to be unit length
void vector3_normalize(vector3_t);

//calculates cross product
//c = a x b
void vector3_cross_product(vector3_t c, vector3_t a, vector3_t b);

//sets vector coordinates
void vector3_set(vector3_t v, float x, float y, float z);

//sets vector to be equal to other vector
void vector3_set_v(vector3_t v, vector3_t src);

//inverts vector coordinates
void vector3_invert(vector3_t);

//rotates vector around specified axis
void vector3_rotate(vector3_t result, vector3_t axis, float angle, vector3_t v);

#endif /* VECTOR3_T_H_ */
