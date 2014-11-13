#include <stdio.h>
#include <stdlib.h>
#include "MyAssembler.h"

int main ()
{
	Code_t MyCode;
	Stack_t stk = 0;

	Translator ("input.txt", "output.txt");
	MyCode = Code_prepare ("output.txt");
	Prog_maker0 (MyCode, &stk);

	printf ("%lg\n", Stk_pop (&stk));

	//Stk_ctor (&stk);
	//Stk_push (&stk, 7);
	//Stk_push (&stk, 4);
	//Stk_add (&stk);
	//printf ("%lg\n", Stk_pop (&stk));
	system ("PAUSE");

	return 0;
}
