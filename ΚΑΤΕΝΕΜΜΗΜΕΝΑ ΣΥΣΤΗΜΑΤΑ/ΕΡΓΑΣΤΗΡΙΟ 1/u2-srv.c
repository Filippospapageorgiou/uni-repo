#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 512  //Max length of buffer

int main(int argc, char *argv[])
{
    struct sockaddr_in si_me, si_other;
    int s, i, portno, slen = sizeof(si_other);
    int recv_len, testint;
    float testfloat;
    char *cur;
    char buf[BUFLEN];

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\nRun as ./u2-srv PORT\n");
         exit(1);
     }

    //create a UDP socket
    s=socket(AF_INET, SOCK_DGRAM, 0);

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    portno = atoi(argv[1]);
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(portno);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    bind(s, (struct sockaddr*)&si_me, sizeof(si_me));
     
    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);

        memset(buf,'\0', BUFLEN);
        //try to receive an integer
        recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
         
        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));

        testint = strtol(buf, &cur, 10);
        testfloat = strtof(cur, &cur);
        printf("Data: %d %f\n", testint, testfloat);
         
        //now reply the client with the same numbers multiplied by 5 
        testint = testint * 5;
        testfloat = testfloat * 5;
        sprintf(buf, "%d %f", testint, testfloat);
        sendto(s, buf, strlen(buf), 0, (struct sockaddr*) &si_other, slen);
    }
 
    close(s);
    return 0;
}
