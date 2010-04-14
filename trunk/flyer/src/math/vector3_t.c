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
	c[1] = a[2]*b[0] - a[0]*b[2];
	c[2] = a[0]*b[1] - a[1]*b[0];
}

//sets vector coordinates
void vector3_set(vector3_t v, float x, float y, float z){
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

//sets vector to be equal to other vector
void vector3_set_v(vector3_t v, vector3_t src){
	v[0] = src[0];
	v[1] = src[1];
	v[2] = src[2];
}

//inverts vector coordinates
void vector3_invert(vector3_t v){
	v[0] = -v[0];
	v[1] = -v[1];
	v[2] = -v[2];
}

//multiplies vector by scalar
void vector3_scale(vector3_t v, float k){
	v[0] *= k;
	v[1] *= k;
	v[2] *= k;
}

//adds vector to a vector
void vector3_add(vector3_t v, vector3_t b){
	v[0] += b[0];
	v[1] += b[1];
	v[2] += b[2];
}


//rotates vector around specified axis
void vector3_rotate(vector3_t result, vector3_t axis, float angle){
	//some values for easier notation
	float c = cos(angle);
	float s = sin(angle);
	float t = 1-cos(angle);
	//algebra says: we have to do it
	vector3_t a = {axis[0], axis[1], axis[2]};
	vector3_normalize(a);
	//transformation matrix, it is too complicated to tell here how it is
	//derieved, for reference visit : http://www.gamedev.net/reference/articles/article1199.asp
	float rotation_matrix[3][3] = {
			{t*a[0]*a[0] + c     , t*a[0]*a[1] - s*a[2], t*a[0]*a[2] + s*a[1]},
			{t*a[0]*a[1] + s*a[2], t*a[1]*a[1] + c,      t*a[1]*a[2] - s*a[0]},
			{t*a[0]*a[2] - s*a[1], t*a[1]*a[2] + s*a[0], t*a[2]*a[2] + c}
	};
	//actual multiplication
	int i,k;
	vector3_t v;
	vector3_set_v(v, result);
	vector3_set(result, 0.0,0.0,0.0);
	for(i=0 ; i<3 ; i++)
		for(k = 0; k<3 ; k++)
			result[i] += rotation_matrix[k][i]*v[k];
}

//for debugging, prints vector on the screen
void vector3_print(vector3_t v){
	printf("%f %f %f\n", v[0], v[1], v[2]);
}

//subtracts vector from a vector a -= b
void vector3_subtract(vector3_t v, vector3_t b){
	v[0] -= b[0];
	v[1] -= b[1];
	v[2] -= b[2];
}
