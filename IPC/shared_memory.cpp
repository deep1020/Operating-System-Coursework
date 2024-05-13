#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;
int main()
{
   int pid;
   pid = fork();
   if (pid == 0)
   {
       int shmid;
       key_t key;
       int *shm;
       key = 123456;
       sleep(1); // sleep for 1 second
       shmid = shmget(key, 27, 0666);
       shm = (int *)shmat(shmid, NULL, 0);
       cout << "[Child] before changed, inside shared memory: " << *shm << endl;
       *shm = 8;
       cout << "[Child] after changed, inside shared memory: " << *shm << endl;
       shmdt((char *)shm);
       exit(0);
   }
   else if (pid > 0)
   {
       int shmid;
       int shmflg = IPC_CREAT | 0666; // Need to write IPC_CREAT first time to initialize
       key_t key;
       int *shm;
       key = 123456;
       shmid = shmget(key, 27, shmflg);
       shm = (int *)shmat(shmid, NULL, 0);
       cout << "[Parent] before changed, inside shared memory: " << *shm << endl;
       *shm = 100;
       cout << "[Parent] after changed, inside shared memory: " << *shm << endl;
       while(*shm != 8)
       {
           sleep(1);
       }
        // wait(NULL); // wait for child process to finish
       cout << "[Parent] after child changed the shared memory: " << *shm << endl;
       shmdt((char *)shm);
       shmctl(shmid, IPC_RMID, 0);
       exit (0);
   }
}

// Declaring variables pid to store the process ID, shmid for the shared memory segment ID, key for the shared memory key, and 
// shm for the pointer to the shared memory.

// parent process
// It obtains the shared memory segment ID (shmid) using shmget() with the specified key and size.
// It attaches the shared memory segment to its address space using shmat().
// It reads the value from the shared memory, prints it, modifies it to 100, and then prints the modified value.
// It enters a loop to wait until the child process changes the value in the shared memory to 8. It sleeps for 1 second in each iteration.
// Once the child process changes the value, it prints the updated value.
// It detaches the shared memory segment using shmdt(), removes the shared memory segment using shmctl() with IPC_RMID command, and exits.

// child process
// It waits for 1 second using sleep(1) to ensure that the parent process initializes the shared memory before accessing it.
// It obtains the shared memory segment ID (shmid) using shmget() with the specified key and size.
// It attaches the shared memory segment to its address space using shmat().
// It reads the value from the shared memory, prints it, modifies it to 8, and then prints the modified value.
// Finally, it detaches the shared memory segment using shmdt() and exits.

// system call
// fork(): create a new process (child process) by duplicating the calling process (parent process).
// shmget(): allocate a shared memory segment. It takes a key, size, and flags as arguments and returns the identifier of the shared memory segment (shmid).
// shmat(): attach a shared memory segment to the address space of the calling process. It takes the shmid, address, and flags as arguments and returns the address at which the segment is attached.
// shmdt(): detach a shared memory segment from the address space of the calling process. It takes the address of the segment as an argument.
// shmctl(): remove the shared memory segment. It takes the shmid, command, and buffer as arguments.
// sleep(): suspend the execution of the calling thread for a specified number of seconds.
// exit(): terminate the calling process. It takes an exit status as an argument.

// variables
// pid: store process Id returned by fork() system call
// shmid: store the identifier of the shared memory segment returned by the shmget() system call
// key: key_t variable used to specify the key for the shared memory segment
// shm: An integer pointer variable used to point to the shared memory segment. 
// It is used to read from and write to the shared memory.

