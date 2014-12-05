//Tolya Grishin

//============================================================

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//============================================================
//type of element of stack

typedef struct Stk_element
{
	double value;
	Stk_element * link;				//pointer to previous element
};

//============================================================
//type of stack

typedef struct Stack_t
{
	Stk_element * head;				//pointer to last element
	int count;						//count of elements in stack
	double AX;						//registers
	double BX;
	double CX;
};

//============================================================
//function Stk_check return 0 if last element of stack is OK
//and return 1 if it is BAD

int Stk_check (Stack_t * stk0)
{
	int GOOD = 0, BAD = 1;
	
	if (stk0 == NULL)
		return BAD;
	
	if (stk0->count < 0)
		return BAD;

	if ((stk0->count == 0) && (stk0->head != NULL) ||
		(stk0->count >  0) && (stk0->head == NULL))
		return BAD;

	if ((stk0->count == 1) && (stk0->head->link != NULL) || 
		(stk0->count >  1) && (stk0->head->link == NULL))
		return BAD;

	return GOOD;
}

//============================================================
//function Stk_print check all elements of stack
//and print information about stack

void Stk_print (Stack_t * stk0)
{
	int i = 0, stk_sz = 0, err = 0, BAD = 0, GOOD = 1;
	Stk_element * stk1 = NULL;
	
	printf ("==============================\n");
	printf ("DIAGNOSTICS OF STACK\n");

	if (stk0 == NULL)
	{
		printf ("\n");
		printf ("------------------------------\n");
		printf ("ERROR: function Stk_print received NULL pointer\n");
		printf ("------------------------------\n");
		printf ("Result: stack is BAD\n");
		printf ("==============================\n");
		return;
	}

	printf ("address = [%p], count = %d\n", stk0, stk0->count);

	if (stk0->count < 0)
	{
		printf ("------------------------------\n");
		printf ("ERROR: count of elements in stack is less than zero\n");
		printf ("------------------------------\n");
		printf ("Result: stack is BAD\n");
		printf ("==============================\n");
		return;
	}

	if ((stk0->count == 0) && (stk0->head != NULL))
	{
		printf ("------------------------------\n");
		printf ("ERROR: count is 0 but there are some elements in stack\n");
		printf ("------------------------------\n");
		printf ("Result: stack is BAD\n");
		printf ("==============================\n");
		return;
	}

	if ((stk0->count > 0) && (stk0->head == NULL))
	{
		printf ("------------------------------\n");
		printf ("ERROR: count is more than 0 but trere aren't any elements in stack\n");
		printf ("------------------------------\n");
		printf ("Result: stack is BAD\n");
		printf ("==============================\n");
		return;
	}

	stk_sz = stk0->count;
	stk1 = stk0->head;
	err = GOOD;
	
	for (i = stk_sz-1; (i >= 0) && (stk1 != NULL); i--)
	{
		printf ("------------------------------\n");
		printf ("Element [%d], ", i);
		printf ("address = [%p]\n", stk1);
		printf ("value = %lg\n", stk1->value);
		printf ("link = [%p]\n", stk1->link);

		if ((i == 0) && (stk1->link != NULL))
		{
			printf ("ERROR: wrong count or link\n");
			printf ("nummer of element is 0 but link is not NULL\n");
			printf ("Conclusion: element of stack is BAD\n");
			err = BAD;
			break;
		}

		if ((i != 0) && (stk1->link == NULL))
		{
			printf ("ERROR: wrong count or link\n");
			printf ("nummer of element is not 0 but link is NULL\n");
			printf ("Conclusion: element of stack is BAD\n");
			err = BAD;
			break;
		}

		printf ("Conclusion: element of stack is OK\n");

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

void Stk_tester (Stack_t * stk0, const char * func_name)
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

Stack_t * Stk_ctor ()
{
	Stack_t * stk0 = NULL;

	stk0 = (Stack_t *) calloc (1, sizeof (Stack_t));
	
	stk0->head = NULL;
	stk0->count = 0;
	stk0->AX = 0;
	stk0->BX = 0;
	stk0->CX = 0;

	Stk_tester (stk0, "Stk_ctor");

	return stk0;
}

//============================================================
//function Stk_push add new element to stack

void Stk_push (Stack_t * stk0, const double elem)
{
	Stk_element * stk1 = NULL;
	
	Stk_tester (stk0, "Stk_push");

	stk1 = (Stk_element *) calloc (1, sizeof (Stk_element));
	
	stk1->value = elem;
	stk1->link = stk0->head;

	stk0->head = stk1;
	stk0->count++;

	Stk_tester (stk0, "Stk_push");
}

//============================================================
//function Stk_pop return last element of stack
//and delete it from stack

double Stk_pop (Stack_t * stk0)
{
	Stk_element * stk1 = NULL;
	double elem = 0;

	Stk_tester (stk0, "Stk_pop");

	if (stk0->count == 0)
	{
		printf ("==============================\n");
		printf ("ERROR in function Stk_pop:\n");
		printf ("this operation is impossible\n");
		printf ("stack is EMPTY so there are no elements\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}

	stk1 = stk0->head;

	elem = stk1->value;

	stk0->head = stk1->link;
	stk0->count--;

	free (stk1);

	Stk_tester (stk0, "Stk_pop");

	return elem;
}

//============================================================
//function Stk_top return last element of stack
//not delete this element from stack

double Stk_top (Stack_t * stk0)
{
	double elem = 0;

	Stk_tester (stk0, "Stk_top");

	if (stk0->count == 0)
	{
		printf ("==============================\n");
		printf ("ERROR in function Stk_top:\n");
		printf ("this operation is impossible\n");
		printf ("stack is EMPTY so there are no elements\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}

	elem = stk0->head->value;

	return elem;
}

//============================================================
//function Stk_clear delete all elements of stack
//not delete stack

void Stk_clear (Stack_t * stk0)
{
	Stk_element * stk1 = NULL;

	Stk_tester (stk0, "Stk_dtor");

	while ((stk0->count > 0) && (stk0->head != NULL))
	{
		stk1 = stk0->head;
		
		stk0->head = stk1->link;
		stk0->count--;
		
		free (stk1);
	}

	if (stk0->count > 0)
	{
		printf ("==============================\n");
		printf ("ERROR in function Stk_clear:\n");
		printf ("elements were deleted incorrectly\n");
		printf ("pointer to last element is NULL but count > 0\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}

	if (stk0->head != NULL)
	{
		printf ("==============================\n");
		printf ("ERROR in function Stk_clear:\n");
		printf ("elements were deleted incorrectly\n");
		printf ("counter = 0 but pointer to last element is not NULL\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}
}

//============================================================
//function Stk_dtor delete stack

void Stk_dtor (Stack_t * stk0)
{
	if (stk0 == NULL)
		return;

	Stk_clear (stk0);

	free (stk0);
}

//============================================================
//function Stk_add delete from stack 2 last elements
//and put in stack their sum
//function also return this sum

double Stk_add (Stack_t * stk0)
{
	double elem1 = 0, elem2 = 0, sum = 0;

	Stk_tester (stk0, "Stk_add");

	if (stk0->count < 2)
	{
		printf ("==============================\n");
		printf ("ERROR in function Stk_add:\n");
		printf ("this operation is impossible\n");
		printf ("there are less than 2 elements in stack\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}

	elem1 = Stk_pop (stk0);
	elem2 = Stk_pop (stk0);
	sum = elem1 + elem2;
	Stk_push (stk0, sum);

	Stk_tester (stk0, "Stk_add");

	return sum;
}

//============================================================
//function Stk_sub delete from stack 2 last elements
//and put in stack their difference

//If Y is last element, and 2 last elements are X and Y
//then function put in stack X-Y

//function also return this difference

double Stk_sub (Stack_t * stk0)
{
	double elem1 = 0, elem2 = 0, dif = 0;

	Stk_tester (stk0, "Stk_sub");

	if (stk0->count < 2)
	{
		printf ("==============================\n");
		printf ("ERROR in function Stk_sub:\n");
		printf ("this operation is impossible\n");
		printf ("there are less than 2 elements in stack\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}

	elem1 = Stk_pop (stk0);
	elem2 = Stk_pop (stk0);
	dif = elem2 - elem1;
	Stk_push (stk0, dif);

	Stk_tester (stk0, "Stk_sub");

	return dif;
}

//============================================================
//function Stk_mul delete from stack 2 last elements
//and put in stack their product (multiply them)
//function also return this product

double Stk_mul (Stack_t * stk0)
{
	double elem1 = 0, elem2 = 0, prod = 0;

	Stk_tester (stk0, "Stk_mul");

	if (stk0->count < 2)
	{
		printf ("==============================\n");
		printf ("ERROR in function Stk_mul:\n");
		printf ("this operation is impossible\n");
		printf ("there are less than 2 elements in stack\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}

	elem1 = Stk_pop (stk0);
	elem2 = Stk_pop (stk0);
	prod = elem1 * elem2;
	Stk_push (stk0, prod);

	Stk_tester (stk0, "Stk_mul");

	return prod;
}


//============================================================
//function Stk_pushAX add new element to stack from register AX

void Stk_pushAX (Stack_t * stk0)
{
	Stk_element * stk1 = NULL;
	
	Stk_tester (stk0, "Stk_pushAX");

	stk1 = (Stk_element *) calloc (1, sizeof (Stk_element));
	
	stk1->value = stk0->AX;
	stk1->link = stk0->head;

	stk0->head = stk1;
	stk0->count++;

	Stk_tester (stk0, "Stk_pushAX");
}

//============================================================
//function Stk_popAX put last element to register AX,
//and delete it from stack
//function also return this element

double Stk_popAX (Stack_t * stk0)
{
	Stk_element * stk1 = NULL;
	double elem = 0;

	Stk_tester (stk0, "Stk_popAX");

	if (stk0->count == 0)
	{
		printf ("==============================\n");
		printf ("ERROR in function Stk_popAX:\n");
		printf ("this operation is impossible\n");
		printf ("stack is EMPTY so there are no elements\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}

	stk1 = stk0->head;

	elem = stk1->value;

	stk0->head = stk1->link;
	stk0->count--;
	stk0->AX = elem;

	free (stk1);

	Stk_tester (stk0, "Stk_popAX");

	return elem;
}

//============================================================
//function Stk_pushBX add new element to stack from register BX

void Stk_pushBX (Stack_t * stk0)
{
	Stk_element * stk1 = NULL;
	
	Stk_tester (stk0, "Stk_pushBX");

	stk1 = (Stk_element *) calloc (1, sizeof (Stk_element));
	
	stk1->value = stk0->BX;
	stk1->link = stk0->head;

	stk0->head = stk1;
	stk0->count++;

	Stk_tester (stk0, "Stk_pushBX");
}

//============================================================
//function Stk_popBX put last element to register BX,
//and delete it from stack
//function also return this element

double Stk_popBX (Stack_t * stk0)
{
	Stk_element * stk1 = NULL;
	double elem = 0;

	Stk_tester (stk0, "Stk_popBX");

	if (stk0->count == 0)
	{
		printf ("==============================\n");
		printf ("ERROR in function Stk_popBX:\n");
		printf ("this operation is impossible\n");
		printf ("stack is EMPTY so there are no elements\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}

	stk1 = stk0->head;

	elem = stk1->value;

	stk0->head = stk1->link;
	stk0->count--;
	stk0->BX = elem;

	free (stk1);

	Stk_tester (stk0, "Stk_popBX");

	return elem;
}

//============================================================
//function Stk_pushCX add new element to stack from register CX

void Stk_pushCX (Stack_t * stk0)
{
	Stk_element * stk1 = NULL;
	
	Stk_tester (stk0, "Stk_pushCX");

	stk1 = (Stk_element *) calloc (1, sizeof (Stk_element));
	
	stk1->value = stk0->CX;
	stk1->link = stk0->head;

	stk0->head = stk1;
	stk0->count++;

	Stk_tester (stk0, "Stk_pushCX");
}

//============================================================
//function Stk_popCX put last element to register CX,
//and delete it from stack
//function also return this element

double Stk_popCX (Stack_t * stk0)
{
	Stk_element * stk1 = NULL;
	double elem = 0;

	Stk_tester (stk0, "Stk_popCX");

	if (stk0->count == 0)
	{
		printf ("==============================\n");
		printf ("ERROR in function Stk_popCX:\n");
		printf ("this operation is impossible\n");
		printf ("stack is EMPTY so there are no elements\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}

	stk1 = stk0->head;

	elem = stk1->value;

	stk0->head = stk1->link;
	stk0->count--;
	stk0->CX = elem;

	free (stk1);

	Stk_tester (stk0, "Stk_popCX");

	return elem;
}

//============================================================
//function Stk_cmp compare 2 last elements in stack
//X is last element, X and Y are 2 last elements
//then	if X<Y function return -1
//		if X=Y function return  0
//		if X>Y function return  1

int Stk_cmp (Stack_t * stk0)
{
	double elem1 = 0, elem2 = 0;

	Stk_tester (stk0, "Stk_cmp");

	if (stk0->count < 2)
	{
		printf ("==============================\n");
		printf ("ERROR in function Stk_cmp:\n");
		printf ("this operation is impossible\n");
		printf ("there are less than 2 elements in stack\n");
		printf ("==============================\n");
		Stk_print (stk0);
		assert (0);
	}

	elem1 = Stk_pop (stk0);
	elem2 = Stk_top (stk0);
	Stk_push (stk0, elem1);

	if (elem1 < elem2)
		return -1;
	if (elem1 > elem2)
		return 1;

	return 0;
}

//============================================================
