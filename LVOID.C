// -----------------------------------------------------------------------

//      	MODULO EN C PARA USO DE OBJETOS LISTA GENERICA

// ----------------------------------------------------------------------

//	AUTOR: M¦ Jose Perez Romero - M¦ Angeles Morillo Jimenez
//	MODIFICACION: 12/12/1999

// ----------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "lvoid.h"

struct tlista    {
	unsigned int tam;
	void *iter;
	void *prim;
	void *ult;
   };

// ----------------------------------------------------------------------
//			FUNCIONES PRIVADAS
// ----------------------------------------------------------------------

void l_error (int error, char *prim)    {
	switch (error)   {
	     case 1: fprintf (stderr, "\n\n\t%s: No hay suficiente memoria.\n", prim);
		     break;
	     case 2: fprintf (stderr, "\n\n\t%s: La lista no existe.\n", prim);
		     break;
	     case 3: fprintf (stderr, "\n\n\t%s: La lista esta vacia.\n", prim);
		     break;
	  }
   }

// ----------------------------------------------------------------------
//			FUNCIONES PUBLICAS
// ----------------------------------------------------------------------

lista l_nueva (unsigned int tam)    {
	struct tlista *nueva;

	nueva = (struct tlista *) malloc (sizeof (struct tlista));
	if (!nueva)   {
		l_error (1, "l_nueva");
		exit (1);
	    }

	nueva -> tam = tam;
	nueva -> prim = nueva -> ult = nueva -> iter = NULL;
	return (nueva);
   }

// ----------------------------------------------------------------------

int l_vacia (lista l)    {
	if (!l)    {
		l_error (2, "l_vacia");
		exit (1);
	   }

	return (((struct tlista *) l) -> prim == NULL);
   }

// ----------------------------------------------------------------------

void l_meterder (lista l, void *e)    {
	void *nuevo;

	if (!l)    {
		l_error (2, "l_meterder");
		exit (1);
	   }
	nuevo = (void *) malloc (sizeof (nuevo) + ((struct tlista *) l) -> tam);
	if (!nuevo)    {
		l_error (1, "l_meterder");
		exit (1);
	   }

	memcpy ((char *) nuevo + sizeof (nuevo), e, ((struct tlista *) l) -> tam);

	if (((struct tlista *) l) -> prim == NULL)    {
		memcpy (nuevo, &((struct tlista *) l) -> prim, sizeof (nuevo));
		((struct tlista *) l) -> prim = ((struct tlista *) l) -> ult = nuevo;
	   }
	else    {
		memcpy (nuevo, ((struct tlista *) l) -> ult , sizeof (nuevo));
		memcpy (((struct tlista *) l) -> ult, &nuevo, sizeof (nuevo));
		((struct tlista *) l) -> ult = nuevo;
	   }
   }

// ----------------------------------------------------------------------

void l_meterizq (lista l, void *e)   {
	void *nuevo;

	if (!l)    {
		l_error (2, "l_meterizq");
		exit (1);
	   }
	nuevo = (void *) malloc (sizeof (nuevo) + ((struct tlista *) l) -> tam);
	if (!nuevo)    {
		l_error (1, "l_meterizq");
		exit (1);
	   }

	memcpy ((char *) nuevo + sizeof (nuevo), e, ((struct tlista *) l) -> tam);

	if (((struct tlista *) l) -> prim == NULL)    {
		memcpy (nuevo, &((struct tlista *) l) -> prim, sizeof (nuevo));
		((struct tlista *) l) -> prim = ((struct tlista *) l) -> ult = nuevo;
	   }
	else    {
		memcpy (nuevo, &((struct tlista *) l) -> prim, sizeof (nuevo));
		((struct tlista *) l) -> prim = nuevo;
	  }
   }

// ----------------------------------------------------------------------

void l_sacarder (lista l, void *e)   {
	void *viejo, *aux;

	if (!l)    {
		l_error (2, "l_sacarder");
		exit (1);
	   }
	if (((struct tlista *) l) -> prim == NULL)    {
		l_error (3, "l_sacarder");
		exit (1);
	   }

	viejo = ((struct tlista *) l) -> ult;
	memcpy (e, (char *) viejo + sizeof (viejo), ((struct tlista *) l) -> tam);

	if (((struct tlista *) l) -> prim == ((struct tlista *) l) -> ult)
		((struct tlista *) l) -> prim = ((struct tlista *) l) -> ult = NULL;
	else   {
		((struct tlista *) l) -> ult = ((struct tlista *) l) -> prim;
		memcpy ((char *)&aux, ((struct tlista *) l) -> ult, sizeof (aux));

		while (aux != viejo)     {
			memcpy (&((struct tlista *) l) -> ult, (char *)&aux, sizeof (aux));
			memcpy ((char *)&aux, ((struct tlista *) l) -> ult, sizeof (aux));
		   }
		memcpy (((struct tlista *) l) -> ult, viejo, sizeof (viejo));
	  }

	free (viejo);
   }

