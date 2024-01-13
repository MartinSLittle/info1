#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define ERROR -1
#define OK 0

int main(int argc, char**argv){

    int pipefd[2], estado; 
    pid_t pid;
    char buff;

    //se crea el pipe 

    estado = pipe(pipefd);

    //si el pipe no se creó correctamente, se cierra cada fd y se sale del programa
    if(estado == ERROR){

        perror("error en la creacion del pipe");
        close(pipefd[0]); close(pipefd[1]);
        exit(EXIT_FAILURE);
    }
    
    //si el pipe se creó correctamente, creamos el nuevo proceso
    else if(estado == OK){


        pid = fork();

        //si el proceso hijo no se creó correctamente
        if(pid == ERROR){

            close(pid);
            exit(EXIT_FAILURE);
        }
        //si nos encontramos en el proceso hijo
        else if(pid == 0){

            // se cierra el file descriptor de escritura. el proceso hijo solo leerá
            close(pipefd[1]);

            while((read(pipefd[0],&buff,sizeof(buff))> 0)){

                //se escribe sobre un file descriptor
                write(STDOUT_FILENO,&buff,1);
            }
           
           write(STDOUT_FILENO, "\n", 1);

            close(pipefd[0]);
            exit(EXIT_SUCCESS);
        }
        //si nos encontramos en el proceso padre
        else if(pid > 0){

        close(pipefd[0]);
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);          /* Reader will see EOF */
        wait(NULL);                /* Wait for child */
        exit(EXIT_SUCCESS);



        }
        
    

    }

    return 0;
}