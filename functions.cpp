#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

typedef struct
{
	long int count;
	long int * numbers;
	long int * freq;
}
mas_of_numb;

typedef struct
{
	long int count_str;
	long int count_col;
	long int ** numbers;
}
table_of_numb;


//===============================================================

//2008-1B. 1st input string contain count of numbers N <= 100000
//2nd input string contain int numbers 0 < x[i] <= 1000
//function must put numbers that meets not more than once in rising order
//if it isnt such numbers, it must put -1
mas_of_numb del_repeated_2 (const long int input_count, const long int * input_numb)
{
	mas_of_numb func = {0, 0, 0};
	long int * num_meet = 0, num_unrepeated = 0, counter = 0;
	
	num_meet = (long int *) calloc (1000, sizeof (* num_meet));
	for (long int i = 0; i < 1000; i++)
	{
		assert ((0 <= i) && (i < 1000));
		num_meet [i] = 0;
	}

	
	for (long int i = 0; i < input_count; i++)
	{
		assert ((0 <= i) && (i < input_count));
		assert ((1 <= input_numb [i]) && (input_numb [i] < 1000));

		num_meet [input_numb [i] - 1]++;  //count of meeting this number

		if (num_meet [input_numb [i] - 1] == 1)
			num_unrepeated++;

		if (num_meet [input_numb [i] - 1] == 2)
			num_unrepeated--;
	}

	
	func.numbers = (long int *) calloc (num_unrepeated, sizeof (* func.numbers));
	for (long int i = 0; i < num_unrepeated; i++)
	{
		assert ((0 <= i) && (i < num_unrepeated));
		func.numbers [i] = 0;
	}

	for (long int i = 0; (i < 1000) && (counter < num_unrepeated); i++)
	{
		assert ((0 <= i) && (i < 1000));
		assert ((0 <= counter) && (counter < num_unrepeated));

		if (num_meet [i] == 1)
		{
			func.numbers [counter] = i + 1;
			counter++;
		}
	}

	func.count = num_unrepeated;

	free(num_meet);
	
	return func;
}


//=============================================================

//2008-3C. INPUT: one string, length <= 1000, srting ends with '\n'
// OUTPUT: input string with turning over words
char * turn_over_words (const char * input_s)
{
	char * func = 0;
	long int len = 0, beg = 0, end = -1;

	len = strlen (input_s);
	func = (char *) calloc (len + 1, sizeof (* func));
	for (long int i = 0; i < len + 1; i++)
	{
		assert ((0 <= i) && (i < len + 1));
		func [i] = 0;
	}

	for (long int i = 0; i < len; i++)
	{
		assert ((0 <= i) && (i < len));

		if ((input_s [i] >= 'a') && (input_s [i] <= 'z') || 
			(input_s [i] >= 'A') && (input_s [i] <= 'Z'))
		{
			if (beg > end)
			{
				beg = i;
				end = i;
			}
			else
				end++;

			if (i == len - 1)
				for (long int j = end; j >= beg; j--)
				{
					assert ((0 <= end + beg - j) && (end + beg - j < len));
					func [end + beg - j] = input_s [j];
				}
		}

		else
		{
			assert ((0 <= i) && (i <= len));
			
			func [i] = input_s [i];

			if (end >= beg)
			{
				for (long int j = end; j >= beg; j--)
				{
					assert ((0 <= end + beg - j) && (end + beg - j < len));
					func [end + beg - j] = input_s [j];
				}
				end = beg - 1;
			}
		}
	}

	return func;
}


//==========================================================

//2008-1C. INPUT: text, less than 100000 symbols, ends with EOF
//OUTPUT: text with deleted wrong spaces
char * del_spaces (const char * input_t)
{
	char * func = 0;
	long int len_inp = 0, len_func = 0;

	len_inp = strlen (input_t);
	func = (char *) calloc (len_inp + 1, sizeof (* func));
	for (long int i = 0; i < len_inp + 1; i++)
	{
		assert ((0 <= i) && (i < len_inp + 1));
		func [i] = 0;
	}

	func [0] = input_t [0];
	for (long int i = 1; i < len_inp; i++)
	{
		assert ((0 <= i) && (i < len_inp));
		assert ((0 <= len_func) && (len_func < len_inp));
		
		if ((input_t [i] != ' ') || (input_t [i] == ' ') && (func [len_func] != ' '))
		{
			len_func++;
			func [len_func] = input_t [i];
		}
	}

	return func;
}


