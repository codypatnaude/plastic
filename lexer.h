
#ifndef LEXER_H
#define LEXER_H LEXER_H


#include <stdio.h>
#include <string>
#include <memory>
#include <exception>

enum tok_type{
    tok_invalid     = 0,
    tok_binop       = -1,
    tok_num         = -2,
    tok_paren       = -3,
    tok_eof         = -4,
    tok_identifier  = -5,
    tok_eol         = -6
};

class Lexer {
    FILE * pFile;

    public:
        double numVal;
        std::string stringVal;
        tok_type tokType;
        int lineNumber = 1;
        void SetFile(FILE * file);
        int GetTok();
        char GetChar();
        int GetPos();
        void GoToPos(int);

    private:
        char next_char = ' ';
};

#endif