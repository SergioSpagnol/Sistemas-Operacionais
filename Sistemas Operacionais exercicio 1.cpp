include <stdio.h>
include <stdlib.h>
include <pthread.h>
include <unistd.h> // para utilizar a fun��o sleep

int y = 0;

void *threadBody(void *arg) // a fun��o precisa receber um ponteiro void como argumento
{
    int x = 0;
    sleep(10);
    printf("x: %d, y: %d\n", ++x, ++y); // � necess�rio imprimir uma quebra de linha (\n) no final da mensagem
    pthread_exit(NULL); // � preciso encerrar a thread antes de retornar
}

int main()
{
    pthread_t tA, tB, tC; // � necess�rio declarar as vari�veis de thread do tipo pthread_t

    // � preciso passar um ponteiro para a fun��o threadBody e um ponteiro para os argumentos (NULL neste caso)
    pthread_create(&tA, NULL, threadBody, NULL);
    pthread_create(&tB, NULL, threadBody, NULL);
    sleep(1);
    pthread_join(tA, NULL); // � necess�rio passar um ponteiro para um objeto pthread_t e um ponteiro para o valor de retorno (NULL neste caso)
    pthread_join(tB, NULL); // � necess�rio passar um ponteiro para um objeto pthread_t e um ponteiro para o valor de retorno (NULL neste caso)
    sleep(1);
    pthread_create(&tC, NULL, threadBody, NULL);
    pthread_join(tC, NULL); // � necess�rio passar um ponteiro para um objeto pthread_t e um ponteiro para o valor de retorno (NULL neste caso)

    return 0; // � necess�rio retornar um valor inteiro na fun��o main
}

