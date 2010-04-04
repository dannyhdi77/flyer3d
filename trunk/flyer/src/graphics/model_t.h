/*
 * model.h
 *
 *  Created on: 2010-03-30
 *      Author: krzychu
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <messages.h>
#include <list_t.h>
#include <GL/gl.h>

#ifndef MODEL_T_H_
#define MODEL_T_H_

//point in 3d space
typedef struct{
	float x,y,z;
} point_t;

//texture coordinates
typedef struct{
	float u,v;
} uv_coordinate_t;

//vertex
typedef struct {
	int position;	//index in points table
	int normal;		//index in normal table
	int uv_coord;	//index in uv table
} vertex_t;

//polygon
typedef struct{
	int n_vert;	//number of vertexes
	vertex_t *vertexes;	//vertex table
} polygon_t;

//object model
typedef struct{
	int n_poly;	//number of polygons
	polygon_t* polygons; //table of polygons

	int n_points;
	point_t* points;

	int n_normals;
	point_t* normals;

	int n_uv;
	uv_coordinate_t* uv_coords;
} model_t;

//loads obj model from a file
model_t* model_load(const char*);

//deletes obj model
void model_delete(model_t*);

//displays model info
void model_info(model_t*);

//displays model in text mode
void model_text_display(model_t*);

//displays model
void model_display(model_t*);


#endif /* MODEL_H_ */
