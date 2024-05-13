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

  cout << "SignalValue: " << signalVal << '\n'; // 0
  cout << "SIGNIT "<< '\n';
  cout << "Sending signal " << SIGINT << '\n'; // 2
  raise(SIGINT);

  cout << "SignalValue: " << signalVal << '\n'; // 2
  cout << "SIGQUIT "<< '\n';
  cout << "Sending signal " << SIGQUIT << '\n'; // 3
  raise(SIGQUIT); // Quit dump core, after that it won't print anything

  cout << "SignalValue: " << signalVal << '\n'; // 2
  cout << "SIGILL "<< '\n';
  cout << "Sending signal " << SIGILL << '\n'; // 4
  raise(SIGILL); // Illigal instruction, after that it won't print anything

  cout << "SignalValue: " << signalVal << '\n'; // 2
  cout << "SIGHUP "<< '\n';
  cout << "Sending signal " << SIGHUP << '\n'; // 1
  raise(SIGHUP); // Hangup, after that it won't print anything

  cout << "SignalValue: " << signalVal << '\n'; // 2
  cout << "SIGABRT "<< '\n'; 
  cout << "Sending signal " << SIGABRT << '\n'; // 6
  raise(SIGABRT); // Abort signal, after that it won't print anything

  cout << "SignalValue: " << signalVal << '\n';
  cout << "SIGKILL "<< '\n';
  cout << "Sending signal " << SIGKILL << '\n'; // 9
  raise(SIGKILL); // Hard Kill signal, after that it won't print anything

}
