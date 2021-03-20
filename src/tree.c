#include "tree.h"

Tree_* init_tree(Parser_* parser)
{
	Tree_* tree = calloc(1,sizeof(*tree));

	tree->parser = parser;
	tree->user_defined_variables = init_array();

	return tree;
}
