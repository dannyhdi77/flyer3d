/*
 * model.c
 *
 *  Created on: 2010-03-30
 *      Author: krzychu
 */
#include "model_t.h"

#define MAX_LINE_LENGTH 20000
#define MAX_POLYGONS 200000



//loads obj model from a file
model_t* model_load(const char* filename){

	//open model file
	FILE* model_f = fopen(filename, "r");
	if(model_f == NULL){
		//fixme please
		printf("failed.\n");
		exit(0);
	}

	//loading

	//temporary data
	list_t t_points;	//list of all points
	point_t tp;	//temporary point
	list_init(&t_points, sizeof(point_t), NULL);

	list_t t_normals;
	point_t tn;
	list_init(&t_normals, sizeof(point_t), NULL);

	list_t t_uv;
	uv_coordinate_t tuv;
	list_init(&t_uv, sizeof(uv_coordinate_t), NULL);

	list_t t_polygons[MAX_POLYGONS];
	int n_poly = 0; //number of polygons
	vertex_t tv;
	int i;
	for(i=0 ; i<MAX_POLYGONS; i++){
		list_init(t_polygons+i,sizeof(vertex_t),NULL);
	}

	int max_line_length = MAX_LINE_LENGTH;
	char* line = (char*) malloc(max_line_length*sizeof(char));
	char* lb; //points to beginning of a line
	while(getline(&line, &max_line_length, model_f) > -1){
		//delete white characters
		lb = line;
		if(*lb == '\0')
			continue;

		while(isspace(*lb))
			lb++;

		if(*lb == 'v'){
			lb++;
			if(*lb == 'n'){
				lb++;
				//normal
				sscanf(lb, "%f %f %f", &(tn.x), &(tn.y), &(tn.z));
				list_insert(&t_normals, &tn);
			}
			else if(*lb == 't'){
				lb++;
				//texture coordinates
				sscanf(lb, "%f %f", &(tuv.u), &(tuv.v));
				list_insert(&t_uv, &tuv);
			}
			else if(*lb == ' '){
				//point
				sscanf(lb, "%f %f %f", &(tp.x), &(tp.y), &(tp.z));
				list_insert(&t_points, &tp);
			}
		}
		else if(*(lb) == 'f'){
			lb++;
			//polygon
			//skip white chars
			while(isspace(*lb))
				lb++;
			//read all vertices
			while(*lb != '\0'){
				tv.position = 0;
				tv.normal = 0;
				tv.uv_coord = 0;
				//read position
				sscanf(lb,"%d",&(tv.position));
				//skip number
				while(isdigit(*lb)||(*lb == '-')||(*lb == '.'))
					lb++;

				//read other parameters
				if(*lb == '/'){
					lb++;
					if(*lb != '/'){
						//read texture index
						sscanf(lb,"%d",&(tv.uv_coord));
						//skip number
						while(isdigit(*lb)||(*lb == '-')||(*lb == '.'))
							lb++;
					}
					else{
						lb++;	//skip /
					}
					sscanf(lb,"%d",&(tv.normal));
					while(isdigit(*lb)||(*lb == '-')||(*lb == '.'))
						lb++;
				}

				//skip white chars
				while((*lb!='\0')&&isspace(*lb))
					lb++;

				//printf("vertex: %d %d %d\n",tv.position, tv.uv_coord, tv.normal);
				tv.normal--;
				tv.position--;
				tv.uv_coord--;
				list_insert(t_polygons + n_poly,&tv);
			}
			n_poly++;
		}
	}

	//finally, create model
	model_t *model = (model_t *) malloc(sizeof(model_t));
	model->points = (point_t*) malloc(sizeof(point_t)*t_points.length);
	model->n_points = t_points.length;

	model->normals = (point_t*) malloc(sizeof(point_t)*t_normals.length);
	model->n_normals = t_normals.length;

	model->uv_coords = (uv_coordinate_t*) malloc(sizeof(uv_coordinate_t)*t_uv.length);
	model->n_uv = t_uv.length;

	model->polygons = (polygon_t*) malloc(sizeof(polygon_t)*n_poly);
	model->n_poly = n_poly;

	list_to_table(&t_points,model->points);
	list_to_table(&t_normals,model->normals);
	list_to_table(&t_uv,model->uv_coords);

	for(i = 0; i<n_poly ; i++){
		model->polygons[i].vertexes = (vertex_t*)malloc(sizeof(vertex_t)*t_polygons[i].length);
		model->polygons[i].n_vert = t_polygons[i].length;
		list_to_table(t_polygons+i,model->polygons[i].vertexes);
	}

	//clean up
	list_delete(&t_points);
	list_delete(&t_normals);
	list_delete(&t_uv);
	for(i=0 ; i<MAX_POLYGONS; i++){
		list_delete(t_polygons+i);
	}
	free(line);
	fclose(model_f);

	return model;
}

//deletes obj model
void model_delete(model_t* m){
	free(m->normals);
	free(m->points);
	free(m->uv_coords);
	int i;
	for(i = 0; i < m->n_poly; i++)
		free(m->polygons[i].vertexes);
	free(m->polygons);
}

//displays model info
void model_info(model_t*);

//displays model in text mode
void model_text_display(model_t* m){
	//display point list
	int i;
	for(i = 0; i < m->n_points; i++)
		printf("point %d: %f %f %f\n",i ,m->points[i].x,m->points[i].y, m->points[i].z);

	//uv coordinates list
	for(i = 0; i < m->n_uv; i++)
			printf("uv %d: %f %f\n",i ,m->uv_coords[i].u,m->uv_coords[i].v);

	//normals list
	for(i = 0; i < m->n_normals; i++)
		printf("normal %d: %f %f %f\n",i ,m->normals[i].x,m->normals[i].y, m->normals[i].z);

	int j;

	//polygons
	for(i = 0; i<m->n_poly; i++){
		printf("polygon %d\n",i);
		for(j = 0; j < m->polygons[i].n_vert; j++){
			printf("	vertex %d: %d %d %d\n", j,
					m->polygons[i].vertexes[j].position,
					m->polygons[i].vertexes[j].uv_coord,
					m->polygons[i].vertexes[j].normal);
		}
	}

}

//displays model
void model_display(model_t* m){
	int i,j;
	int a;
	glColor3f(1.0,0.8,0.4);
	for(i = 0; i<m->n_poly ; i++){
		glBegin(GL_TRIANGLE_FAN);
			for(j=0; j <= m->polygons[i].n_vert; j++){
				a = j%m->polygons[i].n_vert;
				if(m->polygons[i].vertexes[a].normal >= 0){
					glNormal3f(-m->normals[m->polygons[i].vertexes[a].normal].x,
							-m->normals[m->polygons[i].vertexes[a].normal].y,
							-m->normals[m->polygons[i].vertexes[a].normal].z);
				}

				glVertex3f(m->points[m->polygons[i].vertexes[a].position].x,
						m->points[m->polygons[i].vertexes[a].position].y,
						m->points[m->polygons[i].vertexes[a].position].z);
			}
		glEnd();
	}
}