//==============================================================

//2008-4C. 1st input string: size of table NxN, N <= 50
//next N input strings: N int numbers < 10^6
//OUTPUT: string with (2N-1) numbers - sum of numbers on the 
//diagonals (down -> up, right -> left)
mas_of_numb sum_on_diagonals (const long int size, const long int * const * table)
{
	mas_of_numb func = {0, 0, 0};
	long int nummer_diag = 0;
	
	func.count = 2 * size - 1;
	func.numbers = (long int *) calloc (func.count, sizeof (* func.numbers));
	for (long int i = 0; i < func.count; i++)
	{
		assert ((0 <= i) && (i < func.count));
		func.numbers [i] = 0;
	}
	
	for (long int i = 0; i < size; i++)
		for (long int j = 0; j < size; j++)
		{
			nummer_diag = size - 1 - i + j;

			assert ((0 <= i) && (i < size));
			assert ((0 <= j) && (j < size));
			assert ((0 <= nummer_diag) && (nummer_diag < func.count));

			func.numbers [nummer_diag] += table [i] [j];
		}

	return func;
}


//=======================================================

//2008-6A. INPUT: size of table 0 < n, m <= 100
//OUTPUT: table m x n, filled up to down from 1 to n * m
table_of_numb fill_spirally (const long int size_col, const long int size_str)
{
	table_of_numb func = {0, 0, 0};

	func.count_str = size_str;
	func.count_col = size_col;

	func.numbers = (long int **) calloc (size_str, sizeof (* func.numbers));
	for (long int i = 0; i < size_str; i++)
	{
		assert ((0 <= i) && (i < size_str));
		func.numbers [i] = (long int *) calloc (size_col, sizeof (* func.numbers [i]));
	}

	for (long int i = 0; i < size_str; i++)
		for (long int j = 0; j < size_col; j++)
		{
			assert ((0 <= i) && (i < size_str));
			assert ((0 <= j) && (j < size_col));
			func.numbers [i] [j] = size_str * j + i + 1;
		}

	return func;
}


//=========================================================

//2008-7B. INPUT: size of table 0 < n,m <= 100
//OUTPUT: table m x n, filled along diagonals (up -> down, right -> left)
//with numbers from 1 to n * m
table_of_numb fill_snakely (const long int size_col, const long int size_str)
{
	table_of_numb func = {0, 0, 0};
	long int numb = 0, col = 0, str0 = 0;

	func.count_str = size_str;
	func.count_col = size_col;

	func.numbers = (long int **) calloc (size_str, sizeof (* func.numbers));
	for (long int i = 0; i < size_str; i++)
	{
		assert ((0 <= i) && (i < size_str));
		func.numbers [i] = (long int *) calloc (size_col, sizeof (* func.numbers [i]));
	}
	for (long int i = 0; i < size_str; i++)
		for (long int j = 0; j < size_col; j++)
		{
			assert ((0 <= i) && (i < size_str));
			assert ((0 <= j) && (j < size_col));
			func.numbers [i] [j] = 0;
		}

	for (long int diag = 0; diag <= size_str + size_col - 2; diag++)  // diag is nummer of diagonal
	{
		str0 = diag - size_col + 1;  //str0 is the least nummer of string in this diagonal
		if (str0 < 0)
			str0 = 0;

		for (long int str = str0; (str <= diag) && (str < size_str); str++)
		{
			assert ((0 <= str) && (str < size_str));  
			assert ((0 <= col) && (col < size_col));
			
			col = diag - str;  //str is nummer of string, col is nummer of column
			numb++;
			func.numbers [str] [col] = numb;
		}
	}
		
	return func;
}


//======================================================

