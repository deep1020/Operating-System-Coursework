#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(){
    int pid = fork();
    int child_exit_value;
    if (pid == 0)
    {
        cout<< "This is child process" << endl; 
        cout << "Child process pid = " << getpid() << endl;
        sleep(2);
        exit(8); // exit from child process, Don't go to program_a_wait.cpp file
        execl("./program_a_wait", "program_a_wait", NULL);
    }
    else
    {
        child_exit_value = 0;
        wait(&child_exit_value);
        cout << "Parent process pid = " << getpid() << endl;
        cout << "The exit system call in Child process return value : " << endl;
        cout << WEXITSTATUS(child_exit_value) << endl;
    }
    return 0;
}

// System call:
// fork(): To create a new subprocess, resulting in two separate process (parent and child)
// execl(): Execute and leave, To replace child process with program_a_wait using specified path and arguments
// wait(): To wait for child process program_b_wait to finish execution before continuing
// sleep(): Suspend execution of current process for a specified number of seconds
// exit(): Terminate the process and returns exit value
// WEXITSTATUS(): return value of exit system call

// Variables:
// pid of type int(or use pid_t) declared to store return value of fork() system call
// pid storing process Id returned by fork()
// child_exit_value

// Initial values:
// pid of type int initialized with return value of fork() system call. 
// If fork() successfully creates a child process, pid will contain PID of child process in parent process and 0 in child process
// If fork() fails, pid will be set to -1 indicating an error  
// child_exit_value initialized with 0. This ensures that if wait() fails for some reason and doesn't update the value of
// child_exit_value, it will still have a meaningful default value.