#include "lexer.h"

void Lexer::SetFile(FILE *file){
    
    pFile = file;

}

char Lexer::GetChar(){
    
    char last_char = this->next_char; 
    this->next_char = fgetc(this->pFile);

    if(last_char == '\n'){
        ++this->lineNumber;
    }
    return last_char;
}

int Lexer::GetPos(){
    return ftell(this->pFile);
}

void Lexer::GoToPos(int pos){
    fseek(this->pFile, pos, SEEK_SET);
}

int Lexer::GetTok(){
    char c = ' ';

    this->tokType = tok_invalid; 
    
    //skip white space
    do{
        
        c = this->GetChar();
    }while(isspace(c) && c != EOF);
    

    if(c == EOF){
        this->tokType = tok_eof;
    
    }else if(isdigit(c) || c == '.'){
        std::string numstr;
        int decimal = 0;
        
        while(1){
            numstr += c;
            if(c == '.'){
                if(decimal > 0){
                    throw std::logic_error("Invalid number format");
                }
                ++decimal;
            }

            if(isdigit(this->next_char) || this->next_char == '.'){
                c = this->GetChar();
            }else{
                break;
            }
        }

        this->numVal = stod(numstr);
        this->tokType = tok_num;
    
    }else if(isalnum(c)){
        std::string str;
        while(1){
            str += c;

            if(isalnum(this->next_char)){
                c = this->GetChar();
            }else{
                break;
            }
        }
        
        /*do{
            str += c;

            c = this->GetChar();
        }while(isalnum(c));*/

        this->stringVal = str;
        this->tokType = tok_identifier;
    
    }else if(c == '(' || c == ')'){
        this->stringVal = c;
        this->tokType = tok_paren;
    
    }else if(c == '#'){
        do{
            c = this->GetChar();
        }while(c != EOF && c != '\r' && c != '\n');
        return this->GetTok();
    
    }else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '='){
        this->stringVal = c;
        this->tokType = tok_binop;
    
    }else if(c == ';'){
        this->stringVal = c;
        this->tokType = tok_eol;
    }

    
    return this->tokType;
}