#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include<netinet/in.h>
#include<pthread.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    if (argc <2)
    {
        fprintf(stderr, "Error, no port provided\n");
        exit(1);
    }


/*creating the server socket */ 
sockfd= socket(AF_INET, SOCK_STREAM, 0);
if (sockfd<0)
   error("Error opening the socket");

/*fill in port number and to listed on. IP address can be anything (INADDR_ANY)*/
bzero((char *)&serv_addr, sizeof(serv_addr));
portno = atoi(argv[1]);
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port= htons(portno);

/* now bind the socket to this port on this machine (server machine)*/

if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
   error("Error on binding");

/*listed for incoming connection requests */ 
listen(sockfd, 5);
clilen =sizeof(cli_addr);


/*accept a new request and create a newsockfd*/
newsockfd =accept(sockfd, (struct sockaddr*)&cli_addr,&clilen);
if (newsockfd<0)
   error("Error on accept");

/*read message form the clinet */
while(1){
bzero(buffer, 256);
n = read(newsockfd, buffer, 255);
if (n<0)
  error("ERROR reading from socket");
printf("Here is the message: %s", buffer);


/*send reply to clinet*/
n = write(newsockfd, buffer, 256);
if(n<0)
  error("Error wrting to socket");
}

}