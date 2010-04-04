/*
 * list.h
 *	generic list implementation
 *  Created on: 2010-03-30
 *      Author: krzychu
 */
#include <stdlib.h>
#include <string.h>

#ifndef LIST_T_H_
#define LIST_T_H_

/*list element*/
struct s_list_elem_t{
	struct s_list_elem_t* next;
	void* data;
};

/*struct is a bad word*/
typedef struct s_list_elem_t list_elem_t;

/*function operating on data of list element*/
typedef void (*void_fun_t)(void*, void*);

/*list itself*/
typedef struct{
	list_elem_t* head;
	size_t elem_size;
	int length;
	void_fun_t destroyer; /*function called for each element at destruction time*/
} list_t;

//initalizes list: (list pointer, size of element, destroyer function)
void list_init(list_t*, size_t, void_fun_t);

//deletes list
void list_delete(list_t*);

//inserts element to the front of list
void list_insert(list_t*, void*);

//deletes element from a list
void list_remove(list_t*, void*);

//iterates given function through list, suppyying it with optional args
void list_iterate(list_t*, void_fun_t, void*);

//rewrites content of list into specified table in
//reversed order
void list_to_table(list_t*, void*);

#endif /* LIST_H_ */
