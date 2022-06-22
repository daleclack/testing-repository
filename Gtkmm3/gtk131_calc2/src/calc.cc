#include <iostream>
#include <cstdlib>
#include <cstring>
#include "calc.hh"

static int pos = 0;

void calc_reset(){
    pos = 0;
}

double calc_factor_value(const char * factor){
    double result = 0;
    char c = factor[pos];
    if( c == '('){          // if expression has '(', calculate the expression in the '()'
        pos++;
        result = calc_expression_value(factor);
        pos++;
    }else{
        while(isdigit(c)){  // Get the number to calculate
            result = 10 * result + c - '0';
            pos++;
            c = factor[pos];
        }
    }
    return result;
}

double calc_term_value(const char * term){
    double result = calc_factor_value(term);   // Get the first number
    while(true){
        //pos++;    // Calc the multiplication and divide
        char op = term[pos];
        if(op == '*' || op == '/'){
            pos++;
            double value = calc_factor_value(term);    // Get another value
            if(op == '*') result *= value;
            else result /= value;
        }else{
            break;
        }
    }
    return result;
}

double calc_expression_value(const char * expression){
    double result = calc_term_value(expression);   // Calc the result of expression
    //bool more = true;
    while(true){
        char op = expression[pos];
        if(op == '+' || op == '-'){         // Calculate for add and subb
            pos++;
            double value = calc_term_value(expression);
            if( op == '+') result += value;
            else result -= value;
        }else{
            break;
        }
    }
    return result;
}
