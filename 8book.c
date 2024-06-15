#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigalrm_handler(int signum) {
    printf("PID %d received SIGALRM\n", getpid());
}

int main() {
    struct sigaction sa;

    // Imposta il gestore per SIGALRM
    sa.sa_handler = sigalrm_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Avvia un timer di allarme che scade dopo 2 secondi
    alarm(2);

    // Crea un processo figlio
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Codice eseguito dal processo figlio

        // Verifica la disposizione del segnale SIGALRM nel figlio
        struct sigaction child_sa;
        if (sigaction(SIGALRM, NULL, &child_sa) == -1) {
            perror("sigaction child");
            exit(EXIT_FAILURE);
        }

        // Controlla se il gestore del segnale nel figlio è lo stesso del padre
        if (child_sa.sa_handler == sigalrm_handler) {
            printf("Child PID %d inherits SIGALRM disposition from parent\n", getpid());
        } else {
            printf("Child PID %d does not inherit SIGALRM disposition from parent\n", getpid());
        }

    } else {
        // Codice eseguito dal processo padre

        // Iterazioni per mostrare i PID del padre
        for (int i = 0; i < 5; ++i) {
            usleep(500000); // 500 millisecondi di pausa
            printf("Parent PID %d\n", getpid());
        }
    }

    return 0;
}
