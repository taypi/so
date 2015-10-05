#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int checkSize(int);

void calcFib(int);

int main()
{
    int size = 0;
    /* checando valores negativos */
    size = checkSize(size);

    pid_t pid; /* id do processo */
    pid = fork(); /* fork do processo */

    if (pid < 0) { /* Aconteceu um erro */
        fprintf(stderr, "Fork falhou\n");
    }
    else if (pid == 0) { /* Processo filho */
        printf("Comeco do processo filho...\n Sequencia: [");
        calcFib(size);
        printf("] \nFim do processo filho...\n");
    }
    else { /* Processo pai */
        printf ("Comeco do processo pai...\n");
        wait(NULL);
        printf("Fim do processo pai...\n");
    }
    return 0;
}

int checkSize(int size){
    while (size < 1){
        printf("Tamanho da sequência: ");
        scanf("%d", &size);
    }
    return size;
}

void calcFib(int size){
    int i;
    unsigned long long int fib[size];
    for (i = 0; i < size; i++){
        if (i < 2) {
            fib[i] = i;
        }
        else {
            fib[i] = fib[i-1] + fib[i-2];
        }
    printf("%llu ", fib[i]);
    }
}
