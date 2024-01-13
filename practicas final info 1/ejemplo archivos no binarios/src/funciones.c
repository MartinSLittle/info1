#include "funciones.h"


/*int cargar_estructura(char *nombre, char* apellido, char* nota){

    int estado = OK;

    if(nombre != NULL && apellido != NULL && nota != 0){

    


    }
    else estado = ERROR;

    return estado;
}

*/
int cargar_archivo(FILE *archivo,Alumno alumno ){

    int estado = OK,i,cant_alumnos = sizeof(alumno)/sizeof(Alumno);
    char *arreglo = NULL;
    if(estado == OK && archivo != NULL){

        fprintf(archivo,"%s,%s,%d\n",alumno.nombre,alumno.apellido,alumno.nota);

       

    }
    else estado = ERROR;

    return estado;
}


