#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <signal.h>

using namespace std;
struct /*class*/ msgbuffer
{
 public:
   long mtype;
   char messageContent[1024];
};

int main(){
    int msqid;
    key_t key;
    msgbuffer rbuf;
    key = 1234;
    cout << "In child, Call msgget to get the same Message Queue" << endl;
    msqid = msgget(key, 0666);
    msgrcv(msqid, &rbuf, 1024, 1, 0);
    cout << "this is child. I got it:  " << rbuf.messageContent << endl;
    exit(0);
}