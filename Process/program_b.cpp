#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main()
{
    int pid = fork();
    if (pid == 0)
    { // Child process (Program A)
        // sleep(4);
        execl("./program_a", "program_a", NULL);
    }
    else if (pid > 0)
    { // Parent process (Program B)
        cout << "This is Program B" << endl;
        wait(NULL); // Wait for child process to finish
    }
    else
    {
        cout << "Fork failed." << endl;
    }
    return 0;
}

// System call:
// fork(): To create a new subprocess, resulting in two separate process (parent and child)
// execl(): Execute and leave, To replace child process with program_a using specified path and arguments
// when execl() is called, process stops executing that program and starts a new one
// wait(): To wait for child process program_b to finish execution before continuing

// Variables:
// pid of type int(or use pid_t) declared to store return value of fork() system call
// pid storing process Id returned by fork()

// Initial values:
// pid of type int initialized with return value of fork() system call. 
// If fork() successfully craetes a child process, pid will contain PID of child process in parent process and 0 in child process
// If fork() fails, pid will be set to -1 indicating an error  

