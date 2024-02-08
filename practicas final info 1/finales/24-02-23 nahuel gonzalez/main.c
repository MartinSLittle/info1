#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct producto
{
int codigo_Producto;
char proveedor[20];
int cantidad_stock ;
} Producto_t;
typedef struct nodo
{

Producto_t p;
struct nodo *sig;
} Nodo_t;

#define ERROR -1
#define INIT_LIST 1
#define YES 1
#define NO 0


int CargarProductos(const char* nombreArchivo, Producto_t **listado);

int FiltrarProductos(const Producto_t *listado, Nodo_t **listadoFiltrado, const char *nombreProveedor);


int CargarProductos(const char* nombreArchivo, Producto_t **listado)
{

    int init_lists = 0;
    Producto_t *listado_aux = NULL;
    Producto_t *producto = NULL;
    FILE* fp = NULL;
    size_t value;

    if(nombreArchivo != NULL){
    
        //se abre el archivo binario y se comprueba su correcta apertura

        fp = fopen(nombreArchivo, "rb");

        if(fp == NULL)
        { 
            init_lists = ERROR;
            exit(ERROR); 
        }

            
            do{
                value = fread(producto,sizeof(*producto),1,fp);

                //se comprueba que el archivo binario tenga al menos un producto para ser leido
                if(value == 1){
                    
                    //se pide memoria para el primer elemento de la lista
                    if(init_lists == 0){
                        
                        *listado = (Producto_t*)malloc(sizeof(Producto_t));

                        if(*listado == NULL){
                            init_lists = ERROR;
                            fclose(fp);
                            exit(ERROR);}
                        
                        listado[0]->cantidad_stock = producto->codigo_Producto;

                    }
                    //se pide memoria para mas elementos de la lista
                    else if(init_lists != 0){

                        listado_aux =(Producto_t*)realloc(*listado,sizeof(Producto_t) * (init_lists + 1));
                    
                        if(listado_aux == NULL){
                            
                            init_lists = ERROR;
                            fclose(fp);
                            free(*listado);
                            exit(ERROR);}
                        
                    //se carga los miembros  
                    listado_aux[init_lists].codigo_Producto = producto->codigo_Producto;
                    strcpy((listado_aux[init_lists].proveedor),(producto->proveedor));
                    listado_aux[init_lists].cantidad_stock = producto->cantidad_stock;    

                    *listado = listado_aux;    
                    }
                
                init_lists++;
                }
            
            } while (value == 1); /*otra alternativa seria hacer while(!feof(fp)); */ 

            fclose(fp);    
    }

return init_lists;

}   
    

int FiltrarProductos(const Producto_t *listado, Nodo_t **listadoFiltrado, const char *nombreProveedor){

    int estado = 0, list_len = 0,i = 0;
    Nodo_t *nodo_nuevo = NULL;
    Nodo_t *nodo_aux = *listadoFiltrado; //nodo_aux apunta a la cabeza de la lista

    if(listado != NULL && listadoFiltrado != NULL){
    
    //se obtiene la longitud de la lista

    while(listado[list_len].codigo_Producto != 0) list_len++;

    if(!list_len){
        
        estado = ERROR;
        exit(ERROR);
    }  

    //se recorre la lista viendo el criterio de filtro 
    for(i = 0;i<list_len;i++){

        //si strcasecmp devuelve cero, es decir, se cumple el criterio de filtrado
        if((!strcasecmp(listado[i].proveedor,nombreProveedor))){
        
        //Se pide la memoria para el nodo a encolar
        nodo_nuevo = (Nodo_t*)malloc(sizeof(Nodo_t));

        if(nodo_nuevo == NULL){
            estado = ERROR;
            exit(ERROR);
        }  

        //Se cargan los datos del nuevo elemento de la lista al nodo

        nodo_nuevo->p.cantidad_stock = listado[i].cantidad_stock;
        nodo_nuevo->p.codigo_Producto = listado[i].codigo_Producto;
        strcpy((nodo_nuevo->p.proveedor),(listado[i].proveedor));

        //si es el primer elemento a encolar
        if(*listadoFiltrado == NULL){

        *listadoFiltrado = nodo_nuevo; //la cabeza de la lista apunta al nodo nuevo
        nodo_nuevo->sig = NULL; //el nodo nuevo apunta a null, es decir, es el ultimo elemento
        }
        
        // si no es el primer elemento a encolar
        else{

            while(nodo_aux ->sig != NULL) nodo_aux = nodo_aux ->sig;

            nodo_aux->sig = nodo_nuevo;  
            nodo_nuevo->sig = NULL;        

        }
    }

    }
    }
    else estado = ERROR;

return estado;
}


int main(int argc, char**argv){

    FILE *fp = NULL;
    char nombreArchivoBinario[20];
    char proveedorAfiltrar[20];
    int codigoProducto = 0,cantidadStock = 0,flag = 0,cant_productos = 0;
    Producto_t **listado = NULL;
    
    if(argc != 3){
    printf("cantidad de argumentos de main insuficientes \n");
    exit(ERROR);
    }

    strcpy(nombreArchivoBinario,argv[1]);
    strcpy(proveedorAfiltrar,argv[2]);

    
    do
    {
        printf("ingrese el codigo de su producto: ");
        scanf("%d",&codigoProducto);
        printf("ingrese la cantidad de stock: ");
        scanf("%d",&cantidadStock);

        fp = fopen(nombreArchivoBinario,"w+b");

        if(fp == NULL){
        printf("error en la apertura del archivo \n");
        exit(ERROR);
        }

        fwrite(&codigoProducto,sizeof(codigoProducto),1,fp);
        fwrite(&cantidadStock,sizeof(cantidadStock),1,fp);
        fwrite(&proveedorAfiltrar,sizeof(proveedorAfiltrar),1,fp);

        printf("datos cargados correctamente. desea seguir cargando mas productos?   SI(1)   NO(0)");
        scanf("%d",&flag);

        
    } while (flag == YES);
    
    
    cant_productos = CargarProductos(nombreArchivoBinario, listado);

    if(cant_productos == ERROR){
        printf("error en la carga de productos a la lista \n");
        fclose(fp);
        exit(ERROR);
    }

    printf("se cargaron %d elementos a la lista \n",cant_productos);


    return 0;
}