#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>
#include <sys/sem.h>
#include <sys/ipc.h>
using namespace std;

sem_t empty, full; 
int data;
int numIters;
int SHARED = 1;
pthread_mutex_t mutex;

void *Producer(void *arg)
{
    int produced;
    for (produced = 1; produced <= numIters; produced++)
    {
        int tmpSemVal;
        sem_getvalue(&empty, &tmpSemVal);
        cout << "Before. This is producer. empty = " << tmpSemVal << endl;
        sem_getvalue(&full, &tmpSemVal);
        cout << "Before. This is producer. full = " << tmpSemVal << endl;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        data = produced;
        cout << "----------- produced: " << data << endl;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sem_getvalue(&empty, &tmpSemVal);
        cout << "After. This is producer. empty = " << tmpSemVal << endl;
        sem_getvalue(&full, &tmpSemVal);
        cout << "After. This is producer. full = " << tmpSemVal << endl;

        sleep(3);
    }
}

void *Consumer(void *arg)
{
    int total = 0;
    int consumed;
    for (consumed = 1; consumed <= numIters; consumed++)
    {
        int tmpSemVal;
        sem_getvalue(&empty, &tmpSemVal);
        cout << "Before. This is consumer. empty = " << tmpSemVal << endl;
        sem_getvalue(&full, &tmpSemVal);
        cout << "Before. This is consumer. full = " << tmpSemVal << endl;

        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        total = total +  data;
        cout << "----------- consumed: " << data << endl;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sem_getvalue(&empty, &tmpSemVal);
        cout << "Before. This is consumer. empty = " << tmpSemVal << endl;
        sem_getvalue(&full, &tmpSemVal);
        cout << "Before. This is consumer. full = " << tmpSemVal << endl;

        sleep(3);
    }
    cout << "The total is: " << total << endl;
}

int main()
{
   pthread_t pid, cid;
   pthread_attr_t attr;
   pthread_attr_init (&attr);
   pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

   sem_init(&empty, SHARED, 1); // empty = 1;
   sem_init(&full, SHARED, 0); //  full = 0;
   pthread_mutex_init(&mutex, NULL);
   numIters = 5;

   pthread_create(&pid, &attr, Producer, NULL);
   pthread_create(&cid, &attr, Consumer, NULL);
   pthread_join(pid, NULL);
   pthread_join(cid, NULL);
}
