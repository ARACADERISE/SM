#ifndef TOKENS
#define TOKENS
#include <stdio.h>
#include <stdlib.h>

typedef struct Tokens {
	enum {
		Id,
		Colon,
		Eof // end of file, will stop parsing after this is reached
	} TokenId;
	char* token_value;
} Tokens_;

Tokens_* init_token(int token_id, char* token_value);

#endif
