#ifndef PARSER
#define PARSER
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "tokens.h"

typedef struct Parser
{
	Lexer_* lexer;
	Tokens_* tokens;
} Parser_;

Parser_* init_parser(Lexer_* lexer);
Parser_* parse(Parser_* parser);

#endif
