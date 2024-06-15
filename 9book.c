#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
int main(int argc , char *argv []) {
int nzombies = (argc > 1) ? atoi(argv [1]) : 1;
printf (" Parent (PID %ld )\n", ( long ) getpid ());
for ( int j = 0; j < nzombies ; j++) {
switch (fork ()) {
case -1:
errExit ("fork -%d", j);
case 0: /* Child : exits to become zombie */
printf (" Child (PID %ld) exiting \n", ( long ) getpid ());
exit( EXIT_SUCCESS );
default : /* Parent continues in loop */
break ;
}
}
sleep (600); /* Children are zombies during this time */
while (wait(NULL) > 0) /* Reap zombie children */
continue ;
exit( EXIT_SUCCESS );
}