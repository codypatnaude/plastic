#include <stdio.h>
#include <string>
#include "lexer.h"
#include "storage.h"
#include "parser.h"

int main(int argc, char *argv[]){

    if(argc < 1){
        printf("no file specified\n");
        return 0;
    }

    const char * filename =  argv[1];

    printf("opening file %s\n", filename);

    FILE * pFile = fopen(filename, "r");

    if(pFile == NULL){
        printf("could not open file %s\n", filename);
        return 0;
    }

    Lexer *lex = new Lexer();
    lex->SetFile(pFile);

    Parser *parser = new Parser(lex);
    parser->Parse();
    

    fclose(pFile);

    return 0;
}