// ----------------------------------------------------------------------

void l_sacarizq (lista l, void *e)   {
	void *viejo;

	if (!l)    {
		l_error (2, "l_sacarizq");
		exit (1);
	   }
	if (((struct tlista *) l) -> prim == NULL)    {
		l_error (3, "l_sacarizq");
		exit (1);
	   }

	viejo = ((struct tlista *) l) -> prim;
	memcpy (e, (char *) viejo + sizeof (viejo), ((struct tlista *) l) -> tam);

	if (((struct tlista *) l) -> prim == ((struct tlista *) l) -> ult)
		((struct tlista *) l) -> prim = ((struct tlista *) l) -> ult = NULL;
	else   	memcpy (&((struct tlista *) l) -> prim, viejo, sizeof (viejo));

	free (viejo);
   }

// ----------------------------------------------------------------------

void l_meterx (lista l, void *e, int (compar)(const void *, const void *))    {
	void *nuevo, *corr, *ant, *dato;

	if (!l)    {
		l_error (2, "l_meterx");
		exit (1);
	   }

	nuevo = (void *) malloc (sizeof (nuevo) + ((struct tlista *) l) -> tam);
	if (!nuevo)    {
		l_error (1, "l_meterx");
		exit (1);
	   }
	memcpy ((char *) nuevo + sizeof (nuevo), e, ((struct tlista *) l) -> tam);

	if (((struct tlista *) l) -> prim == NULL)    {
		memcpy (nuevo, &((struct tlista *) l) -> prim, sizeof (nuevo));
		((struct tlista *) l) -> prim = ((struct tlista *) l) -> ult = nuevo;
	   }
	else    {
		corr = ((struct tlista *) l) -> prim;
		ant = NULL;
                dato = (char *) malloc (((struct tlista *) l) -> tam);
                if (!dato)    {
                      l_error (1, "l_meterx");
                      exit (1);
                 }
		memcpy (dato, (char *) corr + sizeof (corr), ((struct tlista *) l) -> tam);

		while ((compar (e, dato) > 0) && corr)     {
			ant = corr;
			memcpy (&corr, (char *) corr, sizeof (corr));
			memcpy (dato, (char *) corr + sizeof (corr), ((struct tlista *) l) -> tam);
		   }

		memcpy ((char *) nuevo, &corr, sizeof (nuevo));
		if (ant == NULL)    ((struct tlista *) l) -> prim = nuevo;
		else  if (ant == ((struct tlista *) l) -> ult)     {
			      memcpy ((char *) ant, &nuevo, sizeof (nuevo));
			      ((struct tlista *) l) -> ult = nuevo;
			 }
		      else  memcpy ((char *) ant, &nuevo, sizeof (nuevo));

              free (dato);
	  }
   }

// ----------------------------------------------------------------------

int l_sacarx (lista l, void *e, int (compar)(const void *, const void *))    {
	void *viejo, *ant, *dato;

	if (!l)    {
		l_error (2, "l_sacarx");
		exit (1);
	   }
	if (((struct tlista *) l) -> prim == NULL)    {
		l_error (3, "l_sacarx");
		exit (1);
	   }

	viejo = ((struct tlista *) l) -> prim;
	ant = NULL;
        dato = (char *) malloc (((struct tlista *) l) -> tam);
        if (!dato)    {
               l_error (1, "l_sacax");
               exit (1);
           }
	memcpy (dato, (char *) viejo + sizeof (viejo), ((struct tlista *) l) -> tam);

	while ((compar (e, dato) != 0) && viejo)     {
		ant = viejo;
		memcpy (&viejo, (char *) viejo, sizeof (viejo));
		memcpy (dato, (char *) viejo + sizeof (viejo), ((struct tlista *) l) -> tam);
	   }
        free (dato);

	if (viejo != NULL)    {
		memcpy (e, (char *) viejo + sizeof (viejo), ((struct tlista *) l) -> tam);

		if (((struct tlista *) l) -> prim == viejo)
			memcpy (&((struct tlista *) l) -> prim, viejo, sizeof (viejo));
		else    {
			memcpy ((char *) ant, (char *) viejo, sizeof (viejo));
			if (((struct tlista *) l) -> ult == viejo)
				((struct tlista *) l) -> ult = ant;
		   }

		if (((struct tlista *) l) -> prim == NULL)
			((struct tlista *) l) -> ult = NULL;

		free (viejo);
		return (1);
	   }
	else return (0);
    }

