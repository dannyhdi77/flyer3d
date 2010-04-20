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

//sets n th matrix row to 3d vector and number
void matrix44_set_row(matrix44_t m, int n , vector3_t v, float x){
	m[n] = v[0];
	m[n+4] = v[1];
	m[n+8] = v[2];
	m[n+12] = x;
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

//multiplies two 4x4 matrices
//result = result*a;
void matrix44_mul(matrix44_t result, matrix44_t a){
	matrix44_t tmp;
	int i,j,k;
	for(i = 0; i<4; i++)
		for(j = 0 ; j<4; j++){
			tmp[j+4*i] = 0;
			for(k = 0; k<4; k++)
				tmp[j+4*i] += result[j + 4*k]*a[k + 4*i];
		}
	matrix44_copy(result, tmp);
}

//copies matrix
void matrix44_copy(matrix44_t dest, matrix44_t src){
	int i;
	for(i=0; i<16; i++)
		dest[i] = src[i];
}

//sets matrix to be identity
void matrix44_identity(matrix44_t dest){
	int i;
	for(i = 0; i< 16 ; i++){
		if(i%5 == 0){
			dest[i] = 1.0;
		}
		else{
			dest[i] = 0.0;
		}
	}
}

//multiplies vector by matrix
void matrix44_mul_vector(matrix44_t matrix, vector3_t vec){
	//in order to muliply vector, we have to extend it
	float ev[4];	//extended vector
	vector3_set_v(ev, vec);
	ev[3] = 1.0;

	float result[4] = {0.0,0.0,0.0,0.0};	//result of operation
	int i,j;
	for(i=0; i<4 ; i++)
		for(j=0; j<4; j++)
			result[i] += ev[j]*matrix[i+4*j];
	vector3_set_v(vec, result);
}
