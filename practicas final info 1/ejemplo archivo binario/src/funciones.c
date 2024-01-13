/* ejercicio: crear un archivo cuyo nombre se indique por la consola. A ese archivo se le debe 
cargar los datos de un alumno de una estructura que tendra nombre, apellido y edad. 
Luego, se debera imprimir todos los alumnos cargados*/
#include "funciones.h"

void init_archivo(FILE ** archivo,char * nombre_archivo,char *tipo_archivo){

    if(archivo != NULL) *archivo = fopen(nombre_archivo,"a+b");
        
    
}

int cargar_archivo(FILE **archivo,Alumno * alumno,int cant_alumnos){
    
    int estado = OK;
    if(archivo != NULL && alumno != NULL){

        //se escribe en el archivo binario la cantidad de bytes que hay en el arreglo de alumnos
        size_t cantidad_leida = fwrite(alumno,sizeof(Alumno),cant_alumnos,*archivo);
        printf("cantidad leida por fwrite: %d \n",cantidad_leida);

    }
    else estado = ERROR;
    
    return estado;
}


int imprimir_archivo(FILE *archivo,int cant_alumnos){

    int estado = OK;
    Alumno alumno;
    int cant_leida;
    
    if(archivo != NULL){

            while(!feof(archivo)){

            rewind(archivo);
            fread(&alumno,sizeof(Alumno),sizeof(Alumno),archivo);
            }

        printf("%s,%s,%d \n",alumno.nombre,alumno.apellido,alumno.edad);
        
        
    }
    
    else estado = ERROR;

    return estado;
}