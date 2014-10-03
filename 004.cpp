//Tolya Grishin

//Reshenie kvadratnogo uravneniya po zadannym koeffizientam

//Vhodniye danniye: stroka s tremya chislami cherez probel
//mezhdu chislami lyuboe kolichestvo probelov
//dopuskayutza probely pered pervym i posle poslednego chisla

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct
{
	int num,        //kolichestvo korney
		errcode;    //0 = OK, 1 = ERROR
	double x1, x2;
}
radicals;


typedef struct
{
	int errcode;
	double number[3]; //koeffizienti uravneniya (a, b, c)
}
remake;


const int INFINITY = -1;


remake str_to_doub (const char* abc)   //proverka vhodnyh dannyh
{                                      //v abc nahodyatza a, b, c cherez probel 
	remake st_doub = {0, {0, 0, 0}};
	int len = 0, 
		num_point = 0,   //kolichestvo tochek v chisle
		sym_abc = 0,     //ukazatel na simvol stroki abc
		sym_p = 99,      //ukazatel na simvol stroki p
		num_x = 0;       //kolichestvo chisel v stroke abc
	char p[100];         //stroka dlya perevoda a, b, c v chisla

	len = strlen (abc);

	for (int q = 0; (q < 4) && (sym_abc < len - 1); q++) //dlya kazhdogo iz koef a, b, c...
	{
		for (int i = 0; i < sym_p + 1; i++)
			p[i] = '0';
		sym_p = 0;
		num_point = 0;

		while ((sym_abc < len) && (abc[sym_abc] == ' ')) //nachalo chisla
			sym_abc++;

		while ((sym_abc < len) && (abc[sym_abc] != ' '))  //copy chislo v p
		{
			p[sym_p] = abc[sym_abc];
			sym_abc++;
			sym_p++;
		}

		for (int i = 0; i < sym_p; i++) //proverka formata chisla
		{
			if (p[i] == '.')
				num_point++;
		
			if ( ((p[i] < '0') || (p[i] > '9')) && (p[i] != '.') && (p[i] != '-') ||
			 
				 (num_point > 1) || 
			 
				 (p[i] == '-') && (i != 0) || 
			 
				 ((i == 0) || (i == sym_p - 1)) && (p[i] == '.') ||
			 
				 (i == 1) && (p[0] == '-') && (p[1] == '.') )
			{
				st_doub.errcode = 1;
				return st_doub;
			}
		}

		if ((st_doub.errcode == 0) && (sym_p != 0))
		{
			num_x++;
			if (num_point == 0)  //esli chislo zeloe otdelyaem lishniye nuli tochkoy
				p[sym_p] = '.'; 
			if (q < 3)
				st_doub.number[q] = atof (p);  //perevod stroki v chislo
		}
	}
	
	if (num_x != 3)           //proverka kolichestva vvedennych chisel
		st_doub.errcode = 1;

	return st_doub;
}


radicals sq_equation (const char* abc)  //resheniye uravneniya
{
	double d = 0, a = 0, b = 0, c = 0;
	radicals equat = {0, 0, 0, 0}; 
	
	if (str_to_doub (abc).errcode == 1) //proverka formata vhodnyh dannyh
	{
		equat.errcode = 1;
		return equat;
	}
	
	a = str_to_doub (abc).number[0];   //koeffizienty uravneniya
	b = str_to_doub (abc).number[1];
	c = str_to_doub (abc).number[2];

	if (a == 0)
	{
		if ((b == 0) && (c == 0))
			equat.num = INFINITY;         
		if ((b == 0) && (c != 0))
			equat.num = 0;
		if (b != 0)
		{
			equat.num = 1;
			equat.x1 = -c / b + 0;
		}
	}
	
	else
	{
		d = b * b - 4 * a * c;
		if (d < 0)
			equat.num = 0;
		if (d == 0)
		{
			equat.num = 1;
			equat.x1 = -b / 2 / a + 0;
		}
		if (d > 0)
		{
			equat.num = 2;
			equat.x1 = -b / 2 / a - fabs (sqrt (d) / 2 / a) + 0; //min koren
			equat.x2 = -b / 2 / a + fabs (sqrt (d) / 2 / a) + 0; //max koren
		}
	}

	return equat;
}

int main ()
{
	char a[100];
	radicals k = {0, 0, 0, 0};
	
	gets (a);
	k = sq_equation (a);

	if (k.errcode == 0)
	{
		printf ("%d radicals\n", k.num);
		if (k.num > 0)
			printf ("x1=%lg\n", k.x1);
		if (k.num == 2)
			printf ("x2=%lg\n", k.x2);
	}
	else
		printf ("ERROR\n");

	system ("PAUSE");
	return 0;
}