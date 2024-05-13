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
   int retval; 
   full_id = semget(KEY1, 1, 0666);
   empty_id = semget(KEY2, 1, 0666);

   for (int i = 0; i < 10; i++)
   {
        cout << "Consume an Item. \n" << endl;

        v_op[0].sem_num = 0;
        v_op[0].sem_op = 1;
        v_op[0].sem_flg = 0;

        p_op[0].sem_num = 0;
        p_op[0].sem_op = -1;
        p_op[0].sem_flg = 0;

        retval = semop(full_id, p_op, 1);
        cout << "Consume an item : " << i << endl;
        retval = semop(empty_id, v_op, 1);
   }
}

