#include"stack.h"
#include<iostream>

using namespace std;
Stack::Stack() {
	top = NULL; //Make sure the top of stack pointer points to NULL at construction.
	//cout << "Stack Initialized" << endl;
}

Stack::~Stack() {
	int dummyOne, dummyTwo;
	while (!isEmpty())
		pop(dummyOne, dummyTwo); //While stack is not empty, pop until it is. 
}

void Stack::push(int x, int y) {
	node* temp = new node;
	temp->x = x; //Data written to new node
	temp->y = y;
	temp->next = top; //new node points to old top of stack.
	top = temp;       //point top to the new top of stack.
}

void Stack::pop(int& x, int& y) {
	if (!isEmpty()) {
		x = top->x;
		y = top->y;
		node* toDelete = top;
		top = toDelete->next;
		delete toDelete;
	}
	else {
		//Do nothing
		//cout << "Nothing to pop from stack" << endl;
	}
}

bool Stack::isEmpty() {
	return(top == NULL); //If the top pointer is NULL, then we return true.
}
