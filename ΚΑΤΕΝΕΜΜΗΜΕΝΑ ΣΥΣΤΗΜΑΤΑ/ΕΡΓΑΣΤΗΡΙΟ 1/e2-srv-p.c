#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void *echo_function (void *arg)
       {
        int so = (int) arg;
        int done, n;
        char str[100];

            printf("Connected.\n");

            done = 0;
            do {
                n = recv(so, str, 100, 0);

                send(so, str, n, 0);

                if (n==1) done = 1;

            } while (!done);

         close(so);
         pthread_exit(NULL);
        }

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen, i;
     struct sockaddr_in serv_addr, cli_addr;
     pthread_t thread[50];

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
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

   i=0;

   for (;;)  {
     printf("Waiting for a connection...\n");
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");

     pthread_create(&(thread[i++]), NULL, echo_function, (void *)newsockfd);

   }
            
     return 0; 
}

