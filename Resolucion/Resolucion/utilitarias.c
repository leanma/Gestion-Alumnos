#include<utilitarias.h>
#include<string.h>
#include<varias.h>


int cmp_dni_alumno(const void* a, const void* b)
{
    tAlumno* v1 = (tAlumno*)a;
    tAlumno* v2 = (tAlumno*)b;

    return v1->dni - v2->dni;
}

int baja (tAlumno * alu, FILE * arch, tArbolBinBusq* pa) // al alumno borrar del arbbol y b en el archivo
{
    tRegInd idx;
    tAlumno b_alum;
    idx.dni = alu->dni;

    buscarElemNoClaveArbolBinBusq(pa, &idx, sizeof(tRegInd), cmp_dni_alumno);

    fseek(arch, idx.nro_reg * sizeof(tAlumno), SEEK_CUR);

    fread(&b_alum, sizeof(tAlumno), 1, arch);

    b_alum.estado = 'B';

    fseek(arch, (-sizeof(tAlumno)), SEEK_CUR);

    fwrite(&b_alum, sizeof(tAlumno), 1, arch);

    eliminarElemNoClaveArbol(pa, &idx, cmp_dni_alumno);

    return TODO_OK;
}
