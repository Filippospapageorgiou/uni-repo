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
     

   for (;;)  {
     printf("Waiting for a connection...\n");
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd<0) 
          error("ERROR on accept");

            if (fork() == 0) {  // Child process
                close(sockfd); // Close the listening socket in the child process
                printf("Connected.\n");
            
                while (1) { // Use an infinite loop for clearer logic
                    n = recv(newsockfd, str, 100, 0); // Receive data from client
                    if (n <= 0) break; // If recv returns 0, the client closed the connection, or an error occurred
                    
                    str[n] = '\0'; // Null-terminate the received data, assuming it's a valid string
                    
                    if (strcmp(str, "exit") == 0) { // Correctly compare received string with "exit"
                        send(newsockfd, "Bye Bye", 7, 0); // Send farewell message
                        break; // Exit the loop to close the connection
                    } else {
                        send(newsockfd, str, n, 0); // Echo the received message back to the client
                    }
                }
            
                close(newsockfd); // Close the connection socket in the child process
                exit(0); // Exit the child process
            }
   }
            
     return 0; 
}

