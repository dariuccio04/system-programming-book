#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Gestore del segnale SIGINT
void handler(int signum) {
    printf("sssss\n");
}

int main() {
    // Stabilisce il gestore del segnale SIGINT
    signal(SIGINT, handler);

    // Attende fino a quando non viene premuto il controllo-C
    pause();

    // Ciclo infinito che stampa "mmmmm\n"
    while (1) {
        printf("mmmmm\n");
        sleep(1); // Aggiungo una piccola pausa per evitare un output troppo rapido
    }

    return 0;
}
