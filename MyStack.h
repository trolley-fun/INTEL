//Tolya Grishin

//============================================================

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//============================================================
//count of empty stack

int const EMPTY = -2;

//============================================================
//type of element of stack

typedef struct Stk_element
{
	double value;
	Stk_element * link;
	int count;
};

//============================================================
//type of stack

typedef Stk_element * Stack_t;

//============================================================
//function Stk_check return 0 if last element of stack is OK
//and return 1 if it is BAD

int Stk_check (Stack_t * stk0)
{
	int GOOD = 0, BAD = 1;

	if (EMPTY != -2)
		return BAD;
	
	if (!stk0)
		return BAD;
	
	if (!(* stk0))
		return BAD;

	if ( ((* stk0)->count > 0) && ((* stk0)->link == 0) ||
		 ((* stk0)->count == 0) && ((* stk0)->link != 0) ||
		 ((* stk0)->count == EMPTY) && ((* stk0)->link != 0) ||
		 ((* stk0)->count == EMPTY) && ((* stk0)->value != 0) )
			return BAD;

	if ( ((* stk0)->count < 0) && ((* stk0)->count != EMPTY) )
		return BAD;

	return GOOD;
}

//============================================================
//function Stk_print check all elements of stack
//and print information about stack

void Stk_print (Stack_t * stk0)
{
	int i = 0, stk_sz = 0, err = 0, BAD = 0, GOOD = 1;
	Stack_t stk1 = 0;
	
	printf ("==============================\n");
	printf ("DIAGNOSTICS OF STACK");

	if (!stk0)
	{
		printf ("\n");
		printf ("------------------------------\n");
		printf ("ERROR 01: function Stk_print received NULL pointer\n");
		printf ("------------------------------\n");
		printf ("Result: stack is BAD\n");
		printf ("==============================\n");
		return;
	}

	printf (", address = [%p]\n", stk0);

	if (EMPTY != -2)
	{
		printf ("------------------------------\n");
		printf ("ERROR 02: constant EMPTY was changed\n");
		printf ("EMPTY = %d but must be EMPTY = -2", EMPTY);
		printf ("------------------------------\n");
		printf ("Result: stack is BAD\n");
		printf ("==============================\n");
		return;
	}

	stk1 = * stk0;

	if (!stk1)
	{
		printf ("------------------------------\n");
		printf ("ERROR 03: NULL pointer to element of stack\n");
		printf ("------------------------------\n");
		printf ("Result: stack is BAD\n");
		printf ("==============================\n");
		return;
	}

	stk_sz = stk1->count;
	
	err = GOOD;
	for (i = stk_sz; ; i--)
	{
		printf ("------------------------------\n");
		if (i != EMPTY)
			printf ("Element [%d], ", i);
		else
			printf ("Element [EMPTY], ");
		printf ("address = [%p]\n", stk1);
		printf ("value = %lg\n", stk1->value);
		printf ("link = [%p]\n", stk1->link);
		printf ("count = %d\n", stk1->count);

		if ((stk1->count > 0) && (stk1->link == NULL))
		{
			printf ("ERROR 04: wrong count or link\n");
			printf ("nummer of element is not 0 but link is NULL\n");
			printf ("Conclusion: element of stack is BAD\n");
			err = BAD;
			break;
		}

		if ((stk1->count == 0) && (stk1->link != NULL))
		{
			printf ("ERROR 04: wrong count or link\n");
			printf ("nummer of element is 0 but link is not NULL\n");
			printf ("Conclusion: element of stack is BAD\n");
			err = BAD;
			break;
		}

		if ((stk1->count == EMPTY) && ((stk1->link != NULL) || (stk1->value != 0)))
		{
			printf ("ERROR 04: wrong count or link\n");
			if (stk1->link != NULL)
				printf ("stack is EMPTY but link is not NULL\n");
			if (stk1->value != 0)
				printf ("stack is EMPTY but value is not 0\n");
			printf ("Conclusion: element of stack is BAD\n");
			err = BAD;
			break;
		}

		if ((stk1->count < 0) && (stk1->count != EMPTY))
		{
			printf ("ERROR 05: wrong count\n");
			printf ("nummer of element is less than 0\n");
			printf ("Conclusion: element of stack is BAD\n");
			err = BAD;
			break;
		}

		if (stk1->count != i)
		{
			printf ("ERROR 05: wrong count\n");
			printf ("count of this element is %d ", stk1->count);
			printf ("but count of next element is %d\n", i+1);
			printf ("Conclusion: element of stack is BAD\n");
			err = BAD;
			break;
		}

		printf ("Conclusion: element of stack is OK\n");

		if ((i == 0) || (i == EMPTY))
			break;
		else
			stk1 = stk1->link;
	}

	printf ("------------------------------\n");
	if (err == BAD)
		printf ("Result: stack is BAD\n");
	else
		printf ("Result: stack is OK\n");
	printf ("==============================\n");
}

