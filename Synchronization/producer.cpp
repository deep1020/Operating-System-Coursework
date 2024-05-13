#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>


using namespace std;

#define KEY1 (12341)
#define KEY2 (12342)

int main()
{
   int full_id;  
   int empty_id;  
   struct sembuf v_op[1];
   struct sembuf p_op[1];
   int retval; /* Return value from semop() */
   full_id = semget(KEY1, 1, 0666);
   empty_id = semget(KEY2, 1, 0666);

   for (int i = 0; i < 10; i++)
   {
        cout << "Produce an Item. \n" << endl;

        v_op[0].sem_num = 0;
        v_op[0].sem_op = 1;
        v_op[0].sem_flg = 0;

        p_op[0].sem_num = 0;
        p_op[0].sem_op = -1;
        p_op[0].sem_flg = 0;

        retval = semop(empty_id, p_op, 1);
        cout << "Produce an item: " << i << endl;
        retval = semop(full_id, v_op, 1);
        sleep(1);
   }
}

// Integer variables full_id and empty_id stores the semaphore set IDs for the full and empty slots in the buffer respectively.
// Arrays of sembuf structures v_op and p_op are defined. Each sembuf structure represents a semaphore operation for the V (signal) and P (wait) operations respectively.
// producer produces an item and waits for an empty slot in the buffer (by performing a P operation on the empty_id semaphore).
// Once an empty slot is available, the producer produces an item (prints a message indicating the item number) and 
// signals that a full slot is available (by performing a V operation on the full_id semaphore)
// producer then waits for a short duration using sleep() function to simulate some processing time before producing next item.