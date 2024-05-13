#include <csignal>
#include <signal.h>
#include <iostream>

using namespace std;

int signalVal;

void signal_handler(int signal)
{
  signalVal = signal;
}

int main()
{
  signal(SIGINT, signal_handler);
  cout << "SignalValue: " << signalVal << '\n'; // signalVal -> 0
  cout << "SIGINT "<< '\n';
  cout << "Sending signal " << SIGINT << '\n';
  raise(SIGINT);
  cout << "SignalValue: " << signalVal << '\n'; // SIGINT -> 2
  cout << "SIGABRT "<< '\n';
  cout << "Sending signal " << SIGABRT << '\n';
  raise(SIGABRT);
  cout << "SignalValue: " << signalVal << '\n'; // SIGABRT -> 6
}
// Signals are sent to a process when an event occurs
// When a signal is sent, the operating system interrupts the target process's normal flow of execution to deliver the signal

// SIGHUP -> Hangup -> signal value: 1 
// SIGINT -> INTERRUPT -> signal value: 2
// SIGQUIT -> QUIT DUMP CORE -> signal value: 3
// SIGILL -> ILLEGAL INSTRUCTION -> signal value: 4
// SIGABRT -> Abort signal -> signal value: 6
// SIGKILL -> Hard Kill signal -> signal value: 9

// system call:
// raise(): sends the specified signal to the current process