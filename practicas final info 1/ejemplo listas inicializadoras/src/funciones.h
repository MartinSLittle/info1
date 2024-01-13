#define OK 1
#define ERROR 0 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo{ //una estructura con dos componentes dentro. Por un lado, el dato de tipo char
                    //y por otro lado, un puntero de tipo struct nodo para poder apuntar a otro 
                    //del mismo tipo

    char dato;
    struct nodo* sig;

}Nodo;

int encolar_nodo(Nodo **lista,int valor);
int encolar_nodo_ordenado(Nodo **lista, int valor);
int desencolar_nodo(Nodo **lista);