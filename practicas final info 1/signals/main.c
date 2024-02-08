#include "funciones.h"

int main(void){

    signal(SIGUSR1,signalhandler);
    signal(SIGUSR2,signalhandler);
    signal(SIGINT,signalhandler);

    fprintf(stdout,"esperando seniales... \n");

    while(1);

    return 0;
}


