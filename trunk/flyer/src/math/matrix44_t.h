/*
 * matrix44_t.h
 *
 *  Created on: 2010-04-04
 *      Author: krzychu
 */

#ifndef MATRIX44_T_H_
#define MATRIX44_T_H_

#include <vector3_t.h>

typedef float matrix44_t[16];

//sets n th matrix column to 3d vector and number
void matrix44_set_column(matrix44_t m, int n , vector3_t v, float x);

//sets n th matrix row to 3d vector and number
void matrix44_set_row(matrix44_t m, int n , vector3_t v, float x);

/*composes matrix from given vectors (a,b,c), (d,e,f)
 * (g,h,i), (j,k,l) and values X...
 *
 * |a d g j|
 * |b e h k|
 * |c f i j|
 * |X Y Z T|
 */
void matrix44_compose(matrix44_t, vector3_t, float,vector3_t, float,vector3_t, float, vector3_t, float);

#endif /* MATRIX44_T_H_ */
