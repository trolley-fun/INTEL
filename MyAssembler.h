#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "MyStack.h"

const int sz_str = 20;
const int sz_com = 100;
const int sz_met = 10;

const int ERROR = -1;
const int PUSH = 0;
const int ADD = 1;
const int MUL = 2;
const int END = 3;

typedef struct Code_t
{
	int command [sz_com];
	int ptr_com;
	int metka [sz_met];
};


void Translator (char * in_fileName, char * out_fileName)
{
	int i = 0, numb = 0;
	char str [sz_str];
	FILE * in_file = NULL, * out_file = NULL; 
	
	for (i = 0; i < sz_str; i++)
		str [i] = '\0';
	
	in_file = fopen (in_fileName, "rt");
	out_file = fopen (out_fileName, "wt");

	if (in_file == NULL)
	{
		fclose (out_file);
		printf ("ERROR in function Translator: input file was opened with error\n");
		assert (0);
	}
	if (out_file == NULL)
	{
		fclose (in_file);
		printf ("ERROR in function Translator: output file was opened with error\n");
		assert (0);
	}

	while (fscanf (in_file, "%s", str) != EOF)
	{
		if (strcmp (str, "push") == 0)
		{
			fprintf (out_file, "%d ", PUSH);
			
			if (fscanf (in_file, "%d", &numb) != 1)
			{
				fprintf (out_file, "\n%d\n", ERROR);
				fclose (in_file);
				fclose (out_file);

				printf ("ERROR in function Translator: int number expected after push\n");
				assert (0);
			}
			fprintf (out_file, "%d\n", numb);
			continue;
		}

		if (strcmp (str, "add") == 0)
		{
			fprintf (out_file, "%d\n", ADD);
			continue;
		}
		
		if (strcmp (str, "mul") == 0)
		{
			fprintf (out_file, "%d\n", MUL);
			continue;
		}
		
		if (strcmp (str, "end") == 0)
		{
			fprintf (out_file, "%d\n", END);
			continue;
		}
		
		if (str [0] == ':')
		{
			fprintf (out_file, "%s ", str);
			continue;
		}

		fprintf (out_file, "%d\n", ERROR);

		fclose (in_file);
		fclose (out_file);
		printf ("ERROR in function Translator: wrong command %s\n", str);
		assert (0);
	}

	fprintf (out_file, "%c", EOF);

	fclose (in_file);
	fclose (out_file);
}

Code_t Code_prepare (char * in_fileName)
{
	FILE * in_file = NULL;
	Code_t code;
	int i = 0, numb = 0, com = 0;
	char chr = 'a';

	for (i = 0; i < sz_com; i++)
		code.command [i] = 0;
	for (i = 0; i < sz_met; i++)
		code.metka [i] = -1;
	code.ptr_com = 0;

	in_file = fopen (in_fileName, "rt");
	if (in_file == NULL)
	{
		printf ("ERROR in function Code_prepare: input file was opened with error\n");
		assert (0);
	}

	while (feof (in_file) == 0)
	{
		if (code.ptr_com > sz_com - 3)
		{
			code.command [code.ptr_com] = ERROR;
			code.ptr_com++;
			fclose (in_file);
			printf ("ERROR in function Code_prepare: too much commands\n");
			assert (0);
		}
		
		if (fscanf (in_file, "%d", &com) == 1)
		{
			switch (com)
			{
			case ERROR: code.command [code.ptr_com] = ERROR;
						code.ptr_com++;
						fclose (in_file);
						printf ("ERROR in function Code_prepare: wrong input file\n");
						assert (0);
						break;
			case PUSH:	code.command [code.ptr_com] = PUSH;
						code.ptr_com++;
						if (fscanf (in_file, "%d", &numb) != 1)
						{
							code.command [code.ptr_com] = ERROR;
							code.ptr_com++;
							fclose (in_file);
							printf ("ERROR in function Code_prepare: int number expected after push\n");
							assert (0);
						}
						code.command [code.ptr_com] = numb;
						code.ptr_com++;
						break;
			case ADD:	code.command [code.ptr_com] = ADD;
						code.ptr_com++;
						break;
			case MUL:	code.command [code.ptr_com] = MUL;
						code.ptr_com++;
						break;
			case END:	code.command [code.ptr_com] = END;
						code.ptr_com++;
						break;
			default:	code.command [code.ptr_com] = ERROR;
						code.ptr_com++;
						fclose (in_file);
						printf ("ERROR in function Code_prepare: wrong number of command\n");
						assert (0);
			}

			continue;
		}

		if (fscanf (in_file, "%c", &chr) == EOF)
			break;
		if (chr == ':')
		{
			if ((fscanf (in_file, "%d", &numb) != 1) || (numb < 0) || (numb > 9))
			{
				code.command [code.ptr_com] = ERROR;
				code.ptr_com++;
				fclose (in_file);
				printf ("ERROR in function Code_prepare: incorrect metka %d\n", numb);
				assert (0);
			}
			code.metka [numb] = code.ptr_com;
			continue;
		}

		if (fscanf (in_file, "%c", &chr) == EOF)
			break;
		code.command [code.ptr_com] = ERROR;
		code.ptr_com++;
		fclose (in_file);
		printf ("ERROR in function Code_prepare: incorrect input file\n");
		assert (0);
	}

	code.ptr_com = 0;

	fclose (in_file);

	return code;
}

void Prog_maker0 (Code_t code0, Stack_t * stk0)
{
	int i = 0;

	Stk_ctor (stk0);

	while (code0.command [i] != END)
	{
		switch (code0.command [i])
		{
		case ERROR:	printf ("ERROR in function Prog_maker: error in program");
					assert (0);
					break;
		case PUSH:	Stk_push (stk0, code0.command [i+1]);
					i += 2;
					break;
		case ADD:	Stk_add (stk0);
					i++;
					break;
		case MUL:	Stk_mul (stk0);
					i++;
					break;
		default:	printf ("ERROR in function Prog_maker: wrong command");
					assert (0);
		}
	}
}
