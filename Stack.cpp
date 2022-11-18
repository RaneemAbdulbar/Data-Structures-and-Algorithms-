#include "Stack.h"
#include <stddef.h>

using namespace std;

Stack :: Stack(){
  head = NULL;
}

Stack :: ~Stack(){
  delete head;
}

    
void Stack :: push(StackItem * item){
 
 if (item->isOperator) 
    {
		StackItem* node = new StackItem(true, item -> op);
		node -> op = item -> op;
		node -> next = head;
		head = node;
	}
	else
	{
		StackItem* node = new StackItem(false, item -> op);
		node -> n = item -> n;
		node -> next = head;
		head = node;
	}


}

    
StackItem* Stack :: pop(){
    StackItem * temp = head;

if (head == NULL){ 
       cout << "\n The Stack is empty.";
       return 0;
}
else{
  
    head = head->next;
    return temp;
    delete temp;
}

}

StackItem* Stack :: top(){
    if (!isEmpty())
        return head; 
    else 
        return 0;
}

bool Stack :: isEmpty(){
    if (head== NULL){
        return true;
    }
    else{
        return false;
    }
    
}