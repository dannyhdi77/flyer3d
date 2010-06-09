/*
 * fifo_t.h
 *
 *  Created on: 2010-04-14
 *      Author: krzychu
 */

#ifndef FIFO_T_H_
#define FIFO_T_H_

#include <string.h>
#include <stdlib.h>

typedef struct {
	//pointer to actual data
	void *data;

	//number of elements
	int size;

	//size of each element
	size_t elem_size;

	//max number of elements
	int max_size;

	//indexes of first and last elements
	void* first, *last;

	//front index
	void *front;

} fifo_t;

//Initialization
void fifo_init(fifo_t*, size_t, int);

//destruction
void fifo_delete(fifo_t*);

//insert something, return 0 if not successful
int fifo_insert(fifo_t*, void*);

//get something, return 0 if not successful
int fifo_get(fifo_t*, void*);

//returns fifo size
int fifo_size(fifo_t*);

//iterate fifo contents with specified function
typedef void (*fifo_fun)(void*, void*);
void fifo_iterate(fifo_t*, fifo_fun f, void*);

//returns pointer to front of fifo
void* fifo_get_front_pointer(fifo_t*);

//returns pointer to back of fifo
void* fifo_get_back_pointer(fifo_t*);

#endif /* FIFO_T_H_ */
