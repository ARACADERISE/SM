#include "tokens.h"

Tokens_* init_token(int token_id, char* token_value)
{
	Tokens_* tokens = calloc(1,sizeof(*tokens));

	tokens->TokenId = token_id;
	tokens->token_value = token_value;

	return tokens;
}
