#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
using namespace std;

void sigusr1(int x)
{
    cout << "This is sigusr1 handler: " << x << endl;
}
int pid=fork();
// int flag = 1;
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
        cout << "This is child process, send a signal to parent" << endl;
        kill(getppid(),SIGUSR1);
        cout << "This is child process, a signal was sent to parent" << endl;
   }
   else
   {
        signal(SIGUSR1, sigusr1);
        cout << "This is parent process. Parent is going to sleep for 100 seconds " << endl;
        sleep(100);
     //    wait(NULL);
        cout << "This is parent process. After sleeping" << endl;
   }
   return 0;
}

// The program starts by defining a signal handler function sigusr1 to handle the SIGUSR1 signal. This function simply prints a message along with the value of the signal.
// The program then forks a child process using fork(). After forking, the pid variable holds the process ID of the child process.
// In the parent process (where pid > 0), it sets up the SIGUSR1 signal handler using the signal() function.
// If it's the child process (where pid == 0), it waits for 1 second (sleep(1)) and then sends a SIGUSR1 signal to its parent process using kill(getppid(), SIGUSR1).
// After sending the signal, the child process prints a message indicating that a signal was sent to the parent.
// Meanwhile, the parent process prints a message indicating that it's going to sleep for 100 seconds using sleep(100).
// While the parent process is sleeping, it is waiting for a signal. Once the parent process receives the SIGUSR1 signal sent by the child process, the signal handler sigusr1 is invoked.
// The signal handler function sigusr1 prints a message indicating that it is the signal handler and also prints the value of the signal.
// After handling the signal, the parent process continues its execution and prints a message indicating that it has finished sleeping.
// The program then terminates.