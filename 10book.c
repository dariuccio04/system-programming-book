#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid1, pid2;

    pid1 = fork(); // Il nonno crea il genitore

    if (pid1 == 0) { // Nel genitore
        pid2 = fork(); // Il genitore crea il figlio

        if (pid2 == 0) { // Nel figlio
            for (int i = 0; i < 10; i++) {
                printf("Figlio: ppid = %d\n", getppid());
                sleep(1);
            }
            exit(0); // Il figlio termina dopo aver osservato il ppid per 10 secondi
        } else {
            sleep(3); // Il genitore dorme per 3 secondi
            exit(0); // Il genitore termina, diventando inizialmente un processo zombie
        }
    } else { // Nel nonno
        sleep(6); // Il nonno dorme per 6 secondi
        waitpid(pid1, NULL, 0); // Il nonno attende che il genitore termini
    }

    return 0;
}
