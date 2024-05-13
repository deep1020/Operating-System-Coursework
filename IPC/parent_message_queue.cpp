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
int main()
{ 
   int pid;
   pid = fork(); 
   if (pid > 0)
   {
       int msqid;
       int msgflg = IPC_CREAT | 0666;
       key_t key;
    //    key=ftok("parent_message_queue.cpp",1);
       msgbuffer sbuf;
       size_t buf_len;
       key = 1234;
       cout << "In parent process, Call msgget to get a Message Queue " << "For key: " << key << endl;
       msqid = msgget(key, msgflg);
       sbuf.mtype = 1;
       strcpy (sbuf.messageContent, "This is the message from sender parent to child \n");
       buf_len = sizeof(sbuf.messageContent);
       msgsnd(msqid, &sbuf, buf_len, IPC_NOWAIT);
       wait(NULL);
       msgctl(msqid, IPC_RMID, 0);
       exit(0);
   } 
   else if (pid == 0)
   { 
       execl("./child_message_queue","child_message_queue",NULL);
   }
   else{
        cout<< "Fork failed" << endl;
   }
}


