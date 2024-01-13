/*programa que escucha por 15 segundos cuantos ctrl C se ejecutaron. Si se ejecutaron
5, el programa te avisa y se va
*/





/* funciones utilizadas:

    //funcion que escribe los datos en el file descriptor, sacados del buffer y de tamaño count
    size_t write(int fd, const void *buf, size_t count); 
    
    //funcion signal.
    sighandler_t signal(int signum, sighandler_t handler);

    typedef void (*sighandler_t)(int);

    0(stdin)
    1(stdout)
    2(stderr)

*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int sig);

int main(void){

    char nombre[20], apellido[20];

    signal(SIGINT,sigint_handler);

    printf("decime tu nombre: ");
    scanf("%s",nombre);

    printf("decime tu apellido: ");
    scanf("%s",apellido);

    printf("hola %s %s \n",nombre,apellido);

    return 0;
}

void sigint_handler(int sig){


    const char msg[]= {"Soy el handler de SIGINT \n"};


    //indicamos que el FD es 0, el cual es stdin
    write(0,msg,sizeof(msg));

}