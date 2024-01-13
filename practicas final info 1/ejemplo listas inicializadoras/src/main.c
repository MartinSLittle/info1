#include "funciones.h"


int main(int argc, char**argv){

      int estado = OK,cant_elementos = argc - 1, i;
      Nodo * lista = NULL;
      Nodo * nodo_actual = NULL;

      if(cant_elementos > 0)
      {
        for(i = 1;i<=cant_elementos && estado == OK;i++){

            estado = encolar_nodo_ordenado(&lista,atoi(argv[i]));      
        } 
        
        if(estado == OK){
            
            nodo_actual = lista;
            
            while(nodo_actual != NULL){
             printf("%d \n",nodo_actual->dato);
            nodo_actual = nodo_actual ->sig;
        }        

        } else printf( "error en la lista \n");
       
      }
      else printf("no se pusieron elementos en el main /n");

    
    estado = desencolar_nodo(&lista);

    if(estado == OK){

      printf("nodo desencolado correctamente, ahora la lista queda como: \n");

      while(lista != NULL){

        printf("%d \n",lista -> dato);
        lista = lista ->sig;

      }


    }
    else printf("error en la liberacion de nodo \n");

          
    
    return 0;
}