// ----------------------------------------------------------------------

lista l_copiar (lista l)    {
	void *nueva, *corr, *dato;

	if (!l)    {
		l_error (2, "l_copiar");
		exit (1);
	   }

	nueva = l_nueva (((struct tlista *) l) -> tam);
	corr = ((struct tlista *) l) -> prim;
        dato = (char *) malloc (((struct tlista *) l) -> tam);
        if (!dato)    {
               l_error (1, "l_copiar");
               exit (1);
           }

	while (corr)   {
		memcpy (dato, (char *) corr + sizeof (corr), ((struct tlista *) l) -> tam);
		l_meterder (nueva, dato);
		memcpy (&corr, (char *) corr, sizeof (corr));
	  }

        free (dato);
	return (nueva);
   }

// ----------------------------------------------------------------------

int l_buscar (lista l, void *e, int (compar)(const void *, const void *))   {
	void *corr, *dato;

	if (!l)    {
		l_error (2, "l_buscar");
		exit (1);
	   }
	if (((struct tlista *) l) -> prim == NULL)    {
		l_error (3, "l_buscar");
		exit (1);
	   }

	corr = ((struct tlista *) l) -> prim;
        dato = (char *) malloc (((struct tlista *) l) -> tam);
        if (!dato)    {
               l_error (1, "l_buscar");
               exit (1);
           }
	memcpy (dato, (char *) corr + sizeof (corr), ((struct tlista *) l) -> tam);

	while ((compar (e, dato) != 0) && corr)     {
		memcpy (&corr, (char *) corr, sizeof (corr));
		memcpy (dato, (char *) corr + sizeof (corr), ((struct tlista *) l) -> tam);
	   }
        free (dato);

	if (corr != NULL)    {
		memcpy (e, (char *) corr + sizeof (corr), ((struct tlista *) l) -> tam);
		return (1);
	   }
	else  return (0);
   }

// ----------------------------------------------------------------------

void l_destruir (lista *l)    {
	void *viejo;

	if (!*l)    {
		l_error (2, "l_destruir");
		exit (1);
	   }

	viejo = ((struct tlista *) *l) -> prim;
	while (viejo)   {
		memcpy (&((struct tlista *) *l) -> prim, viejo, sizeof (viejo));
		free (viejo);
		viejo = ((struct tlista *) *l) -> prim;
	   }

	free (((struct tlista *) *l));
	*l = NULL;
    }

// ----------------------------------------------------------------------
//			FUNCIONES DEL ITERADOR
// ----------------------------------------------------------------------

void i_inicializar (lista l)    {

	if (!l)    {
		l_error (2, "il_inicializar");
		exit (1);
	   }
	if (((struct tlista *) l) -> prim == NULL)    {
		l_error (3, "il_inicializar");
		exit (1);
	   }

	((struct tlista *) l) -> iter = ((struct tlista *) l) -> prim;
   }

// ----------------------------------------------------------------------

void i_dame (lista l, void *e)    {
	void *corr;

	if (!l)    {
		l_error (2, "il_siguiente");
		exit (1);
	   }
	if (((struct tlista *) l) -> prim == NULL)    {
		l_error (3, "il_siguiente");
		exit (1);
	   }

	corr = ((struct tlista *) l) -> iter;
	memcpy (e, (char *) corr + sizeof (corr), ((struct tlista *) l) -> tam);
	memcpy (&((struct tlista *) l) -> iter, corr, sizeof (corr));
   }

// ----------------------------------------------------------------------

int i_quedan (lista l)    {

	if (!l)    {
		l_error (2, "il_quedan");
		exit (1);
	   }
	if (((struct tlista *) l) -> prim == NULL)    {
		l_error (3, "il_quedan");
		exit (1);
	   }

	if (((struct tlista *) l) -> iter != NULL)   return (1);
	else  return (0);
   }

// ----------------------------------------------------------------------




