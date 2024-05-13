#include <csignal>
#include <iostream>

using namespace std;

void int_handler(int x)
{
   cout <<"CTL+C is disabled to quit press return" << endl;
}

int main()
{
   signal(SIGINT,int_handler);
   cout <<"Press ctrl+c" << endl;
   cin.get();
}

// signal() function is called to set up the custom signal handler for the SIGINT signal (Ctrl+C). 
// It takes two arguments: the signal to be handled (SIGINT) and the handler function (int_handler).
// cin.get() function is called to wait for the user to press the Enter key. 
// This allows the program to continue running until the user manually terminates it by pressing Enter, 
// rather than allowing Ctrl+C to terminate it immediately.

// When the user presses Ctrl+C, the SIGINT signal is sent to the program. 
// Instead of terminating, the custom signal handler function int_handler is executed, which prints the message 