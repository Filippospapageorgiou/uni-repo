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
    int testint; 
    float testfloat;
    char buf[BUFLEN];
    char *cur;
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
        printf("Enter an integer : ");
        scanf("%d", &testint);
        printf("\nEnter a double : ");
        scanf("%f", &testfloat);

        //send the numbers
        sprintf(buf, "%d %f", testint, testfloat);
        sendto(s, buf, strlen(buf), 0, (struct sockaddr *) &si_other, slen);
         
        //receive as reply the same numbers multplied by 5 
        recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
        testint = strtol(buf, &cur, 10);
        testfloat = strtof(cur, NULL);
        printf("Data: %d %f\n", testint, testfloat);
    }
 
    close(s);
    return 0;
}
