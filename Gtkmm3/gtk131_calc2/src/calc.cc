#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "calc.hh"

static int pos = 0;

void calc_reset(){
    pos = 0;
}

double calc_factor_value(const char * factor){
    double result1 = 0.0, result2 = 0.0, final_result = 0.0;
    char c = factor[pos];
    if( c == '('){          // if expression has '(', calculate the expression in the '()'
        pos++;              // Pass the '('
        result1 = calc_expression_value(factor);
        pos++;              // Pass the ')'
    }else{
        while(isdigit(c)){  // Get the number to calculate
            result1 = 10 * result1 + c - '0';
            pos++;
            c = factor[pos];
        }
        if(c == '.'){                   // Get number between 0 to 1
            pos++;                      // Pass the '.'
            c = factor[pos];
            while(isdigit(c)){
                result2 = 0.1 * result2 + (c - '0') * 0.1;
                pos++;
                c = factor[pos];
            }
        }
        final_result = result1 + result2;
        if(c == '%'){
            final_result /= 100.0;      // Pass the '%'
            pos++;
        }
    }
    return final_result;
}

double calc_term_value(const char * term){
    double result = calc_factor_value(term);   // Get the first number
    double value = 0.0;
    while(pos < strlen(term)){
        //pos++;    // Calc the multiplication and divide
        char op = term[pos];
        if(op == '^' || op == '*' || op == '/'){
            switch (op)
            {
            case '^':
                pos++;
                value = calc_factor_value(term);    // Pow
                result = pow(result,value);
                break;
            case '*':
                pos++;
                value = calc_factor_value(term);    // Subb
                result *= value;
                break;
            case '/':
                pos++;
                value = calc_factor_value(term);    // Get another value
                result /= value;
                break;
            }
            break;
        }else{
            break;
        }
    }
    return result;
}

double calc_expression_value(const char * expression){
    double result = calc_term_value(expression);   // Calc the result of expression
    //bool more = true;
    while(pos < strlen(expression)){
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
