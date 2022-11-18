#ifndef _Calculator_
#define _Calculator_

#include "Stack.h"

#include<iostream>
#include <string>
#include <algorithm>

using namespace std;

class Calculator
{
    private:
        Stack *stack;
        string prefixExpression;
        string infixExpression; 
    public: 
        Calculator(string);
        ~Calculator();
        string getPrefix();
        int calculate();
};

#endif
