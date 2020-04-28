// -----------------------------------------------------------------------

// 			PROGRAMA PRINCIPAL

// ----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "lvoid.h"

//  ---------------------------------------------------------------------

int compar (const void *a, const void *b)   {
	return (* ((int *) a) < * ((int *) b) ? -1:
		* ((int *) a) > * ((int *) b) ? 1 : 0);
    }

// ----------------------------------------------------------------------

int main ()   {
	lista a = NULL, b = NULL;
	int i, d;

	clrscr ();
	a = l_nueva (sizeof (int));
	if (l_vacia (a))    printf ("\n\t La lista est  vac¡a.\n");
	else    {
		printf ("\n\t Error: La lista no se cre¢ bien.\n");
		return (1);
	   }

	printf ("\n\t Meto del 10 al 1 por la izquierda\n");
	for (i = 10; i > 0; i--)   {
		//printf ("   %d", i);
		l_meterizq (a, &i);
	    }
	printf ("\n\t Meto del 11 al 20 por la derecha\n");
	for (i = 11; i < 21; i++)   {
		//printf ("   %d", i);
		l_meterder (a, &i);
	   }

	printf ("\n\t Saco 5 elementos por la derecha\n");
	for (i = 0; i < 5; i++)   {
		l_sacarder (a, &d);
		//printf ("   %d", d);
	   }
	printf ("\n\t Saco 5 elementos por la izquierda\n");
	for (i = 0; i < 5; i++)   {
		l_sacarizq (a, &d);
		//printf ("   %d", d);
	    }

	printf ("\n Ahora tengo una lista ordenada con los n£meros del 6 al 15.");
	if (!l_vacia (a))    printf ("\n La lista no est  vac¡a.");
	else    {
		printf ("\n Error: Ni mete ni saca bien.");
		return (2);
	   }

	d = 10;
	l_sacarx (a, &d, compar);
	printf ("\n Sacarx el elemento %d.", d);
	d = 6;
	l_sacarx (a, &d, compar);
	printf ("\n Sacarx el elemento %d.", d);
	d = 15;
	l_sacarx (a, &d, compar);
	printf ("\n Sacarx el elemento %d.", d);
	d = 10;
	l_meterx (a, &d, compar);
	printf ("\n Meterx el elemento %d.", d);
	d = 6;
	l_meterx (a, &d, compar);
	printf ("\n Meterx el elemento %d.", d);
	d = 15;
	l_meterx (a, &d, compar);
	printf ("\n Meterx el elemento %d.", d);

	printf ("\n Ahora sigo teniendo una lista ordenada con los n£meros del 6 al 15:\n");
	i_inicializar (a);
	i = 6;
	while (i_quedan (a))    {
		i_dame (a, &d);
		printf ("  %d", d);
		if (i != d)   {
			printf ("\t Error: Ten¡an que ser iguales.\n");
			return (3);
		   }
		i++;
	   }
	b = l_copiar (a);
	l_destruir (&a);
	if (a != NULL) {
		printf ("Error: La destrucci¢n no es correcta.\n");
		return (4);
	    }
	i_inicializar (b);
	i = 6;
	while (i_quedan (b)) {
		i_dame (b, &d);
		printf ("  %d", d);
		if (i != d)    {
			printf ("\t Error: La copia no es buena.\n");
			return (3);
		    }
		i++;
	   }
	for (i = 0; i < 20; i++) {
		d = i;
		if (l_buscar (b, &d, compar))   {
			if (i < 6 || i > 15) printf ("Error: El %d est .\n", i);
		    }
		else if (i > 5 && i < 16) printf ("Error: El %d no est .\n", i);
	    }
	l_destruir (&b);
	printf ("\nNo he comprobado si queda la misma memoria que hab¡a al principio.\n");
	printf ("Fin de la ejecuci¢n: TODO BIEN.\n");
	return (0);
  }
