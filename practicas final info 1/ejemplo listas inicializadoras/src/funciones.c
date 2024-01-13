//En esta funcion, "lista" representa el puntero del inicio de la misma, por lo tanto
//si lista apunta a NULL significa que no hay elementos en la lista.

//si ya hay elementos en la lista, busco a través de todos los elementos de la lista 
//con el nodo auxiliar que apunta inicialmente a la cabeza de la lista. 
//La utilidad de este nodo es no perder la cabeza de la lista apuntada por lista.
 

#include "funciones.h"

int encolar_nodo(Nodo**lista,int valor){ 

    int estado = OK; 
    Nodo *nodo_nuevo = NULL;
    Nodo *nodo_aux = *lista; /* nodo que apunta al mismo lugar donde apunta *lista (es decir,
				el inicio de la lista)*/
    
    if(valor) 
    {

        nodo_nuevo =(Nodo*)malloc(sizeof(Nodo));

        if(nodo_nuevo == NULL) estado = ERROR;

        else{

            nodo_nuevo -> sig = NULL; //se apunta el nodo a NULL (final de la cola)
            nodo_nuevo -> dato = valor; //se cargan los datos en el nodo
            
            if(*lista == NULL) *lista = nodo_nuevo; //si no hay elementos en la lista, la cabeza de la misma (lista) apunta hacia el primer nodo
            
            else{ 

            while(nodo_aux-> sig != NULL) nodo_aux = nodo_aux -> sig; //se busca el último nodo de la lista, el cual estará apuntando a NULL
            
            nodo_aux -> sig = nodo_nuevo; // el nodo que antes apuntaba a null ahora apunta al nuevo nodo encolado
            }
        }
    }
    else estado = ERROR;

    return estado;
}

int encolar_nodo_ordenado(Nodo **lista, int valor)
{
    int estado = OK;
    Nodo *nodo_nuevo = NULL;
    Nodo *nodo_aux = *lista;
    Nodo *nodo_anterior = NULL;

    if(valor){

        //se crea el nodo
        nodo_nuevo = (Nodo*)malloc(sizeof(Nodo));

        if(nodo_nuevo == NULL) estado = ERROR;
        else{

            nodo_nuevo->dato = valor;
            //se inserta el nodo al principio de la cola si es el primer elemento o el valor es el mas chico
            
            
            if(*lista == NULL){
                nodo_nuevo->sig = NULL;            
                *lista = nodo_nuevo;

            }
            else if(valor <= nodo_aux -> dato ){
                nodo_nuevo -> sig = nodo_aux;
                *lista = nodo_nuevo;

            }

            //se recorre la lista para encontrar la posicion de inserción del nodo
            else {

                while(nodo_aux -> sig != NULL && valor > nodo_aux -> dato){

                   nodo_anterior = nodo_aux;
                   nodo_aux = nodo_aux -> sig;
                }
                
                if(nodo_aux -> sig != NULL){
                     
                     nodo_nuevo -> sig = nodo_aux; 
                    nodo_anterior -> sig = nodo_nuevo; 

                }
                else{
                    nodo_nuevo-> sig = NULL;
                    nodo_aux -> sig = nodo_nuevo;
                }
               
            }            
        }
    }

    return estado;
}

int desencolar_nodo(Nodo **lista){

    int estado = OK;
    Nodo *nodo_aux = *lista;
    
    if(lista != NULL){

        //se apunta la cabeza de la lista al segundo nodo
        *lista = nodo_aux -> sig;

        //se libera la memoria del nodo a desencolar
        free(nodo_aux);


    }
    else estado = ERROR;

    return estado;
}
