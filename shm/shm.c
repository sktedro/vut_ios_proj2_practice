#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


/*
 * Task (complete all TODO marked tasks):
 *
 * 1. Create a shared memory - make the SharedMem structure shared.
 * 2. Initialise the sharedNum to any value.
 * 3. Make both processes immediately print the initial number
 * 4. Make the child change the value after 100 microseconds
 * 5. Make both processes read the value after it has been changed - if both
 *    processes print the same number, you have successfully created a shared
 *    memory
 * 6. Remove the shared memory (only once - by the parent)
 *
 *
 * Hints:
 *
 * Use commands 'shmget' and 'shmat' to initialise the shared memory.
 * Don't forget to save the ID of the shared memory (for example to the shmid
 * variable in SharedMem struct).
 * At the end, remove the shared memory using commands 'shmdt' and 'shmctl'.
 *
 * Don't forget to check the outputs of these commands if anything goes wrong.
 *
 */


typedef struct{
  int sharedNum;
  int shmid;
} SharedMem;

int main(void){

  //TODO: Initialise the shared memory and give the sharedNum a value

  //Fork the processes
  int procPID = fork();
  if(procPID == 0){
    //This code is only ran by the child

    //TODO:complete the printf statement:
    //printf("I am the child and my initial number is %d.\n");

    //Just wait a bit for the parent to read the initial value;
    usleep(100);

    //TODO: make the child change the value of sharedNum


    //TODO: complete the printf statement:
    //printf("I am the child and my changed number is %d.\n");
    
    exit(0);
  }else if(procPID > 0){
    //This code is only ran by the parent
    
    //TODO: complete the printf statement:
    //printf("I am the parent and my initial number is %d.\n");

    //Wait for the child to change the value before reading it again
    usleep(1000);

    //TODO: complete the printf statement:
    //printf("I am the parent and my changed number is %d.\n");
  }else{
    printf("An unknown error occured.\n");
    return 1;
  }

  //This code is only ran by the parent
  
  //TODO: remove the shared memory

  return 0;
}
