#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main()
{
    int pid;
    pid = fork();
    if (pid == 0) // This is child process
    {
      cout << "This is Child Process. pid = " << getpid() << endl;
    }
    else // This is parent process
    {
      cout << "This is Parent Process. pid = " << getpid() << endl;
      wait(NULL); // wait for child process to finish
      cout << "This is Parent Process. Finished " << endl;
    }
}