#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Socket_Client.h"

using namespace std;

int main(int argc, char *argv[])
{
     myClient client(argv[1]);
     cout << "run client ..." << endl;
     client.runClient();
}
