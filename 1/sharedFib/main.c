#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/* Define o tamanho máximo da sequência */
#define MAX_SEQUENCE 90

typedef struct{
    unsigned long long int fib_sequence[MAX_SEQUENCE];
    int sequence_size;
} shared_data;

int main()
{
    int i;

    /* Identificador para o segmento de memoria compartilhada */
    int segment_id;

    /* O tamanho (bytes) do segmento de memoria compartilhada */
    unsigned long segment_size = sizeof(shared_data);

    /* Aloca o segmento */
    segment_id = shmget(IPC_PRIVATE, segment_size, S_IRUSR | S_IWUSR);

    /* Checa o resultado do shmget */
    if (segment_id == -1) {
        printf("shmget falhou");
        return 0;
    }

    /* Anexa o segmento de memoria */
    shared_data *shared_memory = (shared_data *)shmat(segment_id, NULL, 0);

    shared_memory->sequence_size = 0;

    /* Checando valores negativos */
    while (shared_memory->sequence_size < 1 || shared_memory->sequence_size > MAX_SEQUENCE){
        printf("Tamanho da sequência: ");
        scanf("%d", &shared_memory->sequence_size);
    }

    pid_t pid;
    pid = fork();
    if (pid < 0) { /* Aconteceu um erro */
        fprintf(stderr, "Fork falhou\n");
        return 1;
    }
    if (pid == 0){
        printf("Comeco do processo filho...\n");
        for (i = 0; i < shared_memory->sequence_size; i++){
            if (i < 2) {
                shared_memory->fib_sequence[i] = i;
            }
            else {
                shared_memory->fib_sequence[i] = shared_memory->fib_sequence[i-1] + shared_memory->fib_sequence[i-2];
            }
        }
        printf("...Fim do processo filho\n");
    }
    else{
        printf("Comeco do processo pai...\n");
        wait(NULL);
        for(i = 0; i < shared_memory->sequence_size; i++) {
            printf("%llu ", shared_memory->fib_sequence[i]);
        }
        printf("\n...Fim do processo pai\n");
    }

    /* Desanexa o segmento de memoria compartilhada */
    shmdt(shared_memory);
    /* Remove o segmento de memoria compartilhada */
    shmctl(segment_id, IPC_RMID, NULL);

    return 0;
}
