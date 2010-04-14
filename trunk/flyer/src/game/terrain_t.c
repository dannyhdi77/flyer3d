/*
 * terrain_t.c
 *
 *  Created on: 2010-04-13
 *      Author: krzychu
 */

#include <terrain_t.h>

//initalizes terrain with specified file
void terrain_init(terrain_t* t, const char *path){
	body_init(&t->object, t, DISP_TERRAIN);

	//try to load terrain map
	SDL_Surface *map = SDL_LoadBMP(path);
	SDL_LockSurface(map);
	if(map == NULL){
		//error, display something and exit
	}

	//read dimensions
	t->x = map->w;
	t->y = map->h;

	//allocate memory
	t->height_map = (float*)malloc(sizeof(float)*t->x*t->y);

	//read height map
	int x, y;
	float maxheight = 10.0;
	uint8_t* itr = (uint8_t*)map->pixels;
	for(y = 0; y<map->h ; y++){
		for(x = 0; x<map->pitch ; x++){
			if((x%3 == 0)&&(x/3 < map->w)){
				t->height_map[y*t->x + x/3] = (maxheight*((float)*itr))/255.0;
			}
			itr++;
		}
	}

	//clean up
	SDL_FreeSurface(map);
}

//returns height at specified point
void terrain_get_height(terrain_t*, float, float);

//renders terrain on screen
void terrain_display(terrain_t* t){
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	int x, y;
	for(y = 0; y < t->y ; y++){
			for(x = 0; x< 100 ; x++){
				glVertex3f(x,t->height_map[y*t->x +x ],-y);
			}
		}
/*
	for(x = 0 ; x < 1000; x+=1){
		glVertex3f(0.0, -5.0, -x);
	}
*/
	glEnd();

}

//displays terrain in text mode
void terrain_display_text(terrain_t* t){
	int x, y;
	for(y = 0; y < t->y ; y++){
		for(x = 0; x< t->x ; x++){
			printf("%f ", t->height_map[y*t->x +x ]);
		}
		printf("\n");
	}
}

//deletes terrain
void terrain_delete(terrain_t* t){
	free(t->height_map);
}
