#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define K 2
#define N 3

int A[M][K] = { {1,4}, {2,5}, {3,6} };
int B[K][N] = { {8,7,6}, {5,4,3} };
int C[M][N];

struct v {
   int i; /* linha */
   int j; /* coluna */
};

void *mult(void *); /* calcula a multiplicacao */

int main() {
    int i, j, count = 0;   
    pthread_t tid[M*N]; /* MxN threads de trabalho */
    pthread_attr_t attr[M*N]; /* Conjunto de atributos da thread */
    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++) {
            struct v *data = (struct v *) malloc(sizeof(struct v)); /* Aloca a memoria para a struct */
            data->i = i; /* Atribui o contador i autal a linha da struct */
            data->j = j; /* Atribui o contador j autal a coluna da struct */
            pthread_attr_init(&attr[count]); /* Obtem os atributos default */
            pthread_create(&tid[count],&attr[count],mult,data); /* Criacao da thread passando para ele data como parametro */
            pthread_join(tid[count], NULL); /* Espera a thread ser encerrada */
            count++;
        }
    }

    /* Saida da multiplicacao */
    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}

/* O thread assumirá o controle nessa função */
void *mult(void *param) {
    struct v *data = param;
    int n;

    C[data->i][data->j] = 0;

    /* Somatorio da multiplicacao do elemento da linha vezes o correspondente na coluna atribuido a matriz C*/
    for(n = 0; n < K; n++){
      C[data->i][data->j] += A[data->i][n] * B[n][data->j];
    }
    pthread_exit(0);
}
