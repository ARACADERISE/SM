#ifndef LEXER
#define LEXER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"

typedef struct Lexer {
	char* src;
	char curr_char;
	int index;
	int line;
} Lexer_;

Lexer_* init_lexer(char* source_code);
Tokens_* next_token(Lexer_* lexer);
#endif
