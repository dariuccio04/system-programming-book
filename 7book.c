#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Dichiarazione della variabile locale
    int var = 42;

    // Fork per creare un processo figlio
    pid_t pid = fork();

    if (pid < 0) {
        // Errore nella fork
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Codice eseguito dal processo figlio

        // Mostra il PID del figlio
        printf("Child PID: %d\n", getpid());

        // Modifica della variabile locale nel figlio
        var = 99;

        // Mostra il valore della variabile nel figlio
        printf("Child var: %d\n", var);

    } else {
        // Codice eseguito dal processo padre

        // Delay di 2 secondi per assicurare che il figlio abbia la possibilità di eseguire
        sleep(2);

        // Mostra il PID del padre
        printf("Parent PID: %d\n", getpid());

        // Mostra il valore della variabile nel padre (non modificato dal figlio)
        printf("Parent var: %d\n", var);
    }

    return 0;
}
