#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int EMPTY = -1;
const int err_input = 1;
const int err_ptr = 2;
const int err_link = 3;
const int err_count = 4;

typedef struct Stack_t
{
	double val;
	struct Stack_t * add;
	int count;
};

int Stack_check (Stack_t ** stk0)
{	
	if (stk0 == 0)
		return err_input;
	if (* stk0 == 0)
		return err_ptr;

	if (( (* stk0)->add == 0 ) && ( (* stk0)->count > 0))
		return err_link;

	if ((* stk0)->count < EMPTY)
		return err_count;

	return 0;
}

void Stack_dump (Stack_t ** stk0)
{
	int err0 = 0;

	err0 = Stack_check (stk0);

	printf ("DIAGNOSTICS OF STACK\n");
	printf ("State: ");
	if (err0 == 0)
		printf ("OK\n");
	else
	{
		printf ("ERROR %02d: ", err0);
		switch (err0)
		{
		case err_input: printf ("NULL input pointer\n"); break;
		case err_ptr: printf ("NULL pointer to element of stack\n"); break;
		case err_link: printf ("wrong pointer to previous element of stack\n"); break;
		case err_count: printf ("counter is less than -1\n"); break;
		};
	}
}

void Stack_ctor (Stack_t ** stk0)
{
	if (stk0 == 0)
	{
		Stack_dump (stk0);
		assert (stk0 != 0);
	}

	* stk0 = (Stack_t *) calloc (1, sizeof (** stk0));
	
	(* stk0)->val = 0;
	(* stk0)->add = NULL;
	(* stk0)->count = EMPTY;

	if (Stack_check (stk0) != 0)
	{
		Stack_dump (stk0);
		assert (Stack_check (stk0) == 0);
	}
}

void Stack_push (Stack_t ** stk0, const double elem)
{
	Stack_t * stk1 = 0;
	
	if (Stack_check (stk0) != 0)
	{
		Stack_dump (stk0);
		assert (Stack_check (stk0) == 0);
	}
	
	if ((* stk0)->count == EMPTY)
	{
		(* stk0)->val = elem;
		(* stk0)->count++;
	}
	else
	{
		stk1 = (Stack_t *) calloc (1, sizeof (* stk1));
		stk1->val = elem;
		stk1->add = * stk0;
		stk1->count = (* stk0)->count + 1;
		* stk0 = stk1;
	}

	if (Stack_check (stk0) != 0)
	{
		Stack_dump (stk0);
		assert (Stack_check (stk0) == 0);
	}
}

double Stack_pop (Stack_t ** stk0)
{
	Stack_t * stk1 = 0;
	double elem = 0;

	if (Stack_check (stk0) != 0)
	{
		Stack_dump (stk0);
		assert (Stack_check (stk0) == 0);
	}

	if ((* stk0)->count == EMPTY)
	{
		printf ("ERROR: popping is unavailable\n");
		Stack_dump (stk0);
		assert ((* stk0)->count != EMPTY);
	}
	
	stk1 = * stk0;

	elem = (* stk0)->val;
	
	if ((* stk0)->count == 0)
	{
		(* stk0)->val = 0;
		(* stk0)->count = EMPTY;
	}
	
	if ((* stk0)->count > 0)
	{
		* stk0 = stk1->add;
		free(stk1);
	}

	if (Stack_check (stk0) != 0)
	{
		Stack_dump (stk0);
		assert (Stack_check (stk0) == 0);
	}

	return elem;
}

void Stack_dtor (Stack_t ** stk0)
{
	Stack_t * stk1 = 0;

	if (Stack_check (stk0) != 0)
	{
		Stack_dump (stk0);
		assert (Stack_check (stk0) == 0);
	}

	while ((* stk0)->add != NULL)
	{
		stk1 = * stk0;
		* stk0 = (* stk0)->add;
		free (stk1);
	}
	
	free (* stk0);
}
