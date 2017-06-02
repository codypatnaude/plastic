
#include "storage.h"

/*
 * Symbol table
 */
void SymbolTable::set(std::string key, plsVariable * v){
    printf("STORING VAR: %s : %s\n", key.c_str(), v->c_str());
    symbolList[key] = v;
}

plsVariable * SymbolTable::get(std::string key){
    printf("accessing variable: %s\n", key.c_str());
    //plsVariable *tmp =  symbolList[key];
    std::map<std::string, plsVariable*>::iterator it;
    it = symbolList.find(key.c_str());
    if(it == symbolList.end()){
        printf("OMG THAT VAR DOESN'T EXIST\n");
        throw std::logic_error("Unexpected identifier");
    }
    plsVariable *tmp =  symbolList[key];
    printf("Variable exists\n");
    printf("VARIABLE: %s\n", tmp->c_str());
    return tmp;
}

/*
 * plastic variable type definitions
 */

/*
 * OPERATORS
 */
plsVariable * plsVariable::operator+(plsVariable* RHS){
    if(this->type() == var_str){
        std::string LHS = this->c_str();
        plsString * ret = new plsString(LHS + RHS->c_str());
        return ret;

    }else if(this->type() == var_num){
        plsNum * ret = new plsNum(this->num_val() + RHS->num_val());
        return ret;
        
    }    
}

plsVariable * plsVariable::operator-(plsVariable* RHS){
    if(this->type() == var_num){
        printf("Doing subtraction: %f - %f\n", this->num_val(), RHS->num_val());
        plsNum * ret = new plsNum(this->num_val() - RHS->num_val());
        return ret;    
    }else{
        throw std::logic_error("Invalid operation");
    }
}

plsVariable * plsVariable::operator*(plsVariable* RHS){
    if(this->type() == var_num){
        plsNum * ret = new plsNum(this->num_val() * RHS->num_val());
        return ret;    
    }else{
        throw std::logic_error("Invalid operation");
    }
}

plsVariable * plsVariable::operator/(plsVariable* RHS){
    if(this->type() == var_num){
        plsNum * ret = new plsNum(this->num_val() / RHS->num_val());
        return ret;    
    }else{
        throw std::logic_error("Invalid operation");
    }
}

/*
 * STRING
 */
const char * plsString::c_str() const{
    return value.c_str();
}

double plsString::num_val() const{
    return atof(value.c_str());
}

int plsString::type() const{
    return var_str;
}

/*
 * NUMBER
 */

std::string plsNum::dtos(double x) const{
    std::ostringstream strs;
    strs << x;
    std::string str = strs.str();
    return str;
}

const char * plsNum::c_str() const{
    return dtos(value).c_str();
}

double plsNum::num_val() const{
    return value;
}

int plsNum::type() const{
    return var_num;
}
