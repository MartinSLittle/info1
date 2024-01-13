//funcion que crea un arreglo de arreglos de manera dinamica e imprime el contenido de los mismos


#define OK 0
#define ERROR 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char**argv){

if(argc > 1)
{

int i = 0,estado = OK, cant_palabras = argc - 1;
char **str = NULL;

str = (char**)malloc(sizeof(char*)*(cant_palabras)); 
if(str != NULL){

    for(i = 0;i<cant_palabras;i++){

        (str[i]) =(char*) malloc(strlen(argv[i+1])*sizeof(char));

        if(str[i] != NULL) strcpy(str[i],(argv[i+1]));

    }
}
else estado = ERROR; 

if(estado != ERROR){

    for(i = 0;i<cant_palabras;i++) printf("%s ",(str[i]));

}


}


return 0;
}
