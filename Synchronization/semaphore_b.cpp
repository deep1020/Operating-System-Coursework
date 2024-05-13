#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

using namespace std;

#define KEY (1492)

int main()
{
   int id;  
   struct sembuf operations[1];

   int retval; 
   id = semget(KEY, 1, 0666);
   if(id < 0)
   {
      cout << "cannot find semaphore\n" << endl;
      exit(0);
   }

   cout << "to do a P-operation. \n" << endl;
   cout << "Process id is " << getpid() << endl;

   operations[0].sem_num = 0;
   operations[0].sem_op = -1; // set to -1 indicating a decrementing operation
   operations[0].sem_flg = 0;

   retval = semop(id, operations, 1);

   if(retval == 0)
   {
       cout << "Successful P-operation \n" << endl;
       cout << "Process id is " << getpid() << endl;
   }
   else
   {
       cout <<"P-operation did not succeed.\n" << endl;
   }
}
