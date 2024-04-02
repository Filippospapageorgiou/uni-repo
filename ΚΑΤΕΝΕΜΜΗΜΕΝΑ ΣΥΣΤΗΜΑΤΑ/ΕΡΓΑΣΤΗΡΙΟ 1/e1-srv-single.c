#include <stdio.h>   // Συμπεριλαμβάνει τη βιβλιοθήκη stdio για είσοδο/έξοδο
#include <stdlib.h>  // Συμπεριλαμβάνει τη βιβλιοθήκη stdlib για γενικές λειτουργίες όπως έξοδος
#include <string.h>  // Συμπεριλαμβάνει τη βιβλιοθήκη string για εργασίες με συμβολοσειρές
#include <sys/types.h> // Ορισμοί τύπων δεδομένων
#include <sys/socket.h> // Συμπεριλαμβάνει τη βιβλιοθήκη socket για δικτυακές επικοινωνίες
#include <netinet/in.h> // Ορίζει δομές διευθύνσεων και λειτουργίες για το δίκτυο
#include <unistd.h>  // Παρέχει πρόσβαση σε POSIX λειτουργικές κλήσεις όπως read, write, close

void error(char *msg)
{
	perror(msg); // Εκτυπώνει το μήνυμα λάθους στο stderr
    exit(1); // Εξέρχεται από το πρόγραμμα με κωδικό λάθους 1
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen, n;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     
     // Ελέγχει αν έχει δοθεί αριθμός θύρας ως όρισμα
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\nRun as ./e1-srv-single PORT\n");
         exit(1);
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0);  // Δημιουργεί ένα socket
     if (sockfd < 0) 
         error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr)); // Αρχικοποιεί τη δομή διεύθυνσης του server

     portno = atoi(argv[1]); // Μετατρέπει τον αριθμό θύρας από string σε int

     serv_addr.sin_family = AF_INET; // Ορίζει τον τύπο διεύθυνσης

     serv_addr.sin_port = htons(portno); // Ορίζει τον αριθμό θύρας

     serv_addr.sin_addr.s_addr = INADDR_ANY; // Ακούει σε όλες τις διευθύνσεις

     // Δένει το socket με την διεύθυνση
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
                  error("ERROR on binding");

     listen(sockfd,5); // Θέτει το socket σε κατάσταση ακρόασης

     // Απεριόριστος βρόχος για την επεξεργασία εισερχόμενων συνδέσεων
     while(1){
     	clilen = sizeof(cli_addr);
     	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); // Αποδέχεται μια εισερχόμενη σύνδεση
     	if (newsockfd < 0) 
          error("ERROR on accept");

     	bzero(buffer,256); // Αρχικοποιεί το buffer
     	n = read(newsockfd,buffer,255); // Διαβάζει δεδομένα από το socket
     	if (n < 0) error("ERROR reading from socket");
     	printf("Your message: %s\n",buffer); // Εκτυπώνει το μήνυμα που λήφθηκε

     	n = write(newsockfd,"I got your message",18); // Αποστέλλει μια απάντηση πίσω στον πελάτη
     	if (n < 0) error("ERROR writing to socket");

     	close(newsockfd); // Κλείνει την σύνδεση
     }

     return 0; 
}