//2008-8C. 1st input string: count of numbers 0 < N <= 1000
//2nd input string: N int numbers 0 < x [i] <= 2^31 - 1
//OUTPUT: list of numbers that meets more than 1 time, in order that they was puted
//each string must contain number and its frequancy
//if it is no such numbers, put -1
mas_of_numb freq_repeat (const long int input_count, const long int * input_numb)
{
	mas_of_numb func = {0, 0, 0}, list = {0, 0, 0};
	long int numb_dif = 0, counter = 0, numb_freq = 0;

	list.numbers = (long int *) calloc (1000, sizeof (* list.numbers));
	list.freq = (long int *) calloc (1000, sizeof (* list.freq));
	for (long int i = 0; i < 1000; i++)
	{
		assert ((0 <= i) && (i < 1000));
		list.numbers [i] = 0;
		list.freq [i] = 0;
	}

	for (long int i = 0; i < input_count; i++)
	{
		assert ((0 <= i) && (i < input_count));

		counter = 0;
		while ((list.numbers [counter] != input_numb [i]) && (list.freq [counter] != 0))
		{
			counter++;     //search this number in massiv
			assert ((0 <= counter) && (counter < 1000));
		}
		
		assert ((0 <= counter) && (counter < 1000));

		if (list.freq [counter] == 0)  //if this number isnt meeted before
		{
			list.numbers [counter] = input_numb [i];
			numb_dif++;  // count of different numbers in input string
		}
		list.freq [counter]++;

		if (list.freq [counter] == 2)
			numb_freq++;   // count of numbers that are meeted more than 1 time
	}

	func.numbers = (long int *) calloc (numb_freq, sizeof (* func.numbers));
	func.freq = (long int *) calloc (numb_freq, sizeof (* func.numbers));

	counter = -1;
	for (long int i = 0; i < numb_dif; i++)
	{
		assert ((0 <= i) && (i < numb_dif));
		
		if (list.freq [i] >= 2)
		{
			counter++;
			assert ((0 <= counter) && (counter < numb_freq));
			func.numbers [counter] = list.numbers [i];
			func.freq [counter] = list.freq [i];
		}
	}

	func.count = numb_freq;

	free (list.numbers);
	free (list.freq);

	return func;
}


//===========================================================

//INPUT: 2 int numbers >= 0, in 2 strings, each not more 1000 signs
//OURPUT: multiplication of these numbers
char * long_multiplicate (const char * numb1, const char * numb2)
{
	char * func = 0, k = 'a';
	long int len1 = 0, len2 = 0, pos_now = 0, sum = 0, len_f = 0;

	len1 = strlen (numb1);
	len2 = strlen (numb2);

	func = (char *) calloc (len1 + len2 + 1, sizeof (* func));
	for (long int i = 0; i < len1 + len2; i++)
	{
		assert ((0 <= i) && (i < len1 + len2));
		func [i] = '0';
	}
	func [len1 + len2] = 0;

	for (long int i = len1 - 1; i >= 0; i--)
		for (long int j = len2 - 1; j >= 0; j--)
		{
			assert ((0 <= i) && (i < len1));
			assert ((0 <= j) && (j < len2));

			pos_now = len1 + len2 - i - j - 2;

			sum = (numb1 [i] - '0') * (numb2 [j] - '0') + func [pos_now] - '0';
			
			assert ((0 <= pos_now) && (pos_now + 1 < len1 + len2));
			func [pos_now] = '0' + sum % 10;
			func [pos_now + 1] += sum / 10;
		}
	
	len_f = len1 + len2;
	for (long int i = len1 + len2 - 1; (func [i] == '0') && (i > 0); i--)
	{
		assert ((0 <= i) && (i < len1 + len2));
		func [i] = 0;
		len_f = i;
	}
	
	for (long int i = 0; i < (len_f + 1) / 2; i++)
	{
		assert ((0 <= i) && (i < len1 + len2));
		assert ((0 <= len_f - 1 - i) && (len_f - 1 - i < len1 + len2));
		assert (('0' <= func [i]) && (func [i] <= '9'));
		assert (('0' <= func [len_f - 1 - i]) && (func [len_f - 1 - i] <= '9'));

		k = func [i];
		func [i] = func [len_f - 1 - i];
		func [len_f - 1 - i] = k;
	} 
	
	return func;
}


