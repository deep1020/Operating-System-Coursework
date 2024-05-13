#include <iostream>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

void *print_message_function( void *ptr )
{
    char *message;
    message = (char *) ptr;
    cout << message << endl;
}

int main()
{
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int  iret1, iret2;
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL); 
    cout << "Thread 1 returns: " << iret1 << endl;
    cout << "Thread 2 returns: " << iret2 << endl;
    pthread_exit(NULL);
}

// print_message_function function takes a void pointer ptr as an argument, which is cast to a char* and assigned to variable message. 
// Then, it prints the message to the standard output

// pthread_create is called twice to create two threads:
// The first call creates thread1 and executes print_message_function with message1 as the argument.
// The second call creates thread2 and executes print_message_function with message2 as the argument.

// pthread_join is called twice to wait for both threads to finish executing before continuing. 
// This ensures that the main thread doesn't exit before the created threads complete their execution.
// without pthread_join, it gives unorder execution of thread1 and thread2 

// pthread_exit function is called to exit the main thread and wait for all other threads to terminate.