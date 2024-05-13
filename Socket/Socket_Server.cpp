#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Socket_Server.h"

using namespace std;

int main()
{
     myServer server;
     cout << "run server ..." << endl;
     server.runServer();
     return 0;
} 
