#include "parser.h"

void Parser::Parse(){
    /*
     * MAIN PARSE LOOP
     */
    printf("Beginning parse\n");

    SymbolTable * symbols = new SymbolTable();

    std::string last_identifier;
    var_type last_type;

    while(1){
        int tok_type = lex->GetTok();
        
        if(tok_type==tok_eof){
            break;
            
        }else if(tok_type==tok_identifier){
            printf("SETTING LAST ID: %s\n", lex->stringVal.c_str());
            last_identifier = lex->stringVal;
            
        //execute function
        }else if(tok_type==tok_paren){
        
        //set variable
        }else if(tok_type==tok_binop){
            if(lex->stringVal == "="){
                plsVariable * RHE = evaluate_expression(symbols);
                symbols->set(last_identifier.c_str(), RHE);
            }
            printf("BINOP\n");
        }

    }
}

plsVariable * Parser::evaluate_expression(SymbolTable *symbols){
    
    printf("EVALUATE EXPRESSION\n");
    bool parseParen = false;

    if(lex->tokType == tok_paren){
        parseParen = true;
    }

    int tok_type = lex->GetTok();

    ExpressionTree tree;
    
    while(1){

        if(tok_type == tok_eol || tok_type == tok_eof){
            if(parseParen){
                std::string error = "Unexpected end of line";
                error += std::to_string(lex->lineNumber);
                throw std::logic_error(error.c_str());
            }

            break;
        }

        plsVariable * var = nullptr;
        node_type ntype = node_num;

        if(tok_type == tok_paren){
            if(lex->stringVal == ")"){
                if(!parseParen){
                    throw std::logic_error("Unexpected token )");
                }else{
                    break;
                }
            }else{ // Token is (
                var = this->evaluate_expression(symbols);
                ntype = node_num;
            }
        }else if(tok_type==tok_num){
            var = new plsNum(lex->numVal);
            ntype = node_num;
        }
        else if(tok_type==tok_identifier){
            std::string varName = lex->stringVal;
            var = symbols->get(lex->stringVal);
            ntype = node_num;
        }
        else if(tok_type==tok_binop){
            var = new plsString(lex->stringVal);
            ntype = node_binop;
        }

        tree.AddNode(new ExpressionNode(var, ntype));
        tok_type = lex->GetTok();
    }

    return tree.Solve();

}

ExpressionTree::ExpressionTree(){};
ExpressionTree::~ExpressionTree(){
    delete this->root;
};

void ExpressionTree::AddNode(ExpressionNode *newNode){
    
    
    printf("ADDING NODE: %s\n", newNode->value->c_str());

    if(root == nullptr){
        printf("\tNo root, taking root: %s\n", newNode->value->c_str());
        root = newNode;
        return;
    }

    ExpressionNode * treeNode = root;

    while(1){
        printf("\tComparing: %s\n", treeNode->value->c_str());

        if(newNode->getWeight() <= treeNode->getWeight()){

            printf("\tTaking root\n");
            
            
            newNode->parent = treeNode->parent;

            if(newNode->parent != nullptr){
                newNode->parent->rightChild = newNode;
            }else{
                this->root = newNode;
            }

            treeNode->parent = newNode;
            newNode->leftChild = treeNode;

            break;
        }else{
            
            if(treeNode->rightChild == nullptr){
                printf("\tTaking right child\n");
                newNode->parent = treeNode;
                treeNode->rightChild = newNode;
                break;
            }else{
                treeNode = treeNode->rightChild;
                continue;
            }
        }

        break;
    }
    
}

plsVariable * ExpressionTree::Solve(){
    return this->root->CalculateValue();
}

plsVariable * ExpressionNode::CalculateValue(){
    if(type == node_num){
        plsNum *n  = new plsNum(value->num_val());
        return n;
    }else if(type == node_binop){
        if(leftChild == nullptr || rightChild == nullptr){
            throw std::logic_error("NULL LHE OR RHE");
        }

        plsVariable * LHE = leftChild->CalculateValue();
        plsVariable * RHE = rightChild->CalculateValue();

        plsVariable * ret = nullptr;

        if(strcmp(this->value->c_str(), "+")  == 0){
            ret = *LHE + RHE;
        }else if(strcmp(this->value->c_str(), "-") == 0){
            ret = *LHE - RHE;
        }else if(strcmp(this->value->c_str(), "/") == 0){
            ret = *LHE / RHE;
        }else if(strcmp(this->value->c_str(), "*") == 0){
            ret = *LHE * RHE;
        }
        

        return ret;
    }

}

int ExpressionNode::getWeight(){
    std::map<char, int> binop_priority;
    binop_priority['+'] = 20;
    binop_priority['-'] = 20;
    binop_priority['*'] = 40;
    binop_priority['/'] = 40;
    binop_priority['#'] = 1000;

    int weight = 0;

    if(type == node_num){
        weight = binop_priority['#'];
    }else if(type=node_binop){
        weight = binop_priority[*value->c_str()];
    }

    return weight;
}

ExpressionNode::ExpressionNode(plsVariable* var, node_type type){
    this->type = type;
    this->value = var;
}

ExpressionNode::~ExpressionNode(){
    if(this->rightChild != nullptr){
        delete this->rightChild;
    }

    if(this->leftChild != nullptr){
        delete this->leftChild;
    }

    delete this->value;

    return;
}