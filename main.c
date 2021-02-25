#include <stdio.h>
#include "src/read_file.h"
#include "src/lexer.h"
#include "src/parser.h"

int main()
{
	char* src = read_file("ex.sm");
	Lexer_* lexer = init_lexer(src);
	Parser_* parser = init_parser(lexer);
	parser = parse(parser);
	return 0;
}