//==========================================================

//1st input string: count of numbers N <= 100000
//2nd input string: N numbers x [i] < 2^31 - 1
//3rd input string: cycle shift k <= 100000
//OUTPUT: N numbers with cycle shift (right -> left)
mas_of_numb cycle_shift (const long int input_count, const long int * input_numb, const long int shift)
{
	mas_of_numb func = {0, 0, 0};
	long int old_num = 0;

	func.count = input_count;
	func.numbers = (long int *) calloc (input_count, sizeof (* func.numbers));
	for (long int i = 0; i < input_count; i++)
	{
		assert ((0 <= i) && (i < input_count));
		func.numbers [i] = 0;
	}

	for (long int i = 0; i < input_count; i++)
	{
		old_num = (i + shift) % input_count;
		
		assert ((0 <= i) && (i < input_count));
		assert ((0 <= old_num) && (old_num < input_count));
		func.numbers [i] = input_numb [old_num];
	}

	return func;
}


//========================================================

//2008-8D. INPUT: 2 int numbers >= 0, in 2 strings, each not more 1000 signs
//OUTPUT: sum of these numbers

char * long_sum (const char * numb1, const char * numb2)
{
	char * func = 0, k = 'a';
	long int len1 = 0, len2 = 0, len_f = 0, max_len = 0, min_len = 0, sum = 0;
	
	len1 = strlen (numb1);
	len2 = strlen (numb2);
	if (len1 > len2)
	{
		max_len = len1;
		min_len = len2;
	}
	else
	{
		max_len = len2;
		min_len = len1;
	}

	func = (char *) calloc (max_len + 2, sizeof (* func));
	for (long int i = 0; i < max_len + 1; i++)
	{
		assert ((0 <= i) && (i < max_len + 1));
		func [i] = '0';
	}
	func [max_len + 1] = 0;

	for (long int i = 0; i < min_len; i++)
	{
		assert ((0 <= len1 - i - 1) && (len1 - i - 1 < len1));
		assert ((0 <= len2 - i - 1) && (len2 - i - 1 < len2));
		assert ((0 <= i) && (i + 1 < max_len + 1));

		sum = numb1 [len1 - i - 1] - '0' + numb2 [len2 - i - 1] - '0' + func [i] - '0';
		func [i] = '0' + sum % 10;
		func [i + 1] += sum / 10;
	}

	for (long int i = min_len; i < max_len; i++)
	{
		assert ((0 <= i) && (i + 1 < max_len + 1));
		
		if (len1 == max_len)
		{
			assert ((0 <= len1 - i - 1) && (len1 - i - 1 < len1));
			sum = numb1 [len1 - i - 1] - '0' + func [i] - '0';
		}
		else 
		{
			assert ((0 <= len2 - i - 1) && (len2 - i - 1 < len2));
			sum = numb2 [len2 - i - 1] - '0' + func [i] - '0';
		}

		func [i] = '0' + sum % 10;
		func [i + 1] += sum / 10;
	}

	len_f = max_len + 1;
	if (func [max_len] == '0')
	{
		func [max_len] = 0;
		len_f = max_len;
	}

	for (long int i = 0; i < (len_f + 1) / 2; i++)
	{
		assert ((0 <= i) && (i < len_f));
		assert ((0 <= len_f - i - 1) && (len_f - i - 1 < len_f));
		assert (('0' <= func [i]) && (func [i] <= '9'));
		assert (('0' <= func [len_f - i - 1]) && (func [len_f - i - 1] <= '9'));

		k = func [i];
		func [i] = func [len_f - i - 1];
		func [len_f - i - 1] = k;
	}

	return func;
}


//=========================================================

