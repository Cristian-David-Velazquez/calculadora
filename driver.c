#include "cdecl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define SIZE_BUFFER 100

struct operation{
    int param1;
    int param2;
    char operation;    //signo + o -
    int type;       //binario o entera
};

int PRE_CDECL asm_main( void ) POST_CDECL;
int parsear_comando(struct operation * operation, char * buffer);

int main()
{
    struct operation operation;
    char buffer[SIZE_BUFFER];

    printf("Bienvenido a la calculadora de SisCom de Octa y Cristian\n\n");
    printf("Aqui se puede sumar o restar enteros o binarios\n");
    printf("Ingresa la operacion separando los sumando por espacios \n\n");
    //TODO: hay que decirle que seleccione si va a ser binario o entero

    fgets(buffer, SIZE_BUFFER , stdin);

    parsear_comando(&operation, buffer);
    printf("\nPrint de operation:\nparam1:%d\noperation:%c\nparam1:%d\n\n", operation.param1,operation.operation,operation.param2);



    int ret_status;
    ret_status = asm_main();
    return ret_status;
}



/*  \brief          Divide el comando ingresado por el usuario y lo coloca en el struct de la operacion
 *  \param1[out]    struct de tipo operation donde se guardá el comando parseado
 *  \param2[in]     string que contiene el comando a parsear
 *  \return         Retorna -1 en caso de error o 0 en caso de exito. En el parámetro operation se retorna el comando
 *                  parseado y colocado dentro del struct de tipo operation
 * */

int parsear_comando(struct operation * operation, char * buffer){
    char * tokenAux;
    int intAux = 0;

    //parametro 1
    tokenAux = strtok(buffer, " ");
    intAux = atoi(tokenAux);
    if (intAux > 2147483647 || intAux < -2147483648){  //si el comando sale del limite máximo o mínimo de un int
        printf("El comando ingresado es incorrecto\n");
        return -1;
    }
    operation->param1 = intAux;

    //operando
    tokenAux = strtok(NULL, " ");
    if (tokenAux == NULL || strcmp(tokenAux, "+") != 0 && strcmp(tokenAux, "-") != 0){
        printf("El comando ingresado es incorrecto++\n");
        return -1;
    }
    //strcpy(operation->operation, tokenAux);
    //strncpy(operation->operation, tokenAux, 1);
    operation->operation = *tokenAux;

    //parametro 2
    tokenAux = strtok(NULL, " ");
    intAux = atoi(tokenAux);
    if (intAux > 2147483647 || intAux < -2147483648){  //si el comando sale del limite máximo o mínimo de un int
        printf("El comando ingresado es incorrecto--\n");
        return -1;
    }
    operation->param2 = intAux;

    //Comprobación de cantidad de argumentos
    tokenAux = strtok(NULL, " ");
    if (tokenAux != NULL){      //si tiene mas de 3 parametros
        printf("El comando ingresado es incorrecto\n");
        return -1;
    }


    return 0;
}
