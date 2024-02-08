/**
 * para compilar:
 * $gcc -Wall app.c sock-lib.c -o app
 *
 * para realizar pruebas, abrir dos terminales
 * 1) terminal servidor
 * $./app
 *
 * 2) terminal cliente (utilizando netcat)
 * $echo "25;2.2" | nc localhost 8000
 * $echo "26;2.1" | nc localhost 8000
 * $echo "a#;2,3xxxxxxxxxxxxxxxxxxxxxxxxxx" | nc localhost 8000
 * $echo "27;2.3" | nc localhost 8000
 *
 * para terminar y que se cierre rl archivo
 * $pkill -15 -f app
 *
 **/

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
#define BUFFER_LEN 512

#define ERROR -1
#define OK 1

void signal_handle_sigterm(int signum);
int csv_to_struct(char *str, info_t *data);

// variables globales
int count = 0;
FILE *fp1;
int sock;

int main(int argc, char **argv) {
    int sockdup;
    info_t data;
    int r;

    char buffer[BUFFER_LEN];

    // valores por deafult
    int puerto = PORT_DEFAULT;
    char base_de_datos[80] = DATABASE_FILE;

    // reemplazo el valor por default del puerto con argumentos del main
    if (argc == 2) {
        puerto = atoi(argv[1]);
    }

    fprintf(stdout, "debug:: puerto: %d\n", puerto);

    signal(SIGTERM, signal_handle_sigterm);

    fp1 = fopen(base_de_datos, "a");
    if (fp1 == NULL) {
        fprintf(stderr, "fallo en abrir base de datos\n");
        exit(-1);
    }

    sock = abrir_conexion(PORT_DEFAULT, CONNECTION_MAX, 1);
    if (sock == -1) {
        fprintf(stderr, "fallo abrir_conexion()\n");
        exit(-1);
    }

    // reseteo el contador de conexiones recibidadas
    count = 0;

    while (1) {
        // string vacio
        memset(buffer, 0, BUFFER_LEN);

        sockdup = aceptar_pedidos(sock, 1);

        // recibo un string formato csv
        read(sockdup, buffer, BUFFER_LEN);

        // lo pongo en una estructura
        r = csv_to_struct(buffer, &data);

        // lo guardo en un archivo si no hubo errores
        // y devuelvo el string "VALID" i "INVALID"
        if (r == OK) {
            fwrite(&data, sizeof(info_t), 1, fp1);
            write(sockdup, VALID, strlen(VALID));
        } else {
            write(sockdup, INVALID, strlen(INVALID));
        }

        // contador desde que se re-inicio el proceso
        count++;

        // cierro el socket del lado servidor
        close(sockdup);
    }

    return 0;
}

void signal_handle_sigterm(int signum) {
    printf("=== fin === \n");
    printf("se recibieron %d mensajes\n", count);
    close(sock);
    fclose(fp1);
    exit(EXIT_SUCCESS);
}

int csv_to_struct(char *buffer, info_t *data) {
    char *token;

    // debug
    printf("recv :: %s len=%ld\n", buffer, strlen(buffer));

    // solo valido que el str no sea > 10 caracteres

    if (strlen(buffer) > 10) {
        data->id = 0;
        data->val = 0.0;
        return ERROR;
    }

    // utilizar strtok para dividir el string en tokens
    token = strtok(buffer, TOKEN);
    if (token == NULL) return ERROR;
    data->id = atoi(token);

    token = strtok(NULL, TOKEN);
    if (token == NULL) return ERROR;
    data->val = atof(token);

    return OK;
}
