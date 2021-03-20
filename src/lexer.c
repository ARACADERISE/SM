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
	if(lexer->curr_char != ' ') lexer->prev_char = lexer->curr_char;
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

char check_ahead(Lexer_* lexer, int amount)
{
	if(!(lexer->src[lexer->index+amount] == '\0')) return lexer->src[lexer->index+amount];
	return '\0';
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
		if(check_ahead(lexer,1) == '\n') break;
		advance_index(lexer);
	} while(isalnum(lexer->curr_char));

	return keyword;
}

char* gather_string(Lexer_* lexer)
{
	if(lexer->curr_char == '"') advance_index(lexer);
	char* str_value = calloc(1,sizeof(*str_value));

	do
	{
		str_value = realloc(
			str_value,
			strlen(str_value)+2*sizeof(*str_value)
		);
		strcat(str_value,convert_to_string(lexer->curr_char));
		if(lexer->curr_char == '\\')
		{
			if(check_ahead(lexer,1) == 'n')
			{
				str_value[strlen(str_value)-1] = '\n';
				advance_index(lexer); // '\'
				//advance_index(lexer); // 'n'
			}
			if(check_ahead(lexer,1) == 't')
			{
				str_value[strlen(str_value)-1] = '\t';
				advance_index(lexer);
			}
		}
		if(check_ahead(lexer,1) == '"')
		{
			advance_index(lexer);
			break;
		}
		if(check_ahead(lexer,1) == '#' || 
		   check_ahead(lexer,1) == '\0' || 
		   check_ahead(lexer,1) == '\n') break;
		advance_index(lexer);
	} while(1);

	if(str_value[strlen(str_value)-1] == ' ') str_value[strlen(str_value)-1] = '\0';
	//if(lexer->curr_char == '"') advance_index(lexer);

	//if(lexer->curr_char == ' ') skip_whitespace(lexer);
	//advance_index(lexer); // skipping '\n'
	return str_value;
}

void skip_comment(Lexer_* lexer)
{
	int curr_line = lexer->line;
	do {
		advance_index(lexer);
	} while(lexer->line <= curr_line);
}

Tokens_* next_token(Lexer_* lexer)
{
	
	while(lexer->curr_char != '\0' && lexer->index < strlen(lexer->src))
	{
		if(lexer->curr_char == '#') skip_comment(lexer);
		if(lexer->curr_char == ' ' || lexer->curr_char == '\t') skip_whitespace(lexer);
		if(lexer->curr_char == '\n') advance_index(lexer);
		if(isalnum(lexer->curr_char)) // Implement keyword later, for now, just have user-defined keyword
		{
			char* var = gather_keyword(lexer);
			if(strcmp(var,"echo")==0) return create_token(lexer,Echo,var);
			else return create_token(lexer,Id,var);
		}
		if(lexer->curr_char == '"')
		{
			char* str = gather_string(lexer);
			return create_token(lexer,String,str);
		}
		if(lexer->prev_char == ':')
		{
			char* string_value = gather_string(lexer);
			return create_token(lexer,String,string_value);
		}

		switch(lexer->curr_char)
		{
			case ':': return create_token(lexer,Colon,":");break;
			case '\0': break;
			default:
			{
				fprintf(stderr,"Uncaught value '%c', line %d.\n", lexer->curr_char, lexer->line);
				exit(EXIT_FAILURE);
			}
		}
		break;

	}
	return create_token(lexer,Eof,"\0");
}
