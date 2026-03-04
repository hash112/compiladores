#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    if(argc < 2) 
    {
        printf("Se espera un argumento\n");        
        return 1;
    }

    char *archivo = argv[1];
    FILE *fptr;

    fptr = fopen(archivo, "r");

    if(fptr == NULL)
    {
        printf("No se encontró el archivo: %s\n", archivo);
        return 1;
    } 

    printf("Éxito\n");
    return 0;
}