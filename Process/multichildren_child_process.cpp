#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    // int pid[3];
    // pid[0] = fork();
    // if (pid[0] == 0) {
    //     cout << "[child 1] pid = " << getpid() << endl;
    //     exit(1);
    // } else {
    //     pid[1] = fork();
    //     if (pid[1] == 0) {
    //         cout << "[child 2] pid = " << getpid() << endl;
    //         exit(2);
    //     } else {
    //         pid[2] = fork();
    //         if (pid[2] == 0) {
    //             cout << "[child 3] pid = " << getpid() << endl;
    //             exit(3);
    //         }
    //     }
    // }
    // return 0;
    cout << "[child] pid = " << getpid() << endl;
    exit(0);
    // cout << "[child 2] pid = " << getpid() << endl;
    // cout << "[child 3] pid = " << getpid() << endl;
}
