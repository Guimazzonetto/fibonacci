#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include "time.h"

int n = 25;
int fibonacci[100];
int a, b, auxiliar, i, n;


void *fib(void * arg){
  
    int f0 = 0, f1 = 1, valor = 0;
    int *p;
    p = (int*) arg;
    int n = *p;
    for (int i = 0; i <= n; i++){
      
        if (i <= 1){
          valor = i;
        } 
        
        else {
          
          valor = f0 + f1;
          f0 = f1;
          f1 = valor;
          
        } 
        fibonacci[i] = valor;
    }
}

int fibonacci2(int valor)
{
    if (valor == 0)
    {
        return 0;
    }
    else if (valor == 1)
    {
        return 1;
    }
    else
    {
        return(fibonacci2(valor - 1) + fibonacci2(valor - 2));
    }
}

int main(){

  clock_t T[4];
  T[0] = clock();
  
	pthread_t t0,t1;
    int x1 = n-1, x2 = n-2;
    pthread_create(&t0, NULL, &fib, &x1);
    pthread_create(&t1, NULL, &fib, &x2); 
    pthread_join(t0,NULL);
    pthread_join(t1,NULL);


    fibonacci[n]=fibonacci[x1]+fibonacci[x2];

    printf("Fibonacci do numero 25 = %d",fibonacci[n]);
    printf("\n");

  T[1] = clock();
  double temp = (T[1]-T[0])*1000.0/CLOCKS_PER_SEC;

  printf("Tempo com thread: %g\n\n",temp);

  T[2] = clock();
  
  int fibo2;

  fibo2 = fibonacci2 (n);
  printf("Fibonacci do numero 25 = %d\n",fibo2);


  T[3] = clock();
  double temp_2 = (T[3]-T[2])*1000.0/CLOCKS_PER_SEC;

  printf("Tempo sem thread: %g\n",temp_2);
  
    return 0;

}
