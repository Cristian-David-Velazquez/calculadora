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
/*Convierte binarios a enteros*/
void binDec (int n);
 char src[50], dest[50]="";
int main()
{
    struct operation operation;
    char buffer[SIZE_BUFFER];
    int resultado = 0;
    int error = 0;
    int entero1;
    int entero2;
    printf("Bienvenido a la calculadora de SisCom de Octa y Cristian\n\n");
    printf("Aqui se puede sumar o restar enteros o binarios\n");
    printf("Ingresa la operacion separando los sumando por espacios o \"fin\" para salir\n");
    printf("Ingrese antes de la operacion e para enteros o b para binarios\n");
    printf("ejemplo b 1000 + 1111\n");
    //TODO: hay que decirle que seleccione si va a ser binario o entero

  //  while (1)
  //  {
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
	if(operation.type==0){
	   //entero1=binDec(operation.param1);
	   binDec(operation.param1);
	   entero1=atoi(dest);
	   memset (dest, '\0', 50);
	   memset (src, '\0', 50);
	   binDec(operation.param2);
	   entero2=atoi(dest);
	   printf("%d\n",entero1);
	   printf("%d\n",entero2);
	   return 0;
	}
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

   // }
    

    //ret_status = asm_main();
    return resultado;
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
    char selector;
    
    //Binario o entero
    selector = *strtok(buffer, " ");
    switch(selector){
            case 'e':
                operation->type = 1;
                break;
            case 'b':
                operation->type = 0;
                break;
            default:return -1;
            	break;
           }
    /*if (tokenAux == NULL || strcmp(tokenAux, "e") != 0 && strcmp(tokenAux, "b") != 0){
        printf("El comando ingresado es incorrecto\n");
        return -1;
    }
    operation->type = *tokenAux;;*/
    
    //parametro 1
    tokenAux = strtok(NULL, " ");
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

void binDec (int n) {

    if (n) {
        binDec(n / 2);
        sprintf(src, "%d", n % 2);
        strcat(dest, src);
        //printf("%d", n % 2);
    }
    //printf("%s",dest);
    //return atoi(dest);
}

