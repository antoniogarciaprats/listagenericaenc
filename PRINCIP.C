// ----------------------------------------------------------------------
//               	      PROGRAMA PRINCIPAL
// ----------------------------------------------------------------------

#include <stdio.h>
#include <conio.h>
#include "lvoid.h"

//  ---------------------------------------------------------------------

int compar (const void *a, const void *b)   {
	return (* ((int *) a) < * ((int *) b) ? -1:
		* ((int *) a) > * ((int *) b) ? 1 : 0);
    }

// ----------------------------------------------------------------------

char l_menu (void)    {
	char s;

	printf ("\n\t\t *********************************************\n");
	printf ("\t\t *********             MENU          *********\n");
	printf ("\t\t *********************************************\n\n");
	printf ("\t\t a) Crear una lista.\n");
	printf ("\t\t b) Introducir un elemento por la derecha.\n");
	printf ("\t\t c) Introducir un elemento por la izquierda.\n");
	printf ("\t\t d) Sacar un elemento por la derecha.\n");
	printf ("\t\t e) Sacar un elemento por la izquierda.\n");
	printf ("\t\t f) Introducir un elemento ordenadamente.\n");
	printf ("\t\t g) Sacar un elemento ordenadamente.\n");
	printf ("\t\t h) Hacer una copia de la lista.\n");
	printf ("\t\t i) Buscar un elemento en la lista.\n");
	printf ("\t\t j) Destruir la lista.\n");
	printf ("\t\t k) Mostrar los elementos de la listas.\n");
	printf ("\t\t s) Salir.\n\n");
	printf ("\t\t Elija una operacion: ");
	s = getche ();
	return (s);
    }

// ----------------------------------------------------------------------

void main (void)    {
	char opcion, tecla;
	lista a = NULL, b = NULL;
	int d;

	tecla = 's';
	while (tecla == 's' || tecla == 'S')   {
		clrscr ();
		opcion = l_menu ();
		switch (opcion)   {
			case 'a':
			   a = l_nueva (sizeof (d));
			   printf ("\n\n\t\t Se ha creado una lista vac¡a.");
			   break;

			case 'b':
			   printf ("\n\n\t\t Introduzca el elemento a guardar: ");
			   scanf ("%d", &d);
			   l_meterder (&a, &d);
			   break;

			case 'c':
			   printf ("\n\n\t\t Introduzca el elemento a guardar: ");
			   scanf ("%d", &d);
			   l_meterizq (&a, &d);
			   break;

			case 'd':
			   l_sacarder (&a, &d);
			   printf ("\n\n\t\t El ultimo elemento es el %d.\n", d);
			   break;

			case 'e':
			   l_sacarizq (&a, &d);
			   printf ("\n\n\t\t El primer elemento es el %d.\n", d);
			   break;

			case 'f':
			   printf ("\n\n\t\t Introduzca el elemento a guardar: ");
			   scanf ("%d", &d);
			   l_meterx (&a, &d, compar);
			   break;

			case 'g':
			   printf ("\n\n\t\t Introduzca el elemento a sacar: ");
			   scanf ("%d", &d);
			   l_sacarx (&a, &d, compar);
			   break;

			case 'h':
			   b = l_copiar (&a);
			   printf ("\n\n\t\t Se ha creado una copia de la lista.");
			   break;

			case 'i':
			   printf ("\n\n\t\t Introduzca el elemento a buscar: ");
			   scanf ("%d", &d);
			   if (l_buscar (&a, &d, compar))
				printf ("\n\t\t El elemento %d esta en la lista.", d);
			   else printf ("\n\t\t El elemento %d no esta en la lista.", d);
			   break;

			case 'j':
			   l_destruir (&a);
			   printf ("\n\n\t\t La lista ha sido destruida y liberada la memoria que ocupaba.\n");
			   break;

			case 's':
			   if (a)  l_destruir (&a);
			   if (b)  l_destruir (&b);
			   break;
		    }
		gotoxy (10, 25);
		printf ("¨Quieres seguir realizando mas operaciones (S/N)? ");
		tecla = getche ();
	   }
	clrscr ();
     }
