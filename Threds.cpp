# Soma os elementos de um vetor de inteiros em paralelo utilizando threads
include <stdio.h>
include <stdlib.h>
include <pthread.h>

# define NUM_THREADS 4
# � criada uma estrutura ThreadArg, 
# que representa os argumentos que ser�o passados para cada thread. 
# Essa estrutura cont�m um ponteiro para o vetor de inteiros que ser� somado, 
# um �ndice de in�cio e fim que delimita a parte do vetor que ser� somada e um valor para armazenar a soma parcial dessa parte.
typedef struct {
    int *vetor;
    int inicio;
    int fim;
    int resultado_parcial;
} ThreadArg;

# � declarada a fun��o soma_vetor(), 
# que ser� executada por cada thread e receber� como argumento um ponteiro para a estrutura ThreadArg.
void *soma_vetor(void *arg);

# A fun��o main() � a fun��o principal do programa.
# Ela pede ao usu�rio o tamanho do vetor e os elementos que comp�em o vetor, 
# utilizando a fun��o scanf() para ler os dados.
# Em seguida, aloca dinamicamente um vetor de inteiros utilizando a fun��o malloc() e verifica se a aloca��o foi bem sucedida.
# Se ocorrer algum erro, o programa exibe uma mensagem de erro e encerra a execu��o utilizando a fun��o exit().
# Por fim, o programa preenche o vetor com os valores digitados pelo usu�rio.
int main()
{
    int n;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    int *vetor = (int *) malloc(n * sizeof(int));
    if (vetor == NULL) {
        printf("Erro: memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }

    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    pthread_t threads[NUM_THREADS];
    ThreadArg args[NUM_THREADS];

    int elementos_por_thread = n / NUM_THREADS;
    int resto = n % NUM_THREADS;
    int inicio = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].vetor = vetor;
        args[i].inicio = inicio;
        args[i].fim = inicio + elementos_por_thread;
        args[i].resultado_parcial = 0;

        if (resto > 0) {
            args[i].fim++;
            resto--;
        }

        pthread_create(&threads[i], NULL, soma_vetor, &args[i]);

        inicio = args[i].fim;
    }

    int resultado_total = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        resultado_total += args[i].resultado_parcial;
    }

    printf("A soma dos elementos do vetor eh: %d\n", resultado_total);

    free(vetor);

    return 0;
}

void *soma_vetor(void *arg)
{
    ThreadArg *thread_arg = (ThreadArg *) arg;

    for (int i = thread_arg->inicio; i < thread_arg->fim; i++) {
        thread_arg->resultado_parcial += thread_arg->vetor[i];
    }

    pthread_exit(NULL);
}

