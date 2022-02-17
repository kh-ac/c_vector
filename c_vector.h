#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define INIT_CAPACITY 32 

typedef int element_type ;
typedef struct Vector* vector ;
typedef struct Vector Vector ;

struct Vector
{
    element_type* array ;    
    unsigned      size ;
    unsigned      capacity ;
};

unsigned min(int a , int b)
{
    return ( (a<b)? a : b );
}

vector vector_create()
{
    vector v = (vector)calloc(INIT_CAPACITY,sizeof(Vector)) ;
    if(!v)
    {
        fprintf(stderr,"Not enough memory!");   
        abort();
    }

    v->size = 0 ;
    v->capacity = INIT_CAPACITY ;
    v->array = (element_type*)calloc(v->capacity,sizeof(element_type));
    if(!(v->array))
    {
        fprintf(stderr,"Not enough memory!");   
        abort();
    } 
    return v ;
}

void vector_print(vector v)
{
    for (int i = 0 ; i < v->size ; i++ )
    {
        printf("%d|",v->array[i]);
    }

}

void vector_delete(vector v)
{
    assert(v);
    free(v->array);
    free(v);
}

void vector_double_capacity(vector v)
{
    assert(v);
    v->capacity *= 2;
    element_type* new_array = (element_type*)calloc(v->capacity,sizeof(element_type));
    if(!new_array)
    {
        fprintf(stderr,"Not enough memory!");   
        abort();
    } 

    for (int i = 0 ; i<v->size ;i++)
    {
        *(new_array+i) = *(v->array+i);
    }

    free(v->array);
    v->array = new_array ;

}

void vector_half_capacity(vector v)
{
    assert(v);
    if (v->capacity <= INIT_CAPACITY) return ;

    v->capacity /= 2;

    element_type* new_array = (element_type*)calloc(v->capacity,sizeof(element_type));
    if(!new_array)
    {
        fprintf(stderr,"Not enough memory!");   
        abort();
    }

    for (int i = 0 ; i<v->size ; i++)
    {
        *(new_array+i) = *(v->array+i);
    }

    free(v->array);
    v->array = new_array ;
    v->size = min(v->capacity,v->size);    
}

void vector_add(vector v , element_type element)
{
    assert(v);
    if(v->size == v->capacity) vector_double_capacity(v);
    v->array[v->size] = element ;
    
}