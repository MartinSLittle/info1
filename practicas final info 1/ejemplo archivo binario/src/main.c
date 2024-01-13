#include "funciones.h"


int main(int argc, char**argv){

  FILE *archivo_bin = NULL;
  Alumno alumno;
  int estado;
  
  //se evalua si hubo ingreso de nombre por consola
  if(argc > 1){

    strcpy(alumno.nombre,"martin");
    strcpy(alumno.apellido,"little");
    alumno.edad = 22;

    init_archivo(&archivo_bin,argv[1],"a+b");

    estado = cargar_archivo(&archivo_bin,&alumno,1);

    if(estado == ERROR) printf("error en el cargado del archivo \n");

    else{

        estado = imprimir_archivo(archivo_bin,1);
        if(estado == ERROR) printf("error en la impresion del archivo \n");

        else{
              printf("impresion correcta\n");

        }
    }



  }
  else printf("no se indicó el nombre del archivo \n");
     
          


  return 0;
}