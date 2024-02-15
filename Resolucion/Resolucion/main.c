#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Gestion.h"
#include "Arbol.h"

#define PATH_ARCH_ALUMNOS "../archivos/alumnos.dat"
#define PATH_ARCH_INDICE "../archivos/alumnos.idx"

int main()
{
    char op;

    t_arbol arbol;

    crear_arbol(&arbol);

    cargar_arbol_arch(&arbol,PATH_ARCH_INDICE,sizeof(t_indice));


    FILE*arch_alu=fopen(PATH_ARCH_ALUMNOS,"r+b");
    if(!arch_alu)
      return ERR_ARCHIVO;

    op=menuu();
    while(op!='5')
    {
      switch(op)
      {
      case '1':
        {
          recorrer_arbol_orden(&arbol,mostrar_alumno,arch_alu);
          break;
        }
      case '2':
        {
          recorrer_arbol_orden(&arbol,mostrar_alumno_alta,arch_alu);
          break;
        }
       case '3':
        {
          dar_de_alta(&arbol,arch_alu);
          break;
        }
       case '4':
        {
          dar_de_baja(&arbol,arch_alu);
          break;
        }
        case '5':
        {
          break;
        }
      }
      if(op!='5')
        op=menuu();
    }

    printf("Indice:\n");

    recorrer_arbol_orden(&arbol,mostrar_indice,0);

    FILE*arch_ind=fopen(PATH_ARCH_INDICE,"wb");
    recorrer_arbol_orden(&arbol,grabar_indice,arch_ind);
    fclose(arch_ind);
    fclose(arch_alu);

    vaciar_arbol(&arbol);

    return 0;
}


