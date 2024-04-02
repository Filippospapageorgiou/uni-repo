#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen, n, done;
     char str[100];
     struct sockaddr_in serv_addr, cli_addr;
     pid_t childpid;
     

     

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\nRun as ./e2-srv PORT\n");
         exit(1);
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0); 
     if (sockfd < 0) 
         error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));

     portno = atoi(argv[1]);

     serv_addr.sin_family = AF_INET;

     serv_addr.sin_port = htons(portno);

     serv_addr.sin_addr.s_addr = INADDR_ANY;

     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
                  error("ERROR on binding");

     listen(sockfd,5);
     

    for (;;)  {
     printf("Waiting for a connection...\n");
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if((childpid = fork())==0){
     close(newsockfd);
     if (newsockfd < 0) 
          error("ERROR on accept");

                printf("Connected.\n");

                done = 0;
                do {
                  n = recv(newsockfd, str, 100, 0);

                  send(newsockfd, str, n, 0); 
   
                  if (n==1) done = 1;

                } while (!done);
              }
    }
          
     return 0; 
}

