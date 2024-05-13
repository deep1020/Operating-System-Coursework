#include <strings.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 3490
#define MAXDATASIZE 100

#define BACKLOG 10

using namespace std;

class myServer
{
     public:
            myServer();
            void runServer();
     private:
            int    sockfd, new_fd;
            struct sockaddr_in my_addr;
            struct sockaddr_in their_addr;
            int    sin_size;
            char   buf[MAXDATASIZE];
            int    numbytes;
};

myServer::myServer()
{
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
       cout << "Socket error";
       return;
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(my_addr.sin_zero, 8);
    return;
}
void myServer::runServer()
{
    if (bind(sockfd, (struct sockaddr *)&my_addr, 
             sizeof(struct sockaddr)) == -1)
    {
       cout << "Bind error";
       return;
    }
    if (listen(sockfd, BACKLOG) == -1)
    {
       cout << "Listen error";
       return;
    }
    while(1)
    {
       sin_size = sizeof(struct sockaddr_in);
       //socklen_t* socklength;
       if ((new_fd = accept(sockfd, (struct sockaddr *) &their_addr, 
                            (socklen_t *)&sin_size)) == -1)
       {
         cout << "accept error";
         continue;
       }
       
       cout << "Server: got connection from: " 
            << inet_ntoa(their_addr.sin_addr) << endl;

       if (send(new_fd, "Hello, this is server !", 25, 0) == -1)
       {
         cout << "send error";
         close(new_fd);
         return;
       }
       if ((numbytes = recv(new_fd, buf, MAXDATASIZE, 0)) == -1)
       {
       cout << " Receive error";
       return;
       }
       buf[numbytes] = '\0';
       cout << "This is in the server side ";
       cout << "Recived:  " << buf << endl;
    }
}
 
