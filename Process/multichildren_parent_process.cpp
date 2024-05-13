#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    int pid[3];
    pid[0] = fork();
    if (pid[0] > 0) {
        cout << "[parent] 1 pid = " << getpid() << endl;
        pid[1] = fork();
        if (pid[1] > 0) {
            cout << "[parent] 2 pid = " << getpid() << endl;
            pid[2] = fork();
            if (pid[2] > 0) {
                cout << "[parent] 3 pid = " << getpid() << endl;
            } else if (pid[2] == 0) {
                execl("./multichildren_child_process", "multichildren_child_process", nullptr);
            }
        } else if (pid[1] == 0) {
            execl("./multichildren_child_process", "multichildren_child_process", nullptr);
        }
        for (int i = 0; i < 3; i++) {
            waitpid(pid[i], NULL, 0);
        }
        cout << "[parent] 1 finished " << endl;
    } else if (pid[0] == 0) {
        execl("./multichildren_child_process", "multichildren_child_process", nullptr);
    }
    return 0;
}
