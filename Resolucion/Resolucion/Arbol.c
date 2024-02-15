#include <stdio.h>
#include <stdlib.h>

#include "Arbol.h"
#include "Gestion.h"


void crear_arbol(t_arbol*pa)
{
  *pa=NULL;
}

int cargar_arbol_arch(t_arbol*pa,char*path,size_t tam)
{
  FILE*arch=fopen(path,"rb");
  if(!arch)
    return ERR_ARCHIVO;
  fseek(arch,0l,SEEK_END);
  int cant_reg=ftell(arch)/tam;
  rewind(arch);
  int r=cargar_arbol_gen(pa,arch,tam,0,cant_reg-1,copiar_arbol_arch);
  fclose(arch);
  return r;
}


int copiar_arbol_arch(void*dest,void*orig,size_t tam,int pos)
{
  FILE*arch=(FILE*)orig;
  fseek(arch,tam*pos,SEEK_SET);
  int r=fread(dest,tam,1,arch);
  return r;
}

int cargar_arbol_gen(t_arbol*pa,void*orig,size_t tam,int li,int ls,Copiar copiar_dato)
{
  int m=(li+ls)/2;
  int r;

  if(li>ls)
    return TODOO_OK;

  t_nodoa*nue=(t_nodoa*)malloc(sizeof(t_nodoa));
  if(!nue)
    return ERR_SIN_MEM;
  nue->info=malloc(tam);
  if(!nue->info)
  {
    free(nue);
    return ERR_SIN_MEM;
  }

  nue->tam=tam;
  nue->izq=nue->der=NULL;

  if((r=copiar_dato(nue->info,orig,tam,m)==0))
    return r;
  *pa=nue;
  if((r=cargar_arbol_gen(&(*pa)->izq,orig,tam,li,m-1,copiar_dato))!=TODOO_OK)
    return r;
  return cargar_arbol_gen(&(*pa)->der,orig,tam,m+1,ls,copiar_dato);
}


void recorrer_arbol_orden(t_arbol*pa,Accion accion,void*param)
{
  if(!*pa)
    return;
  recorrer_arbol_orden(&(*pa)->izq,accion,param);
  accion((*pa)->info,param);
  recorrer_arbol_orden(&(*pa)->der,accion,param);
}





t_arbol* mayor_nodo(t_arbol*pa)
{
  if(!*pa)
    return NULL;
  while((*pa)->der)
    pa=&(*pa)->der;
  return pa;
}

t_arbol* menor_nodo(t_arbol*pa)
{
  if(!*pa)
    return NULL;
  while((*pa)->izq)
    pa=&(*pa)->izq;
return pa;
}



int eliminar_raiz_arbol(t_arbol*pa,void*pd,size_t tam)
{
  t_arbol*rempl;
  t_nodoa*elim;
  int hi,hd;

  if(!*pa)
    return ERR_ARBOL_VACIO;

  memcpy(pd,(*pa)->info,MEN(tam,(*pa)->tam));
  free((*pa)->info);
  if(!(*pa)->izq && !(*pa)->der)
  {
    free(*pa);
    *pa=NULL;
    return TODOO_OK;
  }
  hi=altura_arbol(&(*pa)->izq);
  hd=altura_arbol(&(*pa)->der);
  rempl=hi>hd?mayor_nodo(&(*pa)->izq):menor_nodo(&(*pa)->der);
  elim=*rempl;
  (*pa)->info=elim->info;
  (*pa)->tam=elim->tam;
  *rempl=elim->izq?elim->izq:elim->der;
  free(elim);
  return TODOO_OK;
}



int altura_arbol(t_arbol*pa)
{
  int hi,hd;
  if(!*pa)
    return 0;
  hi=altura_arbol(&(*pa)->izq);
  hd=altura_arbol(&(*pa)->der);
  return(hi>hd?hi:hd)+1;
}



void vaciar_arbol(t_arbol*pa)
{
  if(!*pa)
    return;
  vaciar_arbol(&(*pa)->izq);
  vaciar_arbol(&(*pa)->der);
  free((*pa)->info);
  free(*pa);
  *pa=NULL;
}



