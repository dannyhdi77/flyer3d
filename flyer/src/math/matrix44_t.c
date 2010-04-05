/*
 * matrix44_t.c
 *
 *  Created on: 2010-04-04
 *      Author: krzychu
 */

#include <matrix44_t.h>

//sets n th matrix column to 3d vector and number
void matrix44_set_column(matrix44_t m, int n, vector3_t v, float x){
	n *= 4;
	m[n] = v[0];
	m[n+1] = v[1];
	m[n+2] = v[2];
	m[n+3] = x;
}

/*composes matrix from given vectors (a,b,c), (d,e,f)
 * (g,h,i), (j,k,l) and values X...
 *
 * |a d g j|
 * |b e h k|
 * |c f i j|
 * |X Y Z T|
 */
void matrix44_compose(matrix44_t m, vector3_t v1, float x1,vector3_t v2,
		float x2, vector3_t v3, float x3, vector3_t v4, float x4)
{
	matrix44_set_column(m,0,v1,x1);
	matrix44_set_column(m,1,v2,x2);
	matrix44_set_column(m,2,v3,x3);
	matrix44_set_column(m,3,v4,x4);
}

