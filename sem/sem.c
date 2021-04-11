#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define sharedMemKey 4242

#define children 10 //Amount of children to fork
#define sleepLen 100 //Milliseconds for the children to sleep

/*
 * Task (complete all TODO marked tasks):
 *
 * 1. Initialise the semaphore at the beginning (the semaphore should be
 *    allocated in the SharedMem structure
 * 2. Remove the semaphore at the end
 * 3. Only one person can sleep at a time - make the parent sleep first and
 *    then make the children sleep one after another - this is achieved by
 *    locking and unlocking the semaphore with 'sem_wait' and 'sem_post'.
 *
 *
 * Hints:
 *
 * RTFM
 * Check the example output in the sem/ folder
 * For this use I suggest setting the semaphore's initial value to 0 to
 *   ensure that the parent will sleep first.
 *
 */


typedef struct{
  int shmid;
  sem_t sem;
} SharedMem;



int main(void){

  //Create a shared memory
  int shmid = shmget(sharedMemKey, (sizeof(int) + sizeof(sem_t)), IPC_CREAT | 0666);
  if(shmid < 0){
    printf("Shared memory could not be created.\n");
    return 1;
  }
  SharedMem *shm = shmat(shmid, NULL, 0);
  if(shm == (SharedMem *) -1){
    printf("Shared memory could not be created.\n");
    return 1;
  }
  shm->shmid = shmid;

  //TODO: initialise the semaphore

  //Fork the processes
  int procPID = fork();
  if(procPID == 0){
    //This code is only ran by the child
    
    //Create 'children' more children from the child
    for(int i = 0; i < children; i++){
      if(fork() == 0){
        printf("I am a child number %d and I'm waiting for my turn.\n", i + 1);

        //TODO: lock the semaphore so the child can sleep alone

        printf("I am a child number %d and now it's my turn. Sleeping for %d ms.\n", i + 1, sleepLen);
        usleep(1000*sleepLen);
        printf("I am a child number %d and I have slept. I will now release the semaphore and kill myself.\n", i + 1);

        //TODO: release the semaphore to let other children sleep

        exit(0);
      }
    }
    exit(0); //Kill the child process that has forked the other children
  }else if(procPID > 0){
    //This code is only ran by the parent
    
    printf("I am the parent and I will sleep first for %d ms.\n", sleepLen*10);
    usleep(1000*10*sleepLen);
    printf("I am the parent and I have slept. I will now release the semaphore, wait for my children to sleep and kill myself.\n");

    //TODO: release the semaphore

    usleep(1000*(children+1)*sleepLen);
    exit(0);
  }else{
    printf("An unknown error occured.\n");
    return 1;
  }

  
  //TODO: destroy the semaphore
  
  //Remove the shared memory
  shmid = shm->shmid;
  if(shmdt(shm)){
    return 1;
  }
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}
