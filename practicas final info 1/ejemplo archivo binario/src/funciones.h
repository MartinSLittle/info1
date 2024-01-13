#define OK 1
#define ERROR 0 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct alumno{

    char nombre[20];
    char apellido[20];
    int edad;


}Alumno;

int imprimir_archivo(FILE *archivo,int cant_alumnos);
void init_archivo(FILE ** archivo,char * nombre_archivo,char *tipo_archivo);
int cargar_archivo(FILE **archivo,Alumno * alumno,int cant_alumnos);
