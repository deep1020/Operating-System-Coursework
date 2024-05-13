#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
using namespace std;
void signalHandler(int signal) {
    // Do nothing
}
int main() {
    // Spawn a child process for program A
    pid_t pid = fork();
    if (pid == -1) {
        // Handle error
        cout << "Error: failed to fork process A" << endl;
        return 1;
    } 
    else if (pid == 0) {
        // Child process (program A)
        execl("program_a_signal", "program_a_signal", NULL);
    } 
    else {
        // Parent process (program B)
        // Execute tasks of program B
        cout << "Program B tasks" << endl;
        // Wait for program A to be ready, sleep is required to execute program_b_signal
        sleep(1);
        // Send signal to program A to start executing its tasks
        cout << "Sending signal to Program A" << endl;
        kill(pid, SIGUSR1);
        cout << "Signal sent" << endl;
        // Wait for program A to finish executing its tasks
        // int status;
        // waitpid(pid, &status, 0);
        wait(NULL);
        cout<< "parent process after waiting to finish program A tasks" << endl;
    }
    return 0;
}