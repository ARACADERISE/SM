#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dyn_array.h"

DynamicArray_* init_array() {
    DynamicArray_* array = calloc(1,sizeof(*array));
    array->ItemTitles = calloc(1,sizeof(*array->ItemTitles));
    array->ItemDetails = calloc(1,sizeof(*array->ItemDetails));
    array->amount_of_items = 0;
    
    return array;
}

DynamicArray_* append(DynamicArray_* array, char* _title, void* _item, size_t item_size) {
    array->amount_of_items++;
    
    /* Reallocating */
    array->ItemTitles = realloc(
        array->ItemTitles,
        array->amount_of_items*item_size
    );
    array->ItemDetails = realloc(
        array->ItemDetails,
        array->amount_of_items*item_size
    );
    
    /* Assigning */
    array->ItemTitles[array->amount_of_items-1] = _title;
    array->ItemDetails[array->amount_of_items-1] = _item;

   return array; 
}

int array_includes(DynamicArray_* array, char* item_name)
{
	for(int i = 0; i < array->amount_of_items; i++)
	{
		if(strcmp(array->ItemTitles[i],item_name)) return 0;
	}
	return 1;
}

char* return_item_value(DynamicArray_* array, char* item_name)
{
	for(int i = 0; i < array->amount_of_items; i++)
	{
		if(strcmp(array->ItemTitles[i],item_name)==0) return array->ItemDetails[i];
	}
	return (void*)0; // error.
}
