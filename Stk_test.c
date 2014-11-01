#include <stdio.h>
#include <stdlib.h>
#include "MyStack.h"


int main ()
{
	Stack_t x = 0;

	Stk_ctor (&x);
	Stk_push (&x, 99);
	Stk_push (&x, -91);
	Stk_push (&x, 1.28);
	Stk_print (&x);
	printf ("%lg\n", Stk_pop(&x));
	printf ("%lg\n", Stk_pop(&x));
	printf ("%lg\n", Stk_pop(&x));
	//printf ("%lg\n", Stk_pop(&x));
	//Stk_print (&x);
	Stk_dtor (&x);

	system ("PAUSE");
	return 0;
}
