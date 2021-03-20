#include "parser.h"

char* flags;

Parser_* init_parser(Lexer_* lexer)
{
	Parser_* parser = calloc(1,sizeof(*parser));

	parser->lexer = lexer;
	return parser;
}

void get_next_token(Parser_* parser)
{
	parser->tokens = next_token(parser->lexer);
}

void print_err(Parser_* parser)
{
	if(parser->tokens->TokenId == EOF)
	{
		fprintf(stderr,"Unexpected EOF while parsing. Line %d.\n", parser->lexer->line-1);
		exit(EXIT_FAILURE);
	}
	fprintf(stderr,"Unexpected '%s' while parsing. Line %d.\n", parser->tokens->token_value, parser->lexer->line-1);
	exit(EXIT_FAILURE);
}

Parser_* parse_user_define(Parser_* parser)
{
	// save variable name to syntax tree here
redo:
	get_next_token(parser);
	if(!(parser->tokens->TokenId == Colon))
	{
		fprintf(stderr,"Expected ':', got %s\n", parser->tokens->token_value);
		exit(EXIT_FAILURE);
	}
	get_next_token(parser);
	switch(parser->tokens->TokenId)
	{
		case String:
		{
			// do something to store the value
			flags = calloc(strlen(parser->tokens->token_value) + 2, sizeof(*flags));
			flags = parser->tokens->token_value;
			get_next_token(parser);
			break;
		}
		default:
		{
			print_err(parser);
		}
	}
	if(parser->tokens->TokenId == Id) goto redo;
	return parser;
}

Parser_* parse_echo(Parser_* parser)
{
	get_next_token(parser);
	if(parser->tokens->TokenId == String)
	{
		if(strcmp(parser->tokens->token_value, "$flags")==0)
		{
			printf("%s",flags);
		} else
		{
			printf("%s",parser->tokens->token_value);
		}
		get_next_token(parser);
	} else
	{
		fprintf(stderr,"Error, line %d:\n\techo expects two double quotes.\n\tSyntax:\n\t\techo \"Something To Print Here\"\n", parser->lexer->line-1);
		exit(EXIT_FAILURE);
	}
	return parser;
}

Parser_* check_value(Parser_* parser)
{
redo_:
	switch(parser->tokens->TokenId)
	{
		case Id: parse_user_define(parser);break;
		case Echo: parse_echo(parser);break;
		default: break;
	}
	if(!(parser->tokens->TokenId == Eof)) goto redo_;
	return parser;
}

Parser_* parse(Parser_* parser)
{
	parser->tokens = next_token(parser->lexer);
	
	return check_value(parser);
}
