#include <stdio.h>
#include<stdlib.h>

int main( int argc, char *argv[] )  {
/*
   if( argc == 4 ) {
      printf("The %d  arguments supplied are %s %s %s \n",argc, argv[1], argv[2],argv[3]);
   }
   else {
      printf("Four arguments expected. <number><operand><number> \n");
   
   }
   
   for (int i = 0; i <= argc; i++) {
    printf("%d at %p: %s\n", i, argv[i], argv[i]);
  }
   
  */
   int z = 0; 

   if ((char)argv[2][0]=='+')
   {
   int y = atoi(argv[1]);
   int x = atoi(argv[3]);
   z = x + y;
   }
   printf("%d", z);

  return 0;

}


