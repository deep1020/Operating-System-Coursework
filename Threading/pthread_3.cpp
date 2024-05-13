#include <iostream>
#include <cstdlib>
#include <pthread.h>
using namespace std;

struct thread_data{
   int  thread_id;
   char *message;
};
void *PrintHello(void *threadarg)
{
   struct thread_data *my_data;
   my_data = (struct thread_data *) threadarg;
   cout << "Thread ID : " << my_data->thread_id << ",";
   cout << " Message : " << my_data->message << endl;
   pthread_exit(NULL);
}
int main ()
{
   pthread_t threads[5];
   struct thread_data td[5];
   int rc;
   int i;
   for(i=0;i<5;i++){
      cout <<"main() : creating thread, " << i << endl;
      td[i].thread_id = i;
      td[i].message = "This is message";
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&td[i]);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}

// struct thread_data td[5]: This array of thread_data structures is used to hold the thread-specific data for each thread. 
// Each element represents the data for a thread.

// defines a structure thread_data, which contains two fields: thread_id of type int and message of type char*. 
// This structure is used to pass data to the threads.

// PrintHello(): thread start routine. It takes a void* argument (which is expected to be a pointer to a thread_data structure),
// casts it to thread_data*, and prints the thread ID and message stored in the structure. Then, it exits the thread.
// array of pthread_t variables threads is declared to store the thread IDs of the created threads.
// array of thread_data structures td is declared to store the thread data for each thread.
// Inside the loop, thread data is initialized for each thread: the thread_id is set to the loop index i, and 
// the message is set to "This is message".

// pthread_create(): create each thread. It takes the address of the thread ID variable, NULL as the thread attributes,
// PrintHello function as the thread start routine, and a pointer to the thread data structure as the argument.

// If an error occurs during thread creation, an error message is printed, and the program exits with an error code.
// After creating all threads, the pthread_exit(NULL) function is called to wait for all threads to finish execution before the main function exits.