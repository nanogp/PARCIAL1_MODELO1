#include "General.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void ejecutarEnConsola(const char *lineaDeComando)
{
    printf("\n");
    system(lineaDeComando);
}

char pedirConfirmacion(const char *mensajeAlUsuario)
{
    char retorno;

    printf("\n%s (S/N): ", mensajeAlUsuario);
    fflush(stdin);
    scanf("%c", &retorno);

    do
    {
        switch(retorno)
        {
            case 'S':
            case 's':
                retorno = 'S';
                break;
            case 'N':
            case 'n':
                retorno = 'N';
                break;
            default:
                printf("\nPor favor ingrese 'S' o 'N': ");
                fflush(stdin);
                scanf("%c", &retorno);
                break;
        }
    }
    while(retorno != 'S' && retorno != 'N');

    return retorno;
}

int pedirInt(const char mensajeIngreso[])
{
    int retorno;

    printf("%s", mensajeIngreso);
    fflush(stdin);
    scanf("%d", &retorno);


    return retorno;
}

int pedirIntValido(const char mensajeIngreso[], const char mensajeReingreso[], const int limiteInferior, const int limiteSuperior)
{
    int retorno;

    retorno = pedirInt(mensajeIngreso);

    while(retorno < limiteInferior || retorno > limiteSuperior)
    {
        retorno = pedirFloat(mensajeReingreso);
    }

    return retorno;
}

float pedirFloat(const char mensajeIngreso[])
{
    float retorno;

    printf("%s", mensajeIngreso);
    fflush(stdin);
    scanf("%f", &retorno);


    return retorno;
}

float pedirFloatValido(const char mensajeIngreso[], const char mensajeReingreso[], const float limiteInferior, const float limiteSuperior)
{
    float retorno;

    retorno = pedirFloat(mensajeIngreso);

    while(retorno < limiteInferior || retorno > limiteSuperior)
    {
        retorno = pedirFloat(mensajeReingreso);
    }

    return retorno;
}

void pedirString(char *retorno, const char mensajeIngreso[])
{
    printf("%s", mensajeIngreso);
    fflush(stdin);
    gets(retorno);
}

void pedirStringValido(char *retorno, const char mensajeIngreso[], const char mensajeReingreso[], const int limite)
{
    char stringIngresado[1000];

    pedirString(stringIngresado, mensajeIngreso);

    while(strlen(stringIngresado) > limite)
    {
        printf("\nEl texto ingresado supera el l¡mite de %d caracteres establecido.", limite);
        pedirString(stringIngresado, mensajeIngreso);
    }

    strcpy(retorno, stringIngresado);
}

float calcularPromedio(float numero1, float numero2)
{
    float retorno;

    retorno = (numero1 + numero2) / 2;

    return retorno;
}

int buscarEnArrayInt(const int buscar, const int array[], const int cant)
{
    int retorno = -1;
    int i;

    for(i=0 ; i<cant ; i++)
    {
        if(array[i] == buscar)
        {
            retorno = i;
            break;
        }
    }

    return retorno;
}

void imprimirEnPantalla(const char *texto)
{
    printf("%s", texto);
}

void generarTitulo(char *texto)
{
    int i;
    char nuevoTitulo[LARGO_TITULO] = "| ";

    strcat(nuevoTitulo, texto);
    strcat(nuevoTitulo, " |");

    strcpy(texto, "\n+");
    for(i=0 ; i<strlen(nuevoTitulo)-2 ; i++)
    {
        strcat(texto, "-");
    }
    strcat(texto, "+\n");

    strcat(texto, nuevoTitulo);

    strcat(texto, "\n+");
    for(i=0 ; i<strlen(nuevoTitulo)-2 ; i++)
    {
        strcat(texto, "-");
    }
    strcat(texto, "+");

}

void imprimirTitulo(const char *texto)
{
    char titulo[LARGO_TITULO];
    strcpy(titulo, texto);
    generarTitulo(titulo);
    imprimirEnPantalla(titulo);
}
