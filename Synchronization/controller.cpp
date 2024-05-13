#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define KEY1 (12341)
#define KEY2 (12342)

int main()
{
   int full_id;
   int empty_id;
   union semun 
   {
        int val;
        struct semid_ds *buf;
        ushort * array;
   } argument;

   full_id = semget(KEY1, 1, 0666 | IPC_CREAT);
   empty_id = semget(KEY2, 1, 0666 | IPC_CREAT);

   argument.val = 0;
   if(semctl(full_id, 0, SETVAL, argument) < 0)
   {
      cout << "Cannot set semaphore value.\n" << endl;
   }
   else
   {
      cout << "Semaphore initialized.\n" << endl;
   }

   argument.val = 2;
   if(semctl(empty_id, 0, SETVAL, argument) < 0)
   {
      cout << "Cannot set semaphore value.\n" << endl;
   }
   else
   {
      cout << "Semaphore initialized.\n" << endl;
   }
}

