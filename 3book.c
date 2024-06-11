/*
andiamo a creare il comando tee -a file
il comando tee -a file, prende da standard input (stdin)
e mette tutto sul file specificato e sullo standard output
(stdout)
se specificato "-a" allora andrà ad appendere il contenuto, se non è specificato "-a" allora andrà a sovrascrivere il file

passaggi di codice:

andiamo a definire gli argv

(versione senza -a)
se il file non esiste allora lo creiamo (O_CREAT)
se il file esiste già -> O_TRUNC
(versione con -a)
se il file esiste già allora useremo O_APPEND invece di O_TRUNC

in poche parole, scriveremo ogni byte da standard input a standard output e il file di destinazione
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#define MAXN 1024

int main(int argc, char * argv[]){
  char buffer[MAXN];
  char *f;
  int fd;
  int with_a = 0;
  //verifichiamo il numero di argomenti: se solo due allora non ci sarò "-a"
  //nostra convenzione
  if (argc == 2){
   strcpy(f, argv[1]);
    //qui stavo per usare c come python:
    //stavo assegnando f = argv[1]
    //usa le str function!!!!!!!!!!!!!!!!!!!
  } else if (argc == 3) {
    with_a = 1;
    // segno che effettivamente c'è dentro -a
    strcpy(f, argv[2]);
    //se gli argc sono 3 allora abbiamo una struttura del tipo:
    // tee -a file
  } else printf("error");

  //devo aprire il file con i vari permessi e flags ecc
  int flags = O_WRONLY | O_CREAT;
  //apro il file in lettura, se non esiste lo creo

  //se ho -a allora uso append sennò uso trunc

  if (with_a){
    flags |= O_APPEND;
  } else
  {
    flags |= O_TRUNC;
  }
  // assegnazione bit a bit (|=)
   fd = open (f, flags,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  /*
  S_IRUSR = permessi di lettura solo al proprietario del file
  S_IWUSR = permessi di scrittura solo al proprietario del file
  S_IRGRP = permessi di lettura solo al gruppo proprietario
  S_IROTH = permessi di lettura ad altri utenti (oth -> other)

  */
  ssize_t ver;
  //ora scrivo ogni byte dallo stdin allo stdout e al file fd
  // stdin -> STDIN_FILENO
  while ( (ver = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0){
    //vogliamo scrivere su STDOUT_FILENO e nel file
    //scriviamo e allo stesso tempo verifichiamo che abbia scritto davvero, confrontando il valore di ritorno (numero di byte scritti) con "ver"
  if (write(STDOUT_FILENO, buffer, sizeof(buffer)) != ver){
    printf("error");
    close(fd);
  }
    if (write(fd, buffer, sizeof(buffer)) != ver){
      printf("error");
      close(fd);
    }
  }
  close(fd);
}