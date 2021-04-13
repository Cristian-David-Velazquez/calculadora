#include "cdecl.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Variables y defines globales
#define SIZE_BUFFER 100

struct operation{
    int param1;
    int param2;
    char operation; //signo + o -
    int type;       //binario o entera
};

char dest[50]="";

//Funciones de ASM
int asm_sum_int( int a, int b) __attribute__ ((cdecl ));
int asm_rest_int( int a, int b) __attribute__ ((cdecl ));

//Funciones de C
int parsear_comando(struct operation * operation, char * buffer);   
void decBin (int n);
int binDec(int binario);
int powe (int x, int y);



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
    printf("ejemplo: b 1000 + 1111\n");
    //TODO: hay que decirle que seleccione si va a ser binario o entero

    while (1)
    {
        error = 0;
        printf("\n--------------------\n");
        printf("\nOperación: ");
        fgets(buffer, SIZE_BUFFER , stdin);
        
        if (strcmp(buffer, "fin\n") == 0){  //Cierra la calculadora
            return 0;
        }

        if (parsear_comando(&operation, buffer) == -1){
            error = -1;
        }
        //printf("\nPrint de operation:\nparam1:%d\noperation:%c\nparam1:%d\n\n", operation.param1,operation.operation,operation.param2);

        if(operation.type == 0){
           
           /* decBin(operation.param1);
            entero1 = atoi(dest);
            memset (dest, '\0', 50);
      

            decBin(operation.param2);
            entero2 = atoi(dest);
            printf("%d\n",entero1);
            printf("%d\n",entero2);*/
            operation.param1=binDec(operation.param1);
            operation.param2=binDec(operation.param2);
            //return 0;
        }
        
        if (error < 0){         //Gestion de erroes de los parámetros ingresados

           if (error == -1) {   //Error en parsear_comando()
                printf("El comando ingresado es incorrecto\n");
            } else if (error == -2){       //Error en binDec() o decBin()
                printf("El parámetro ingresado es incorrecto\n");
            } else {            //Otro error
                printf("Se ha producido un error\n");
            }
            
        } else {                //Ejecución de la opeacion
            switch(operation.operation){
                case '+':
                    resultado = asm_sum_int( operation.param1, operation.param2);
                    break;
                case '-':
                    resultado = asm_rest_int( operation.param1, operation.param2);
                    break;
                default:break;
            }
        
            if (resultado != -1){   //Gestion de error de la operacion
                printf("\nResultado: %d\n", resultado);
            } else {
                printf("\nResultado: Se ha producido un desbordamiento\n");
            }
        }

    }
    

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
        default:
            return -1;
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
    if (intAux == 2147483647 || intAux == -2147483648 || tokenAux == NULL){  //si el comando sale del limite máximo o mínimo de un int
        return -1;
    }
    operation->param1 = intAux;

    //operando
    tokenAux = strtok(NULL, " ");
    if (tokenAux == NULL || strcmp(tokenAux, "+") != 0 && strcmp(tokenAux, "-") != 0){
        return -1;
    }
    operation->operation = *tokenAux;

    //parametro 2
    tokenAux = strtok(NULL, " ");
    intAux = atoi(tokenAux);
    if (intAux == 2147483647 || intAux == -2147483648 || tokenAux == NULL){  //si el comando sale del limite máximo o mínimo de un int
        return -1;
    }
    operation->param2 = intAux;

    //Comprobación de cantidad de argumentos
    tokenAux = strtok(NULL, " ");
    if (tokenAux != NULL){      //si tiene mas de 3 parametros
        return -1;
    }


    return 0;
}


void decBin (int n) {
char src[50];
    if (n) {
        binDec( n / 2);
        sprintf( src, "%d", n % 2);
        strcat( dest, src);
        //printf("%d", n % 2);
    }
    //printf("%s",dest);
    //return atoi(dest);
}

int binDec(int binario){
int decimal=0;
int digito, exp=0;
	  while(((int)(binario/10))!=0)
   {
           digito = (int)binario % 10;
           decimal = decimal + digito * powe(2,exp);
           exp++;
           binario=(int)(binario/10);
   }
   decimal=decimal + binario * powe(2,exp);
   printf ("decimal:%d",decimal);
   return decimal;
}

int powe (int x, int y){
    int resultado = 1;
    for (int i = 0; i < y; i++)
    {
        resultado *= x;
    }
    return resultado;
}
