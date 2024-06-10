#include <stdio.h>

int main(void) {



  int cnt = read (fd, buf, numbytes);
  //read è una sistem call posix che ritorna un intero
  //fd è il file su cui legge e su cui memorizzera numbytes su buf


  //le system call linux ritornano -1 se falliscono

  if (cnt == -1){
    if(errno == EINTR){
    // errno per segnalare errori e fail
    // Questo errore si verifica quando una chiamata di sistema viene interrotta da un segnale prima che possa essere completata

      // Ad esempio, se un programma sta leggendo da un file e riceve un segnale SIGINT, la lettura può essere interrotta e generare un errore EINTR
      fprintf (stderr ,
      "read () was interrupted by a signal \n");
    //stderr per printare l'errore
    else if(errno == EBADF){
      fprintf(stderr, "ok");
      //Questo errore si verifica quando un file descriptor passato a una chiamata di sistema non è valido
    })
    }
  }
  


  
  return 0;
}