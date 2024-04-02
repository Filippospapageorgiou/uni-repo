#include <stdio.h>   // Περιλαμβάνει βιβλιοθήκη για είσοδο/έξοδο.
#include <stdlib.h>  // Περιλαμβάνει βιβλιοθήκη για γενικούς σκοπούς (π.χ. exit).
#include <string.h>  // Περιλαμβάνει βιβλιοθήκη για εργασίες με συμβολοσειρές.
#include <sys/types.h> // Ορισμοί τύπων δεδομένων για συστηματικές κλήσεις.
#include <sys/socket.h> // Περιλαμβάνει βιβλιοθήκη για δικτυακές λειτουργίες socket.
#include <netinet/in.h> // Περιλαμβάνει δομές για διευθύνσεις δικτύου.
#include <netdb.h>  // Περιλαμβάνει λειτουργίες για διευθύνσεις διακομιστών.
#include <unistd.h> // Περιλαμβάνει πολλές POSIX συναρτήσεις και μακροεντολές.
#include <arpa/inet.h> // Περιλαμβάνει λειτουργίες για διαδικτυακές διευθύνσεις.

void error(char *msg)
{
	perror(msg); // Εμφανίζει το μήνυμα λάθους στο stderr.
    exit(0); // Εξοδος από το πρόγραμμα με κωδικό 0.
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    // Ελέγχει αν δόθηκαν αρκετά ορίσματα (hostname και port).
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]); // Μετατροπή του αριθμού θύρας από string σε int.
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // Δημιουργία TCP socket.
    if (sockfd < 0) 
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr)); // Αρχικοποίηση δομής διεύθυνσης server.
    serv_addr.sin_family = AF_INET; // Ορισμός τύπου διεύθυνσης IPv4.
    serv_addr.sin_port = htons(portno); // Ορισμός αριθμού θύρας.

    inet_aton(argv[1], &serv_addr.sin_addr); // Μετατροπή IP διεύθυνσης από string σε binary.

    // Προσπάθεια σύνδεσης με τον server.
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    printf("Please enter the message: "); // Προτροπή για εισαγωγή μηνύματος.
    bzero(buffer,256); // Καθαρισμός του buffer.
    fgets(buffer,255,stdin); // Ανάγνωση μηνύματος από το πληκτρολόγιο.
    n = write(sockfd,buffer,strlen(buffer)); // Αποστολή μηνύματος στον server.
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256); // Καθαρισμός του buffer.
    n = read(sockfd,buffer,255); // Λήψη απάντησης από τον server.
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer); // Εμφάνιση της απάντησης.
    return 0;
}