void dar_de_alta(t_arbol*pa,FILE*arch)
{
  t_indice ind;
  t_alumno alu;
  ind.nro_reg=-1;

  printf("Ingrese el dni del alumno a dar de alta:\t");
  scanf("%d",&ind.dni);

  buscar_indice(pa,&ind,comparar_clave);
  if(ind.nro_reg!=-1)
  {
    if(alu.estado=='A')
      printf("\nALUMNO YA SE ENCUENTRA DADO DE ALTA\n");
    else
      alu.estado='A';
  }
  else
  {
    alu.dni=ind.dni;
    alu.estado='A';

    printf("Ingrese el nombre y apellido:\t");
    fflush(stdin);
    scanf("%s",alu.apyn);

    printf("Ingrese la cantidad de materias:\t");
    scanf("%d",&alu.cant_materias);

    printf("Ingrese el promedio:\t");
    scanf("%f",&alu.promedio);

    fseek(arch,0l,SEEK_END);
    fwrite(&alu,sizeof(t_alumno),1,arch);
    ind.dni=alu.dni;
    ind.nro_reg=ftell(arch)/sizeof(t_alumno)-1;
    ingresar_arbol(pa,&ind,sizeof(t_indice),comparar_clave);

    printf("\nALUMNO DADO DE ALTA\n");
  }
}


void dar_de_baja(t_arbol*pa,FILE*arch)
{
  t_indice ind;
  t_alumno alu;
  ind.nro_reg=-1;

  printf("Ingrese el dni del alumno a dar de baja:\t");
  scanf("%d",&ind.dni);

  buscar_indice(pa,&ind,comparar_clave);
  if(ind.nro_reg!=-1)
  {
    fseek(arch,ind.nro_reg*sizeof(t_alumno),SEEK_SET);
    fread(&alu,sizeof(t_alumno),1,arch);
    alu.estado='B';
    eliminar_indice(pa,&ind,comparar_clave);
    fseek(arch,-(long)sizeof(t_alumno),SEEK_CUR);
    fwrite(&alu,sizeof(t_alumno),1,arch);
    printf("\nALUMNO DADO DE BAJA CORRECTAMENTE\n");
  }
  else
  {
    printf("ALUMNO NO ENCONTRADO\n");
  }
}




void eliminar_indice(t_arbol*pa,t_indice* pd,Cmp cmp)
{
  if(!*pa)
    return;
  eliminar_indice(&(*pa)->izq,pd,cmp);
  if(cmp((*pa)->info,pd)==0)
  {
    eliminar_raiz_arbol(pa,pd,sizeof(t_indice));
    return;
  }
  eliminar_indice(&(*pa)->der,pd,cmp);
}


void buscar_indice(t_arbol*pa,void* pd,Cmp cmp)
{
  if(!*pa)
    return;
  buscar_indice(&(*pa)->izq,pd,cmp);
  if(cmp((*pa)->info,pd)==0)
  {
    memcpy(pd,(*pa)->info,(*pa)->tam);
  }
  buscar_indice(&(*pa)->der,pd,cmp);
}





int ingresar_arbol(t_arbol*pa,void*pd,size_t tam,Cmp cmp)
{
  while(*pa)
  {
    if(cmp(pd,(*pa)->info)<0)
      pa=&(*pa)->izq;
    else if(cmp(pd,(*pa)->info)>0)
      pa=&(*pa)->der;
    else
      return 0;
  }

  t_nodoa*nue=(t_nodoa*)malloc(sizeof(t_nodoa));
  if(!nue)
    return ERR_SIN_MEM;
  nue->info=malloc(tam);
  if(!nue->info)
  {
    free(nue);
    return ERR_SIN_MEM;
  }

  memcpy(nue->info,pd,tam);
  nue->tam=tam;
  nue->izq=nue->der=NULL;
  *pa=nue;
  return TODOO_OK;
}



int comparar_clave(const void*x,const void*y)
{
  t_indice indx=*(t_indice*)x;
  t_indice indy=*(t_indice*)y;
  if(indx.dni>indy.dni)
    return 1;
  if(indx.dni<indy.dni)
    return -1;
  return 0;
}



void grabar_indice(void*ind,void*arch)
{
  t_indice indice=*(t_indice*)ind;
  FILE* arc=(FILE*)arch;
  fwrite(&indice,sizeof(t_indice),1,arc);
}



void mostrar_indice(void*ind,void*x)
{
  t_indice in=*(t_indice*)ind;
  printf("%d\t%d\n",in.dni,in.nro_reg);
}

