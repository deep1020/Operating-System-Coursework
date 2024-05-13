#include <iostream>
#include <cstdlib>
#include <pthread.h>

// #define NUM_THREADS 5

using namespace std;

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   cout << "Hello World! Thread ID, " << tid << endl;
   pthread_exit(NULL);
}

int main ()
{
   pthread_t threads[5];
   int rc;
   int i;
   for(i=0; i < 5; i++){
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}

// PrintHello which takes a void pointer threadid as an argument. Inside function, it casts the threadid to a long integer(tid)
// and prints "Hello World! Thread ID, " followed by the thread ID (tid). Then, it exits the thread using pthread_exit(NULL).
// pthread_t is a data type in the threads (pthread) library used to represent a thread identifier

// System calls
// pthread library functions indirectly invoke system calls when managing threads
// pthread_create(): creates a new thread. Internally, it may involve system calls to allocate resources for the new thread and set up its execution context.
// pthread_exit(): terminates the calling thread and returns a value to the thread's creator (if any)
// Internally, it may involve system calls to clean up thread-specific resources.

// Variables
// pthread_t threads[5]: array of pthread_t and it stores the thread IDs of the threads created by the pthread_create() function
// rc: integer variable is used to store the return value of the pthread_create() 
// int i: loop counter in the for loop to iterate over the array of threads and create each thread sequentially

// Initial values of variables
// pthread_t threads[5]: the initial values of variables declared within a function are indeterminate unless explicitly initialized. 
// Therefore, the initial values of the elements in the threads array are undefined.
// int rc: Similar to the array, its initial value is indeterminate.
// int i: This integer variable is declared but not initialized.