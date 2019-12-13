#ifndef STACK_H
#define STACK_H

//Create a node struct for stack
struct node
{
	int x;
	int y;
	node* next;
};

//Create a class for stack
class Stack {
public:
	Stack();//CONSTRUCTOR
	~Stack();//DECONSTRUCTOR
	void push(int x, int y); //Push coords onto stack
	void pop(int& x, int& y); //Pop coords off of stack
	bool isEmpty();
private:
	node* top;
};

#endif // !STACK_H