//============================================================
//function Stk_tester check last element of stack
//and print information about stack if element is BAD,
//if element is BAD Stk_tester break program

void Stk_tester (Stack_t * stk0, char * func_name)
{
	if (Stk_check (stk0) != 0)
	{
		printf ("==============================\n");
		printf ("ERROR in function %s: stack is wrong\n", func_name);
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}
}

//============================================================
//function Stk_ctor create correct stack

void Stk_ctor (Stack_t * stk0)
{
	if (!stk0)
	{
		printf ("==============================\n");
		printf ("ERROR 02: function Stack_ctor recieved NULL pointer\n");
		printf ("==============================\n");
		assert (0);
	}

	* stk0 = (Stack_t) calloc (1, sizeof (Stk_element));
	(* stk0)->value = 0;
	(* stk0)->link = NULL;
	(* stk0)->count = EMPTY;

	Stk_tester (stk0, "Stk_ctor");
}

//============================================================
//function Stk_push add new element to stack

void Stk_push (Stack_t * stk0, const double elem)
{
	Stack_t stk1 = 0;
	
	Stk_tester (stk0, "Stk_push");

	if ((* stk0)->count == EMPTY)
	{
		(* stk0)->value = elem;
		(* stk0)->count = 0;
	}
	
	else
	{
		stk1 = (Stack_t) calloc (1, sizeof (Stk_element));
		
		stk1->value = elem;
		stk1->link = * stk0;
		stk1->count = (* stk0)->count + 1;

		* stk0 = stk1;
	}

	Stk_tester (stk0, "Stk_push");
}

//============================================================
//function Stk_pop return last element of stack
//and delete it from stack

double Stk_pop (Stack_t * stk0)
{
	Stack_t stk1 = 0;
	double elem = 0;

	Stk_tester (stk0, "Stk_pop");
	stk1 = * stk0;

	if (stk1->count == EMPTY)
	{
		printf ("==============================\n");
		printf ("ERROR 06: pop is impossible\n");
		printf ("stack is EMPTY so there are no elements to pop\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}

	if (stk1->count == 0)
	{
		elem = stk1->value;
		stk1->value = 0;
		stk1->count = EMPTY;
	}

	else
	{
		* stk0 = stk1->link;
		elem = stk1->value;
		free (stk1);
	}

	Stk_tester (stk0, "Stk_pop");

	return elem;
}

//============================================================
//function Stk_dtor delete stack

void Stk_dtor (Stack_t * stk0)
{
	Stack_t stk1 = 0;
	int stk_sz = 0, i = 0;

	if (!stk0)
	{
		printf ("==============================\n");
		printf ("ERROR 02: function Stack_dtor recieved NULL pointer\n");
		printf ("==============================\n");
		assert (0);
	}

	if (* stk0 != NULL)
	{
		stk_sz = (* stk0)->count;

		for (i = stk_sz; (* stk0 != NULL) && (i >= EMPTY); i--)
		{
			stk1 = * stk0;

			if ((stk1->count > 0) && (stk1->link == NULL))
			{
				printf ("==============================\n");
				printf ("Function Stk_dtor: ERROR 04: wrong count or link\n");
				printf ("nummer of element is not 0 but link is NULL\n");
				printf ("==============================\n");
				Stk_print (stk0);
				assert (0);
			}

			* stk0 = (* stk0)->link;
			free (stk1);
		}
	}

	if (* stk0 != NULL)
	{
		printf ("==============================\n");
		printf ("Function Stk_dtor: ERROR: stack was not distructed\n");
		printf ("stack was distructed but pointer is not NULL\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}
}

//============================================================
