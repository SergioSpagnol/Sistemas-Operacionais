include <stdio.h>
include <stdlib.h>
include <pthread.h>

void *fibonacci(void *arg);

int main()
{
    int n;
    printf("Digite a quantidade de elementos da sequencia de Fibonacci: ");
    scanf("%d", &n);
    
	// Declaração e criação da thread
    pthread_t thread_fibonacci;
    pthread_create(&thread_fibonacci, NULL, fibonacci, &n);

    printf("Aguarde o calculo da sequencia de Fibonacci...\n");
	
	
	// Espera a thread terminar sua execução
    pthread_join(thread_fibonacci, NULL);

    printf("Thread de Fibonacci finalizada.\n");

    return 0;
}

void *fibonacci(void *arg)
{
    int n = *((int *)arg);

    int a = 0, b = 1, c;
    printf("%d ", a);
    printf("%d ", b);
	// Cálculo da sequência de Fibonacci
    for (int i = 2; i < n; i++)
    {
        c = a + b;
        printf("%d ", c);
        a = b;
        b = c;
    }

    printf("\n");

    pthread_exit(NULL);
}

