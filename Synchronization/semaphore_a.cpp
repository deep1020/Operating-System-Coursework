#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

using namespace std;

#define KEY (1492)

int main()
{
   int id;  
   struct sembuf operations[1];
   int retval; /* Return value from semop() */
   id = semget(KEY, 1, 0666 | IPC_CREAT);
   if(id < 0)
   {
      cout << "A cannot find semaphore, exiting." << endl;
      exit(0);
   }

   cout << "Program A to do a V-operation. \n" << endl;

   operations[0].sem_num = 0;
   operations[0].sem_op = 1; // set to 1 indicating an incrementing operation
   operations[0].sem_flg = 0;

   retval = semop(id, operations, 1);
   if(retval == 0)
   {
       cout << "Successful V-operation by A \n" << endl;
   }
   else
   {
       cout << "V-operation did not succeed.\n" << endl;
   }
}

// sembuf: array of structure that sembufs can be created in order to do a whole bunch of semaphore operations at the same time
// retval: store the return value from the semop() function

// semget(): create a semaphore set ID. It attempts to find an existing semaphore set identified by the provided KEY and permissions 0666.
// If the semget() call succeeds, the program proceeds to perform a V-operation on the semaphore using the semop() function.
// If the semget() call fails (returns a value < 0), it indicates an error, and the program prints an error message and exits.

// V-operation is performed by setting the sem_num member of the sembuf structure to 0 (indicating the index of the semaphore in the set), 
// setting the sem_op member to 1 (indicating an increment operation), and setting the sem_flg member to 0 (indicating no flags).

// semop():  semaphore set ID (id), the operations array, and the number of semaphore operations to perform (1)
// If semop() succeeds(return 0), it indicates that the V-operation was successful, and the program prints a success message.
// If semop() fails(return value < 0), it indicates an error, and the program prints an error message.

// variables:
// id: Integer variable used to store the semaphore identifier obtained from the semget system call
// operations: Array of sembuf structures used to define semaphore operations. In this case, it is an array of size 1, 
// as only one semaphore operation is performed.
// retval: Integer variable used to store the return value of the semop system call, indicating the success or failure of the semaphore operation.