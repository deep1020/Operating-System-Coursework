#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

int pid=fork();
// int flag = 1;

void sigusr2(int signum) {
    // Define behavior for SIGUSR2
    cout << "Received SIGUSR2 signal" << signum << endl;
}
void sigusr1(int signum) {
    // Define behavior for SIGUSR1
    cout << "Received SIGUSR1 signal" << signum << endl;
    // if (flag) {
        // flag = 0;
        for (int j = 1; j < 10; j++) {
            kill(pid, SIGUSR2); // Sending SIGUSR2 to child process
            sleep(1);
        }
    // }
}
int main()
{
    if (pid < 0)
    {
        cout << "fork error \n";
        exit(1);
    }
    if (pid == 0)
    {
        sleep(1);
        signal(SIGUSR2,sigusr2);
        kill(getppid(),SIGUSR1); // Sending SIGUSR1 to parent process
        for (int j = 1; j < 10; j++)
        {
            pause();
        }
    }
    else
    {
        signal(SIGUSR1, sigusr1);
        for (int i = 1; i < 10; i++)
        {
            pause();
        }
        // wait(NULL);
    }
}

// First go in parent process. Set up signal handler for SIGUSR1 and suspend execution until SIGUSR1 is received
// Now in child process, sleep for 1 second, set up signal handler for SIGUSR2, sending SIGUSR1 to parent process
// In parent process, call sigusr1 function -> print "Received SIGUSR1 signal"
// In for loop, sending SIGUSR2 to child process, call sigusr2 function and print "Received SIGUSR2 signal" 9 times

// In the parent process (pid != 0):
// It sets up a signal handler for SIGUSR1 using the signal() function.
// It waits for the child process to terminate using the wait() function.

// In the child process (pid == 0):
// It sleeps for 1 second to allow the parent process to set up signal handling.
// It sets up a signal handler for SIGUSR2 using the signal() function.
// It sends a SIGUSR1 signal to the parent process using kill(getppid(), SIGUSR1).
// It enters a loop, waiting for SIGUSR2 signals using the pause() function.

// Inside the sigusr1() function, the behavior for the SIGUSR1 signal is defined. 
// It prints a message indicating that the signal has been received and then enters a loop to send SIGUSR2 signals to the child process.
// The loop runs for 9 iterations, with a sleep of 1 second between each signal.

// Inside the sigusr2() function, the behavior for the SIGUSR2 signal is defined. 
// In this case, it simply prints a message indicating that the signal has been received.

// fork(): create a new process (child process) by duplicating the calling process (parent process).
// sleep(): suspends the execution of the calling thread for a specified number of seconds.
// kill(): send a signal to a process or a group of processes.
// signal(): set up signal handling for various signals. It specifies the action to be taken when a particular signal is received.
// pause(): suspends the execution of the calling process until a signal is received.
// wait(): used by the parent process to wait for the termination of the child process.
