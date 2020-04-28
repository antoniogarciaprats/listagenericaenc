// -----------------------------------------------------------------------

//      MODULO DE CABECERAS PARA USO DE OBJETOS LISTA GENERICA

// ----------------------------------------------------------------------

//	AUTOR: M¦ Jose Perez Romero - M¦ Angeles Morillo Jimenez
//	MODIFICACION: 12/12/1999

// ----------------------------------------------------------------------

#ifndef LISTAVOID

#define LISTAVOID

typedef void *lista;

lista l_nueva (unsigned int tam);
int l_vacia (lista l);
void l_meterder (lista l, void *e);
void l_meterizq (lista l, void *e);
void l_sacarder (lista l, void *e);
void l_sacarizq (lista l, void *e);
void l_meterx (lista l, void *e, int (compar)(const void *, const void *));
int l_sacarx (lista l, void *e, int (compar)(const void *, const void *));
lista l_copiar (lista l);
int l_buscar (lista l, void *e, int (compar)(const void *, const void *));
void l_destruir (lista *l);

void i_inicializar (lista l);
void i_dame (lista l, void *e);
int i_quedan (lista l);

#endif