#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define BUFLEN 512  //Max length of buffer
 
int main(int argc, char *argv[])
{
    struct sockaddr_in si_other;
    struct sockaddr_in cli_addr;
    int s, i, portno, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
    struct hostent *server;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    s=socket(AF_INET, SOCK_DGRAM, 0);

    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(0);
    cli_addr.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
 
    bzero((char *) &si_other, sizeof(si_other));
    si_other.sin_family = AF_INET;

    server = gethostbyname(argv[1]);
    bcopy((char *)server->h_addr,
    (char *)&si_other.sin_addr.s_addr,
    server->h_length);

    portno = atoi(argv[2]);
    si_other.sin_port = htons(portno);

    // inet_aton("192.168.0.70", &si_other.sin_addr); 
 
    while(1)
    {
        printf("Enter message : ");
        fgets(message, BUFLEN, stdin);

        //send the message
        sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen);
         
        //receive a reply and print it
        memset(buf,'\0', BUFLEN);
        recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
         
        puts(buf);
    }
 
    close(s);
    return 0;
}
