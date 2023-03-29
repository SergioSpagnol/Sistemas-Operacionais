include <stdio.h>
include <stdlib.h>
include <pthread.h>
include <unistd.h> // para utilizar a função sleep

int y = 0;

void *threadBody(void *arg) // a função precisa receber um ponteiro void como argumento
{
    int x = 0;
    sleep(10);
    printf("x: %d, y: %d\n", ++x, ++y); // é necessário imprimir uma quebra de linha (\n) no final da mensagem
    pthread_exit(NULL); // é preciso encerrar a thread antes de retornar
}

int main()
{
    pthread_t tA, tB, tC; // é necessário declarar as variáveis de thread do tipo pthread_t

    // é preciso passar um ponteiro para a função threadBody e um ponteiro para os argumentos (NULL neste caso)
    pthread_create(&tA, NULL, threadBody, NULL);
    pthread_create(&tB, NULL, threadBody, NULL);
    sleep(1);
    pthread_join(tA, NULL); // é necessário passar um ponteiro para um objeto pthread_t e um ponteiro para o valor de retorno (NULL neste caso)
    pthread_join(tB, NULL); // é necessário passar um ponteiro para um objeto pthread_t e um ponteiro para o valor de retorno (NULL neste caso)
    sleep(1);
    pthread_create(&tC, NULL, threadBody, NULL);
    pthread_join(tC, NULL); // é necessário passar um ponteiro para um objeto pthread_t e um ponteiro para o valor de retorno (NULL neste caso)

    return 0; // é necessário retornar um valor inteiro na função main
}

