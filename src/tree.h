#ifndef TREE
#define TREE
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "dynamic-arrays/dyn_array.h"

typedef struct Tree
{
	Parser_* parser;
	enum {
		T_Id,
		StrVal
	} TId;
	DynamicArray_* user_defined_variables;
	int atp; // Ammount To Print
	char** to_print; // Things that the user wants to print(via the echo keyword)
} Tree_;

Tree_* init_tree(Parser_* parser);

#endif
