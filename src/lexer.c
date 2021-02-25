#include "lexer.h"

Lexer_* init_lexer(char* source_code)
{
	Lexer_* lexer = calloc(1,sizeof(*lexer));
	lexer->src = source_code;
	lexer->index = 0;
	lexer->curr_char = lexer->src[lexer->index];
	lexer->line = 1;

	return lexer;
}

void advance_index(Lexer_* lexer)
{
	lexer->index++;
	lexer->curr_char = lexer->src[lexer->index];
	if(lexer->curr_char == '\n')
	{
		do {
			lexer->line++;
			lexer->index++;
			lexer->curr_char = lexer->src[lexer->index];
		} while(lexer->curr_char == '\n');
	}
}

Tokens_* create_token(Lexer_* lexer, int t_i, char* val)
{
	advance_index(lexer);
	return init_token(t_i, val);
}

void skip_whitespace(Lexer_* lexer)
{
	if(lexer->curr_char == ' ')
	{
		do
		{
			advance_index(lexer);
		} while(lexer->curr_char == ' ' || lexer->curr_char == '\t');
	}
}

char* convert_to_string(char val)
{
	char* converted_value = calloc(1,sizeof(*converted_value));

	converted_value[0] = val;
	converted_value[1] = '\0';
	return converted_value;
}

char* gather_keyword(Lexer_* lexer)
{
	char* keyword = calloc(1,sizeof(*keyword));

	do
	{
		keyword = realloc(
			keyword,
			strlen(keyword)+2*sizeof(*keyword)
		);
		strcat(keyword,convert_to_string(lexer->curr_char));
		advance_index(lexer);
	} while(isalnum(lexer->curr_char));

	return keyword;
}

Tokens_* next_token(Lexer_* lexer)
{
	
	while(lexer->curr_char != '\0' && lexer->index < strlen(lexer->src))
	{
		if(lexer->curr_char == ' ' || lexer->curr_char == '\t') skip_whitespace(lexer);
		if(lexer->curr_char == '\n') advance_index(lexer);
		if(isalnum(lexer->curr_char)) // Implement keyword later, for now, just have user-defined keyword
		{
			char* var = gather_keyword(lexer);
			return create_token(lexer,0,var);
		}

		switch(lexer->curr_char)
		{
			case ':': return create_token(lexer,1,":");break;
			case '\0': break;
			default:
			{
				fprintf(stderr,"Uncaught value '%c', line %d.\n", lexer->curr_char, lexer->line);
				exit(EXIT_FAILURE);
			}
		}
		break;

	}
	return create_token(lexer,2,"\0");
}
