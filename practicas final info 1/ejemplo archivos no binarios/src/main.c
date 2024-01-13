/* Crear un programa que reciba por linea de comando el nombre del archivo a crear. 
Escriba en dicho archivo la siguiente informacion resultante de una estructura:
Nombre, apellido, nota
XXX,YYY,20
Imprima por pantalla el contenido escrito del archivo*/

#include "funciones.h"

int main(int argc, char **argv)
{

    Alumno alumno;
    Alumno buff;
    int *nota = buff.nota;
    int estado = OK;
    FILE *archivo = NULL;
    char nombre_archivo[30];
    char buffer[100];

    if(argc > 1)
    { // si se ingresó por consola un nombre para el archivo

        strcpy(nombre_archivo,(argv[1]));

        archivo = fopen(nombre_archivo,"a+"); //copio el nombre ingresado por consola en el nombre del archivo, e indico que se cree para escritura y lectura
    
        if(archivo != NULL)
        {

            //cargo los parametros de la estructura
            strcpy(alumno.nombre,"martin");
            strcpy(alumno.apellido,"Little");
            alumno.nota = 7;

            estado = cargar_archivo(archivo,alumno);

            if(estado == OK)
            {
                //se coloca el puntero de posicion del archivo al incio
                rewind(archivo); 
                
                printf("%s \n",fgets(buffer,sizeof(buffer),archivo));

               
                fclose(archivo);


            }
    
        } 
    }
    else printf("error en la apertura del archivo \n");  

    return 0;
}