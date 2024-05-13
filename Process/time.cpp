#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

using namespace std;

int main()
{
   int i;
   time_t time_local;
   for (int i = 0; i < 10; i++)
   {
      time(&time_local);
      cout << ctime(&time_local) << endl;
      sleep(1);
   }
} 
// system call
// ctime(): current time value (time_local) to convert it to a human-readable string representation of local time

// variable
// time_local of data type time_t is declared to store the current time.
