#include <strings.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>

#define PORT 3490

#define MAXDATASIZE 100

using namespace std;

class myClient
{
     public:
            myClient(char *);
            void runClient();
     private:
            int    sockfd, numbytes;
            char   buf[MAXDATASIZE];
            struct hostent *he;
            struct sockaddr_in their_addr;
};

myClient::myClient(char *host_name)
{
    if ((he = gethostbyname(host_name)) == NULL)
    {
       cout << "gethostbyname error";
       return;
    }
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
       cout << "Socket error";
       return;
    }
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(PORT);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(their_addr.sin_zero, 8);
    
    return;
}
void myClient::runClient()
{
    if (connect(sockfd, (struct sockaddr *)&their_addr, 
                sizeof(struct sockaddr)) == -1)
    {
       cout << "Connect error";
       return;
    }
    if ((numbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1)
    {
       cout << " Receive error";
       return;
    }
    buf[numbytes] = '\0';
    cout << "This is in the client side ";
    cout << "Recived:  " << buf << endl;
    if (send(sockfd, "This is client: Nice to talk !", 100, 0)
 == -1)
    {
         cout << "send error";
         close(sockfd);
         return;
     }
}

