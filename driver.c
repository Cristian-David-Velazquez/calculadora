#include "cdecl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define SIZE_BUFFER 100

struct operation{
    int param1;
    int param2;
    char operation; //signo + o -
    int type;       //binario o entera
};

int PRE_CDECL asm_main() POST_CDECL;
//extern int _assemblySum(int x, int y);
int asm_sum_int( int a, int b) __attribute__ ((cdecl ));
int asm_rest_int( int a, int b) __attribute__ ((cdecl ));
int parsear_comando(struct operation * operation, char * buffer);



int main()
{
    struct operation operation;
    char buffer[SIZE_BUFFER];
    int resultado = 0;
    int error = 0;

    printf("Bienvenido a la calculadora de SisCom de Octa y Cristian\n\n");
    printf("Aqui se puede sumar o restar enteros o binarios\n");
    printf("Ingresa la operacion separando los sumando por espacios o \"fin\" para salir\n");
    //TODO: hay que decirle que seleccione si va a ser binario o entero

    while (1)
    {
        error = 0;
        printf("\n--------------------\n");
        printf("\nOperación: ");
        fgets(buffer, SIZE_BUFFER , stdin);
        
        if (strcmp(buffer, "fin\n") == 0){
            return 0;
        }

        if (parsear_comando(&operation, buffer) == -1){
            error = -1;
        }
        //printf("\nPrint de operation:\nparam1:%d\noperation:%c\nparam1:%d\n\n", operation.param1,operation.operation,operation.param2);

        if (error != -1){

            switch(operation.operation){
            case '+':
                resultado = asm_sum_int( operation.param1, operation.param2);
                break;
            case '-':
                resultado = asm_rest_int( operation.param1, operation.param2);
                break;
            default:break;
        }
        
            if (resultado != -1){
                printf("\nResultado: %d\n", resultado);
            } else {
                printf("\nResultado: Se ha producido un desbordamiento\n");
            }
        } 

    }
    

    //ret_status = asm_main();
    return 0;
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
    //if (intAux > 2147483647 || intAux < -2147483648){  //si el comando sale del limite máximo o mínimo de un int
    if (intAux == 2147483647 || intAux == -2147483648){  //si el comando sale del limite máximo o mínimo de un int
        printf("El comando ingresado es incorrecto\n");
        return -1;
    }
    operation->param1 = intAux;

    //operando
    tokenAux = strtok(NULL, " ");
    if (tokenAux == NULL || strcmp(tokenAux, "+") != 0 && strcmp(tokenAux, "-") != 0){
        printf("El comando ingresado es incorrecto\n");
        return -1;
    }
    //strcpy(operation->operation, tokenAux);
    //strncpy(operation->operation, tokenAux, 1);
    operation->operation = *tokenAux;

    //parametro 2
    tokenAux = strtok(NULL, " ");
    intAux = atoi(tokenAux);
    if (intAux == 2147483647 || intAux == -2147483648){  //si el comando sale del limite máximo o mínimo de un int
        printf("El comando ingresado es incorrecto\n");
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
