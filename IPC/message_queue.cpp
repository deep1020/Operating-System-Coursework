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
       msgbuffer sbuf;
       size_t buf_len;
       key = 1234;
       cout << "In parent process, Call msgget to get a Message Queue" << endl;
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
}
// Message queues provide an asynchronous communications protocol, it means the sender and receiver of the message do not need
// to interact with the message queue at the same time.
// Messages placed onto the queue are stored until the recipient retrieves them. 

// Declare a structure msgbuffer to hold messages content. 
// It contains a long member mtype to specify the message type and a character array messageContent

// parent process (pid > 0)
// It initializes a message queue using msgget() with a specified key (1234) and permissions (0666).
// It constructs a message sbuf with type 1 and some content.
// It sends the message using msgsnd() to the message queue.
// It waits for the child process to terminate using wait().
// After the child process terminates, it removes the message queue using msgctl() with the IPC_RMID command.

// child process (pid==0)
// It initializes the message queue using msgget() with the same key and permissions.
// It receives a message from the message queue using msgrcv().
// It prints the received message content.

// system call
// fork(): create a new process (child process) by duplicating the calling process (parent process).
// msgget(): create a new message queue or to obtain the identifier of an existing message queue.
// msgsnd(): send a message to a message queue.
// msgrcv(): receive a message from a message queue.
// wait(): used by the parent process to wait for the child process to terminate.
// msgctl(): clean up/remove queue

// variables
// pid: store the process ID returned by the fork() system call.
// msqid: store the message queue ID returned by the msgget() system call.
// msgflg: specify the flags for creating the message queue. It is initialized with the value IPC_CREAT | 0666.
// key: A key_t variable used to specify the key for identifying the message queue. It is initialized with the value 1234.
// sbuf: An instance of the msgbuffer structure used to hold the message to be sent.
// rbuf: An instance of the msgbuffer structure used to hold the received message.

// Initial values of variables
// pid: No initial value is explicitly assigned. It will be assigned the process ID returned by the fork() system call.
// msqid: No initial value is explicitly assigned. It will be assigned the message queue ID returned by the msgget() system call.
// msgflg: Initialized with the value IPC_CREAT | 0666, message queue should be created if it does not exist (IPC_CREAT), 
// and its permissions are set to 0666.
// key: Initialized with the value 1234, which serves as the key for identifying the message queue.
// sbuf: No initial value is explicitly assigned. It will be initialized with the message type and content before sending.
// rbuf: No initial value is explicitly assigned. It will be initialized with the received message content after receiving.