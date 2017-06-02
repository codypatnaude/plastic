#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <sstream>
#include <map>

enum var_type{
    var_str = -1,
    var_num = -2,
    var_binop = -3
};

/*
 * plastic variable type definitions
 */

class plsVariable{

    public:
        virtual const char * c_str() const = 0;
        virtual double num_val() const = 0;
        virtual int type() const = 0;

        plsVariable * operator+(plsVariable*);
        plsVariable * operator*(plsVariable*);
        plsVariable * operator/(plsVariable*);
        plsVariable * operator-(plsVariable*);
};

class plsString : public plsVariable{
    public: 
        const char * c_str() const;
        double num_val() const;
        int type() const;

        plsString(std::string x) : value(x) {};

        plsString(const char * x) : value(x) {};


    private:
        std::string value;

    
};

class plsNum : public plsVariable{
    public: 
        const char * c_str() const;
        double num_val() const;
        int type() const;

        //Constructors
        plsNum(int x) : value(x) {}
        plsNum(const char * x) : value(atof(x)) {}

        //Operators
        double operator+(const plsNum& n){
            return value + n.num_val();
        }

    private:
        double value;
        std::string dtos(double x) const;

    
};

class SymbolTable {
    public:
        void set(std::string key, plsVariable * v);
        plsVariable * get(std::string key);
    
    private:
        std::map<std::string, plsVariable*> symbolList;
};

#endif