// gcc -Wall app.c sock-lib.c datetime.c -o app

#include <signal.h>
#include <stdio.h>

#include "info.h"
#include "sock-lib.h"

#define PORT_DEFAULT 8000
#define CONNECTION_MAX 10
#define DATABASE_FILE "database.bin"
#define TOKEN ";"
#define VALID "VALID"
#define INVALID "INVALID"   
#define BUFFER_LENGTH 100


int backlog_count = 0;
FILE*fp;

int main(int argc, char **argv) {
    
    int socket_fd,new_socket_fd,port =PORT_DEFAULT;
    info_t data;
    char buffer[BUFFER_LENGTH];

    if(argc != 2){

        fprintf(stderr,"puerto no ingresado \n");
        exit(EXIT_FAILURE);
    }

    //obtengo el puerto pasado por argumento de main 
    port = atoi(argv[1]);

    //abro el archivo binario donde se almacenaran los datos de la estructura
    fp = fopen(DATABASE_FILE,"w+b");
    
    if(fp == NULL){
        fprintf(stderr, "error en la apertura o creacion del archivo \n");
        exit(EXIT_FAILURE);
    }


    // se usa la funcion abrir_conexion para abrir el socket y enlazarlo (bind)
    socket_fd = abrir_conexion(port,CONNECTION_MAX,1);

    if(socket_fd == ERROR){

        fprintf(stderr,"error en la apertura del socket. \n");
        exit(EXIT_FAILURE);

    }
    // se prepara para aceptar conexiones del cliente

    while(1){

        new_socket_fd = aceptar_pedidos(socket_fd,1);

        if(new_socket_fd == ERROR){

            fprintf(stderr,"error en la conexion \n");
        }
        //obtenemos el file descriptor del mensaje enviado con los datos
        else{

        recv(new_socket_fd,buffer,BUFFER_LENGTH,0);




        }

    
    }

    

    


    return 0;
}
