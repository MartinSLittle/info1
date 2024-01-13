#define OK 0
#define ERROR 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct alumno{

char nombre[10];
char apellido[10];
int nota;

}Alumno;

int cargar_archivo(FILE* archivo,Alumno alumno );
