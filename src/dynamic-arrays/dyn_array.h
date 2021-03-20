#ifndef DYN_ARRAY
#define DYN_ARRAY

typedef struct DynamicArray {
    char** ItemTitles; // this will always be a string
    void** ItemDetails; // we don't know what we're storing
    size_t current_size; // this will be the allocated size for the current ItemDetail
    size_t amount_of_items;
} DynamicArray_;

DynamicArray_* init_array();
DynamicArray_* append(DynamicArray_* array, char* _title, void* _item, size_t item_size);
int arr_includes(DynamicArray_* array, char* item_name);
char* return_item_value(DynamicArray_* array, char* item_name);

#endif
