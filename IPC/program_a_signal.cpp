#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;
void signalHandler(int signal) {
    // Execute tasks of program A
    cout << "Program A tasks" << endl;
}
int main() {
    // Register signal handler for SIGUSR1 signal
    signal(SIGUSR1, signalHandler);
    // Wait for SIGUSR1 signal from program B
    cout << "Waiting for signal from Program B" << endl;
    pause(); // pause is required to execute signalHandler method which prints Program A tasks
    return 0;
}