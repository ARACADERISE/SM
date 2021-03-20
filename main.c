#include <stdio.h>
#include "src/read_file.h"
#include "src/lexer.h"
#include "src/parser.h"

int main(int args, char* argv[])
{
        if(args < 2)
        {
                fprintf(stderr,"Expected a file as a argument.\n\t./main.o filename.\n");
                exit(EXIT_FAILURE);
        }
        char* src = read_file(argv[1]);
        Lexer_* lexer = init_lexer(src);
        Parser_* parser = init_parser(lexer);
        parser = parse(parser);
        return 0;
}
