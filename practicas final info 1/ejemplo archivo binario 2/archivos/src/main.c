#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct usuario
{
    char nombre[10];
    char apellido[10];
    int nota;
}Usuario;


int main(int argc,char **argv)
{
    Usuario *usuarios=NULL, *aux=NULL,destino[3];
    int cant_usuarios, camp_estructura, i;
    FILE *pArchivo=NULL;

    camp_estructura=3;

    cant_usuarios= ((argc-1)/camp_estructura);
    aux=(Usuario*)realloc(usuarios, cant_usuarios*sizeof(Usuario));
    if(aux != NULL)
    {
        usuarios=aux;
        for(i=0 ; i<cant_usuarios ; i++)
        {
            strcpy((usuarios+i)->nombre, *(argv+1+(camp_estructura*i)));
            strcpy((usuarios+i)->apellido, *(argv+2+(camp_estructura*i)));
            (usuarios+i)->nota=atoi(argv[3+(camp_estructura*i)]);
        }
        
        for (i = 0; i < cant_usuarios; i++) 
        {
            printf("Usuario %d:\n", i + 1);
            printf("Nombre: %s\n", usuarios[i].nombre);
            printf("Apellido: %s\n", usuarios[i].apellido);
            printf("Nota: %d\n", usuarios[i].nota);
            printf("\n");
        }

        pArchivo=fopen("familia.db", "a+b ");
        if( pArchivo != NULL)
        {
            fwrite( usuarios , sizeof(Usuario) , cant_usuarios , pArchivo );
            fseek(pArchivo , 0 , SEEK_SET);
            fread( destino , sizeof(Usuario), cant_usuarios , pArchivo );

            for (i = 0; i < cant_usuarios; i++) 
            {
                printf("Usuario bajado del archivo%d:\n", i + 1);
                printf("Nombre: %s\n", destino[i].nombre);
                printf("Apellido: %s\n", destino[i].apellido);
                printf("Nota: %d\n", destino[i].nota);
                printf("\n");
            }

            fclose(pArchivo);
        }

        free(usuarios);
    }
    return 0;
}

