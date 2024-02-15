#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TODOO_OK          1
#define ERR_ARBOL_VACIO   0

#define MEN(a,b)    (a)<(b)?(a):(b)

typedef struct s_nodoa
{
  void* info;
  size_t tam;
  struct s_nodoa*izq,*der;
}t_nodoa;

typedef t_nodoa* t_arbol;


typedef struct
{
	int dni;
	int nro_reg;
}t_indice;


typedef int(*Cmp) (const void*,const void*);
typedef void(*Accion) (void*,void*);
typedef int(*Copiar) (void*,void*,size_t,int);


void crear_arbol(t_arbol*pa);
int cargar_arbol_arch(t_arbol*pa,char*path,size_t tam);
int cargar_arbol_gen(t_arbol*pa,void*orig,size_t tam,int li,int ls,Copiar copiar_dato);
void recorrer_arbol_orden(t_arbol*pa,Accion accion,void*param);
int eliminar_raiz_arbol(t_arbol*pa,void*pd,size_t tam);
int altura_arbol(t_arbol*pa);
t_arbol* mayor_nodo(t_arbol*pa);
void vaciar_arbol(t_arbol*pa);
int ingresar_arbol(t_arbol*pa,void*pd,size_t tam,Cmp cmp);
int copiar_arbol_arch(void*dest,void*orig,size_t tam,int pos);

void buscar_indice(t_arbol*pa,void* pd,Cmp cmp);
void eliminar_indice(t_arbol*pa,t_indice* pd,Cmp cmp);
void mostrar_indice(void*ind,void*x);
void grabar_indice(void*ind,void*arch);

int comparar_clave(const void*x,const void*y);

void dar_de_baja(t_arbol*pa,FILE*arch);
void dar_de_alta(t_arbol*pa,FILE*arch);


#endif // ARBOL_H_INCLUDED
