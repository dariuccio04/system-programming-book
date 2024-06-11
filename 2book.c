#define BUF_SIZE 1024
//definiamo una convenzione sulla dimensione del file

char buf[BUF_SIZE];

int fd = open(argv[1], O_RDONLY);
//apriamo un file con la system call open di posix
//apriamo il file passato come primo argomento
//lo apriamo con i soli permessi di lettura

if(fd == -1) errExit();
//controlliamo il valore di ritorno per verificare che si sia aperto correttamente

FLAGS = 0_CREAT | O_WRONLY | O_TRUNC;
/*
i flags sono delle modalità di apertura del file
O_CREAT: crea il file se non esiste
O_WRONLY: apre il file in lettura
O_TRUNC: elimina tutti i byte dal file
  */
mode = S_IRUSR | S_IWUSR | S_IRGRP;
/*
i mode settano i permessi su file:
S_IRUSR: permesso di lettura per il solo proprietario del file
S_IWUSR: permesso di scrittura per il solo proprietario del file
S_IRGRP : permesso di scrittura per il gruppo
IR (READ), GRP (GROUP)
permessi: rw- r-- ---
*/

int fd2 = open(argv[2], flags, mode);
//flags e mode settati prima
if (fd2 == -1) errExit;
while ((byte_letti= read(fd, buf, BUF_SIZE))>0 ){
  /*
  valori di ritorno:
  >0 numero di byte letti
  0 EOF
  -1 ERRORE
  */
  if (write(fd2, buf, byte_letti ) != byte_letti){
    fatal();
  }
  //stiamo in effetti verificando che i byte letti siano gli stessi che escono dalla funzione write
}


if (nread == -1) errExit("read");
if (close(infd) == -1) errExit("close");
if (close(outfd) == -1) errExit("close");


