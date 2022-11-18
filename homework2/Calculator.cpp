#include "Calculator.h"


Calculator::Calculator(string infixExp) 
{
	// reverse string 
	infixExpression = infixExp;
	string infixExprvs = infixExpression;
	reverse(infixExprvs.begin(), infixExprvs.end());
	infixExprvs += " ;";
	
	stack = new Stack();

	//change "(" to ")" and vise versa
	for (int i=0; i<infixExprvs.size(); i++) 
	{
		if (infixExprvs[i] == '(')
			infixExprvs[i] = ')';
		else if (infixExprvs[i] == ')')
			infixExprvs[i] = '(';
	}

	istringstream iss(infixExprvs);
	string element;
	string prefixExp;
	iss >> element;
	iss >> element;
	while (element.compare(";") != 0)
	{
		StackItem* item = new StackItem(element);
		if (!(item->isOperator))
			prefixExpression += element + " ";	

		else if (item->isOperator)
		{
			if (stack->isEmpty())
				stack->push(item);
			else
			{
				if (item->op == 0)
					stack->push(item);
				else if (item->op == 1) 
				{
					while (!(stack->isEmpty()) && (stack->top()->op != 0))
					{
							StackItem* temp_stackItem = stack->pop();
							prefixExpression += temp_stackItem->toString() + " ";
							delete temp_stackItem;
					}
					stack->pop();
				}
				else if(item->op == 4 || item->op == 5){
					// there is no case where we need to care about popping when the incoming operator is * /
					stack->push(item);
				}
				else if (item->op == 3 || item->op == 2){
					while (!(stack->isEmpty()) && (stack->top()->op != 0) )
					{
							StackItem* temp_stackItem = stack->pop();
							prefixExpression += temp_stackItem->toString() + " ";
							delete temp_stackItem;
						
					}
					stack->push(item);
				}
			}
		}		
		iss >> element;
	}
	if (!(stack->isEmpty()))
	{
		while (!(stack->isEmpty()))
		{
			StackItem* temp_stackItem = stack->pop();
			prefixExpression += temp_stackItem->toString() + " ";
			delete temp_stackItem;
		}
	}
	reverse(prefixExpression.begin(), prefixExpression.end()); 
	prefixExpression += " ;";
}

int Calculator::calculate() 
{
	
   
    string reversedPrefix = this->prefixExpression;
    string calcExpression;
    string elem1;
    istringstream iss1(reversedPrefix);
    iss1 >> elem1;
	//pushing the elements onto the string 
    while(elem1.compare(";") != 0){
        StackItem *item = new StackItem(elem1);
        stack->push(item);
        iss1 >> elem1;
    }
	//getting them out of the stack onto the string 
    while(!stack->isEmpty()){
        calcExpression += stack->top()->toString() +" ";
        stack->pop();
    }
    calcExpression += ";";
	

    //here we calculate the result
    string elem2;
    istringstream iss(calcExpression);
    iss >> elem2;
    while(elem2.compare(";") != 0){
        StackItem *stack1 = new StackItem(elem2);
        if(!stack1->isOperator){
            stack->push(stack1);
        }
        else{
            StackItem *a = stack->pop();
            StackItem *b = stack->pop();

            switch (stack1->op)
            {
            case (2):{
                StackItem *minusOp = new StackItem(to_string(a->n - b->n));
                stack->push(minusOp);
                break;
                }
            case (3):{
                StackItem *plusOp = new StackItem(to_string(a->n + b->n));
                stack->push(plusOp);
                break;
                }
            case (4):{
                StackItem *divideOp = new StackItem(to_string(a->n / b->n));
                stack->push(divideOp);
                break;
                }
            case (5):{
                StackItem *multiplyOp = new StackItem(to_string(a->n * b->n));
                stack->push(multiplyOp);
                break;
                }
            }
            delete a;
            delete b;
        }
        iss >> elem2;
    }
    int result = stack->top()->n;
    
    while(!stack->isEmpty()){
        stack->pop();
    }
    return result;
}
string Calculator::getPrefix() { return prefixExpression; }
Calculator :: ~Calculator() { delete stack; }