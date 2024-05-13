#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
using namespace std;

void *worker(void *arg)
{
    int i;
    for (i = 0; i < 5; i++) {
        cout <<"worker function"<<endl;
        // pthread_yield(); // not working
        pthread_yield_np();
    }
    return NULL;
}
int main()
{
    int i;
    pthread_t worker_tid;
    pthread_create(&worker_tid, NULL, worker, NULL);
    for (i = 0; i < 5; i++) {
        cout << "Main function"<<endl;
        pthread_yield_np();
    }
    pthread_join(worker_tid, NULL);
    //exit(0);
}

// system call:
// pthread_create(): create the worker thread. It takes the address of worker_tid, NULL as the thread attributes, 
// the worker function as the thread start routine, and NULL as the argument to be passed to the thread function.
// pthread_yield(): yield the CPU, allowing other threads to run. 
// The thread is placed at the end of the run queue for its static priority and another thread is scheduled to run

