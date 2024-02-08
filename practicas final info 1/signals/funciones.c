#include "funciones.h"

void signalhandler(int signum){

    switch (signum){

        case SIGUSR1: fprintf(stdout,"SIGUSR1 recibido \n"); break;
        case SIGUSR2: fprintf(stdout,"SIGUSR2 recibido \n"); break;
        case SIGINT:
            
        fprintf(stdout,"\n programa terminado, saliendo.. \n"); 
        exit(EXIT_SUCCESS);
        break;
            
    }
    
}