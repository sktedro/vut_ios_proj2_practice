#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*
 * Task:
 *
 * Create m son processes, n daughter processes and keep the parent process.
 * Daughters, sons and the parent should execute a different code.
 *
 *
 * Hints:
 *
 * Use the fork() function and don't forget to save it's return value. It
 * returns:
 *   0 for the child process
 *   >0 for the parent process
 *   -1 on an error
 * and this is how you can distinguish the processes and make them do different
 * tasks...
 *
 * Use for loops to create 'm' and 'n' processes, if statements to make the
 * parent execute different code than the children and exit() to end the
 * child's life.
 *
 */

int main(int argc, char **argv){
  if(argc != 3){
    printf("Give me two arguments on how many sons and daughters you'd like.");
    printf("\nEg. ./fork m n should create m sons and n daughters\n");
    return 0;
  }
  int sons = atoi(argv[1]);
  int daughters = atoi(argv[2]);



  //Son: Make this code run m times
  printf("I am a son and there should be %d of me.\n", sons);

  //Daughter: Make this code run n times
  printf("I am a daughter and there should be %d of me.\n", daughters);
  
  //Make this code only run once
  printf("I am the parent process and there should only be one of me.\n");



  return 0;
}
