#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define K 2
#define N 3

int A [M][K] = { {1,4}, {2,5}, {3,6} };
int B [K][N] = { {8,7,6}, {5,4,3} };
int C [M][N];

struct v {
   int i; /* row */
   int j; /* column */
};

void *mult(void *); /* calcula a multiplicacao */

int main() {

   int i,j;
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         /* MxN threads de trabalho */
         struct v *data = (struct v *) malloc(sizeof(struct v));
         data->i = i;
         data->j = j;
         /* Agora criamos o thread passando para ele data como parametro */
         pthread_t tid;       /* Thread ID */
         pthread_attr_t attr; /* Conjunto de atributos do thread */
         /* Obtém os atributos default */
         pthread_attr_init(&attr);
         /* Cria o thread */
         pthread_create(&tid,&attr,mult,data);
         /* Espera o thread ser encerrado */
         pthread_join(tid, NULL);
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

/* Thread */
void *mult(void *param) {
   struct v *data = param;
   int n, sum = 0;

   /* Coluna X Linha */
   for(n = 0; n< K; n++){
      sum += A[data->i][n] * B[n][data->j];
   }
   /* Atribuindo o valor a nova matriz */
   C[data->i][data->j] = sum;

   pthread_exit(0);
}
