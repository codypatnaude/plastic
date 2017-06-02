#include <string.h>
#include "lexer.h"
#include "storage.h"

class Parser{
    public:
        Parser(Lexer *Lex) : lex(Lex) {}
        void Parse();
    private:
        Lexer *lex;
        plsVariable * evaluate_expression(SymbolTable *symbols);
};

enum node_type{
    node_num = -1,
    node_binop = -2
};

class ExpressionNode{
    public:
        ExpressionNode(plsVariable*, node_type);
        virtual ~ExpressionNode();
        node_type type;
        plsVariable * value;
        ExpressionNode   *leftChild  = nullptr;
        ExpressionNode   *rightChild = nullptr;
        ExpressionNode   *parent     = nullptr;
        plsVariable * CalculateValue();
        int getWeight();
};

class ExpressionTree{
    public:
        ExpressionTree();
        virtual ~ExpressionTree();
        void AddNode(ExpressionNode*);
        plsVariable * Solve();

    private:
        ExpressionNode * root = nullptr;
};