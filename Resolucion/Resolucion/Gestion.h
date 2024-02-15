#ifndef RESOLUCION_H_INCLUDED
#define RESOLUCION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TODOO_OK          1
#define ERR_ARCHIVO       0
#define ERR_SIN_MEM       0


typedef struct{
    int dni;
    char apyn[40];
    int cant_materias;
    float promedio;
    char estado;
}t_alumno;





char menuu();
void mostrar_menu();

void mostrar_alumno(void*ind,void*arch_alu);
void mostrar_alumno_alta(void*ind,void*arch_alu);



#endif // RESOLUCION_H_INCLUDED