int main ()
{
	long int nummer_func = 0, n = 0, m = 0, * str_int1 = 0, ** table1 = 0;
	mas_of_numb mas1 = {0, 0, 0};
	table_of_numb mas_mas1 = {0, 0, 0};
	char * str_ch1 = 0, * str_ch2 = 0, * str_ch3 = 0, sym = 'a';
	
	printf ("Put number of function\n1) del_repeated_2\n2) turn_over_words\n");
	printf ("3) del_spaces\n4) sum_on_diagonals\n5) fill_spirally\n");
	printf ("6) fill_snakely\n7) freq_repeat\n8) long_multiplicate\n");
	printf ("9) cycle shift\n10) long_sum\n");
	scanf ("%ld", &nummer_func);
	scanf ("%c", &sym);

//=============================================================
	
	if (nummer_func == 1)
	{
		scanf ("%ld", &n);
		str_int1 = (long int *) calloc (n, sizeof (* str_int1));
		for (long int i = 0; i < n; i++)
		{
			assert ((0 <= i) && (i < n));
			str_int1 [i] = 0;
		}
		
		for (long int i = 0; i < n; i++)
		{
			assert ((0 <= i) && (i < n));
			scanf ("%ld", &str_int1[i]);
		}

		mas1 = del_repeated_2 (n, str_int1);
		
		for (long int i = 0; i < mas1.count; i++)
		{
			assert ((0 <= i) && (i < mas1.count));
			printf ("%ld ", mas1.numbers [i]);
		}
		if (mas1.count == 0)
			printf ("-1 \n");
		else
			printf ("\n");
		
		free (str_int1);
		free (mas1.numbers);
	}

//================================================================

	if (nummer_func == 2)
	{
		str_ch1 = (char *) calloc (1001, sizeof (* str_ch1));
		for (long int i = 0; i < 1001; i++)
		{
			assert ((0 <= i) && (i < 1001));
			str_ch1 [i] = 0;
		}

		scanf ("%c", &sym);
		for (long int i = 0; sym != '\n'; i++)
		{
			assert ((0 <= i) && (i < 1000));
			str_ch1 [i] = sym;
			scanf ("%c", &sym);
		}
		
		str_ch2 = turn_over_words (str_ch1);
		for (long int i = 0; i < strlen (str_ch2); i++)
		{
			assert ((0 <= i) && (i < strlen (str_ch2)));
			printf ("%c", str_ch2 [i]);
		}
		printf ("\n");

		free (str_ch1);
		free (str_ch2);
	}

//===========================================================

	if (nummer_func == 3)
	{
		str_ch1 = (char *) calloc (100000, sizeof (* str_ch1));
		for (long int i = 0; i < 100000; i++)
		{
			assert ((0 <= i) && (i < 100000));
			str_ch1 [i] = 0;
		}

		for (long int i = 0; scanf ("%c", &sym) == 1; i++)
		{
			assert ((0 <= i) && (i < 100000));
			str_ch1 [i] = sym;
		}

		str_ch2 = del_spaces (str_ch1);
		for (long int i = 0; i < strlen (str_ch2); i++)
		{
			assert ((0 <= i) && (i < strlen (str_ch2)));
			printf ("%c", str_ch2 [i]);
		}

		free (str_ch1);
		free (str_ch2);
	}

//==========================================================

	if (nummer_func == 4)
	{
		scanf ("%ld", &n);

		table1 = (long int **) calloc (n, sizeof (* table1));
		for (long int i = 0; i < n; i++)
		{
			assert ((0 <= i) && (i < n));
			table1 [i] = (long int *) calloc (n, sizeof (* table1 [i]));
		}
		
		for (long int i = 0; i < n; i++)
			for (long int j = 0; j < n; j++)
			{
				assert ((0 <= i) && (i < n));
				assert ((0 <= j) && (j < n));
				scanf ("%ld", &table1 [i] [j]);
			}

		mas1 = sum_on_diagonals (n, table1);

		for (long int i = 0; i < mas1.count; i++)
		{
			assert ((0 <= i) && (i < mas1.count));
			printf ("%ld ", mas1.numbers [i]);
		}
		printf ("\n");

		for (long int i = 0; i < n; i++)
		{
			assert ((0 <= i) && (i < n));
			free (table1 [i]);
		}
		free (table1);
		free (mas1.numbers);
	}

//=============================================================

	if (nummer_func == 5)
	{
		scanf ("%ld %ld", &n, &m);

		mas_mas1 = fill_spirally (n, m);

		for (long int i = 0; i < mas_mas1.count_str; i++)
		{
			for (long int j = 0; j < mas_mas1.count_col; j++)
			{
				assert ((0 <= i) && (i < mas_mas1.count_str));
				assert ((0 <= j) && (j < mas_mas1.count_col));
				printf ("%ld ", mas_mas1.numbers [i] [j]);
			}
			printf ("\n");
		}

		for (long int i = 0; i < mas_mas1.count_str; i++)
		{
			assert ((0 <= i) && (i < mas_mas1.count_str));
			free (mas_mas1.numbers [i]);
		}
		free (mas_mas1.numbers);
	}

//====================================================

	if (nummer_func == 6)
	{
		scanf ("%ld %ld", &n, &m);

		mas_mas1 = fill_snakely (n, m);

		for (long int i = 0; i < mas_mas1.count_str; i++)
		{
			for (long int j = 0; j < mas_mas1.count_col; j++)
			{
				assert ((0 <= i) && (i < mas_mas1.count_str));
				assert ((0 <= j) && (j < mas_mas1.count_col));
				printf ("%ld ", mas_mas1.numbers [i] [j]);
			}
			printf ("\n");
		}

		for (long int i = 0; i < mas_mas1.count_str; i++)
		{
			assert ((0 <= i) && (i < mas_mas1.count_str));
			free (mas_mas1.numbers [i]);
		}
		free (mas_mas1.numbers);
	}

//===============================================================

	if (nummer_func == 7)
	{
		scanf ("%ld", &n);

		str_int1 = (long int *) calloc (n, sizeof (* str_int1));
		for (long int i = 0; i < n; i++)
		{
			assert ((0 <= i) && (i < n));
			scanf ("%ld", &str_int1 [i]);
		}

		mas1 = freq_repeat (n, str_int1);

		for (long int i = 0; i < mas1.count; i++)
		{
			assert((0 <= i) && (i < mas1.count));
			printf ("%ld %ld\n", mas1.numbers [i], mas1.freq [i]);
		}
		if (mas1.count == 0)
			printf ("-1\n");

		free (str_int1);
		free (mas1.numbers);
		free (mas1.freq);
	}

//============================================================

	if (nummer_func == 8)
	{
		str_ch1 = (char *) calloc (1001, sizeof (* str_ch1));
		str_ch2 = (char *) calloc (1001, sizeof (* str_ch2));
		for (long int i = 0; i < 1001; i++)
		{
			assert ((0 <= i) && (i < 1001));
			str_ch1 [i] = 0;
			str_ch2 [i] = 0;
		}

		scanf ("%s", str_ch1);
		scanf ("%s", str_ch2);
		
		str_ch3 = long_multiplicate (str_ch1, str_ch2);
		printf ("%s\n", str_ch3);

		free (str_ch1);
		free (str_ch2);
		free (str_ch3);
	}

//==================================================================

	if (nummer_func == 9)
	{
		scanf ("%ld", &n);

		str_int1 = (long int*) calloc (n, sizeof (* str_int1));
		for (long int i = 0; i < n; i++)
		{
			assert ((0 <= i) && (i < n));
			scanf ("%ld", &str_int1 [i]);
		}

		scanf ("%ld", &m);

		mas1 = cycle_shift (n, str_int1, m);
		for (long int i = 0; i < mas1.count; i++)
		{
			assert ((0 <= i) && (i < mas1.count));
			printf ("%ld ", mas1.numbers [i]);
		}
		printf ("\n");
		
		free (str_int1);
		free (mas1.numbers);
	}

//===========================================================

	if (nummer_func == 10)
	{
		str_ch1 = (char *) calloc (1001, sizeof (* str_ch1));
		str_ch2 = (char *) calloc (1001, sizeof (* str_ch2));
		for (long int i = 0; i < 1001; i++)
		{
			assert ((0 <= i) && (i < 1001));
			str_ch1 [i] = 0;
			str_ch2 [i] = 0;
		}

		scanf ("%s", str_ch1);
		scanf ("%s", str_ch2);

		str_ch3 = long_sum (str_ch1, str_ch2);
		printf ("%s\n", str_ch3);

		free (str_ch1);
		free (str_ch2);
		free (str_ch3);
	}

//=======================================================================

	return 0;
}

