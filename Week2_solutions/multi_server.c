// socket server example, handles multiple clients using threads

#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread

//the thread function
void *start_function(void *);
char buffer[256];
void error(char *msg)
{
    perror(msg);
    exit(1);
}
int main(int argc , char *argv[])
{
    int sockfd, newsockfd , c , *new_sock;
    int  portno;
    
    struct sockaddr_in server , client;

    //Create socket
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    portno = atoi(argv[1]);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);

    //Bind
    if( bind(sockfd,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(sockfd , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

        c=sizeof(struct sockaddr_in);
       while(newsockfd=accept(sockfd,(struct sockaddr*)&client,(socklen_t*)&c))
       {
        puts("Connection accepted");

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = newsockfd;

        if( pthread_create( &sniffer_thread , NULL ,  start_function , (void*) new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }

        puts("Working thread assigned");
    }

    if (newsockfd < 0)
    {
        error("accept failed");
        return 1;
    }
    return 0;
}
/*
  This will handle connection for each client
  */
void *start_function(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int n, temp;

        char    sendBuff[100], client_message[2000];
        bzero(buffer, 256);

      while((n=read(sock,buffer, 255))>0)
      {
        printf("Here is the message: %s", buffer);
        temp = write(sock, buffer, 256);
      }
      close(sock);

      if(n==0)
      {
        puts("Client Disconnected");
      }
      else
      {
        error("recv failed");
      }
    return 0;
}