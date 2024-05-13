#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define KEY (1492)

int main()
{
   int id; 
   union semun 
   {
      int val;
      struct semid_ds *buf;
      ushort * array;
   } argument;
   argument.val = 0;
   id = semget(KEY, 1, 0666 | IPC_CREAT);

   if(id < 0)
   {
      cout << "Unable to obtain semaphore.\n" << endl;
      exit(0);
   }
   if(semctl(id, 0, SETVAL, argument) < 0)
   {
      cout << "Cannot set semaphore value.\n" << endl;
   }
   else
   {
      cout << "Semaphore initialized.\n" << endl;
   }
}

// A union semun contains 3 members: val (integer), buf (pointer to struct semid_ds), and array (pointer to ushort). 
// This union is used as an argument for various semaphore control operations.
// val member of the semun union is initialized to 0, representing the initial value of the semaphore.
// semctl(): remove semaphore through a call
// If the semget() call succeeds, the program proceeds to set the initial value of the semaphore
// using the semctl() function with the SETVAL command. semctl(semaphore Id, IPC_RMID, arg(anything))
// IPC_RMID -> semctl() to remove that semaphore set
// If both semget() and semctl() succeed, the program prints a message indicating that the semaphore has been successfully initialized.