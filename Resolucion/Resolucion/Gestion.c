#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Gestion.h"
#include "Arbol.h"



char menuu()
{
  char op;
  mostrar_menu();
  fflush(stdin);
  scanf("%c",&op);

  while(op!='1' && op!='2' && op!='3' && op!='4' && op!='5')
  {
    printf("\nOPCION NO VALIDA\n");
    mostrar_menu();
    fflush(stdin);
    scanf("%c",&op);
  }
  return op;
}

void mostrar_menu()
{
  printf("MENU:\n");
  printf("1-->MOSTRAR TODOS\n"
         "2-->MOSTRAR DE ALTA\n"
         "3-->DAR DE ALTA\n"
         "4-->DAR DE BAJA\n"
         "5-->SALIR\n");
  printf("INGRESE SU OPCION-->\t");
}



void mostrar_alumno(void*ind,void*arch_alu)
{
  t_alumno aux;
  t_indice indice=*(t_indice*)ind;
  FILE* arch=(FILE*)arch_alu;

  fseek(arch,indice.nro_reg*sizeof(t_alumno),SEEK_SET);
  fread(&aux,sizeof(t_alumno),1,arch);
  printf("%-3d\t%-30s\t%-5d\t%.2f\t%c\n",aux.dni,aux.apyn,aux.cant_materias,aux.promedio,aux.estado);
}


void mostrar_alumno_alta(void*ind,void*arch_alu)
{
  t_alumno aux;
  t_indice indice=*(t_indice*)ind;
  FILE* arch=(FILE*)arch_alu;

  fseek(arch,indice.nro_reg*sizeof(t_alumno),SEEK_SET);
  fread(&aux,sizeof(t_alumno),1,arch);
  if(aux.estado!='B')
    printf("%-3d\t%-30s\t%-5d\t%.2f\t%c\n",aux.dni,aux.apyn,aux.cant_materias,aux.promedio,aux.estado);
}




