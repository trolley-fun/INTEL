************************************************
MyStack.h
************************************************
1) typedef struct Stk_element
{
	double value;
	Stk_element * link;
	int count;
};
************************************************
2) typedef Stk_element * Stack_t;
************************************************
3) Type of stack is Stack_t
************************************************
4) int Stk_check (Stack_t * stk0);
Function Stk_check return 0 if last element of stack is OK
and return 1 if it is BAD
************************************************
5) void Stk_print (Stack_t * stk0);
Function Stk_print check all elements of stack
and print information about stack
************************************************
6) void Stk_tester (Stack_t * stk0, char * func_name);
Function Stk_tester check last element of stack
and print information about stack if element is BAD,
func_name is name of function which called Stk_tester,
if element is BAD, Stk_tester break program
************************************************
7) void Stk_ctor (Stack_t * stk0);
Function Stk_ctor create correct stack
************************************************
8) void Stk_push (Stack_t * stk0, const double elem);
Function Stk_push add new element to stack
************************************************
9) double Stk_pop (Stack_t * stk0);
Function Stk_pop return last element of stack
and delete it from stack
************************************************
10) void Stk_dtor (Stack_t * stk0);
Function Stk_dtor delete stack
************************************************
