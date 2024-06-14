#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void sigHandler(int sig) {
    printf("Ouch!\n"); /* UNSAFE */
    sleep(5);
    // Il programma poi dormirà per 5 secondi. Durante questo tempo, se premi Ctrl+C altre tre volte, non vedrai immediatamente altri messaggi "Ouch!". Questo dimostra che il segnale SIGINT è temporaneamente bloccato mentre il gestore è in esecuzione
    printf("Bye\n");
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    sa.sa_flags = 0; /* No flags */
    sa.sa_handler = sigHandler; /* Handler function */
    sigemptyset(&sa.sa_mask); /* Don’t block additional signals during invocation of handler */

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        pause(); /* Wait for a signal */
    }
}
