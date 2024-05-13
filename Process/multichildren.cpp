#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;
int main(){
    int pid[3];
    pid[0] = fork(); 
    if (pid[0] > 0) 
    {   
        cout << "[parent] 1 pid = " << getpid() << endl;
        pid[1] = fork();
        if (pid[1] > 0)
        {
          cout << "[parent] 2 pid = " << getpid() << endl;
          pid[2] = fork();
          if (pid[2] > 0)
          {
            cout << "[parent] 3 pid = " << getpid() << endl;
          }
          else if (pid[2] == 0)
          {
            cout << "[child 3] pid = " << getpid() <<  endl;
            exit(3);
          }
        }
        else if (pid[1] == 0) 
        {   
          cout << "[child 2] pid = " << getpid() <<  endl;
          exit(2);
        }
        for(int i = 0; i < 3; i++)
        {
          waitpid(pid[i],NULL,0);
        }
        cout << "[parent] 1 finished " << endl;
    } 
    else if (pid[0] == 0) 
    {   
        cout << "[child 1] pid = " << getpid() << endl;
        exit(1);
    }
}

// waitpid(): wait for many children

