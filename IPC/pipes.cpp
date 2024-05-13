#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main()
{
    int status, pid, pipefds[2];
    char msgString[22];
    status = pipe(pipefds);
    pid = fork();
    if (pid == 0) 
    {
        close(pipefds[0]);
        cout << "Send a message: " << endl;
        // sleep(1);
        write(pipefds[1], "pipe message succeed!", 22);  
        close(pipefds[1]);
        // exit(0);
    }
    else
    {
        close(pipefds[1]);
        read(pipefds[0], msgString, 22);
        // wait(NULL);
        cout << "Received a message: " << msgString << endl;
        close(pipefds[0]);
        // exit(0);
    }
}
// In the child process (where pid == 0), it closes the read end of the pipe (pipefds[0]) since it will only write to the pipe. 
// Then it prompts the user to enter a message, writes the message to the pipe using the write() system call, and 
// finally closes the write end of the pipe (pipefds[1]). After that, it exits.

// In the parent process (where pid > 0), it closes the write end of the pipe (pipefds[1]) since it will only read from the pipe. 
// Then it reads from the pipe using the read() system call into the msgString buffer. It prints the received message and 
// closes the read end of the pipe (pipefds[0]). Finally, it exits.

// system call
// pipe(): creates a pipe, a unidirectional data channel that can be used for inter-process communication.
// close(): close a file descriptor. In the program, it is used to close unnecessary ends of the pipe in each process.
// write(): write data into a file descriptor. In the program, it is used by the child process to write a message to the write end of the pipe.
// read(): read data from a file descriptor. In the program, it is used by the parent process to read the message from the read end of the pipe.

// variables
// status: An integer variable used to store the return value of the pipe() system call.
// pid: An integer variable used to store the process ID returned by the fork() system call.
// pipefds: An array of integers used to represent the file descriptors of the pipe. 
// It holds two elements, one for the read end and one for the write end of the pipe.
// msgString: A character array used to store the message read from the pipe by the parent process. 