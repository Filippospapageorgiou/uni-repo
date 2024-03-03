#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h> 

#define N 4
#define mpi_root 0



int main(int argc,char **argv)
{
    int i,j,np,me,flag=0,sum=0,count=0,abs_value=0,loc_max=0,fin_max=0,big_flag=0,min_loc=0,min_pos;
    int root=0;
    int x[N][N];
    int y[N],B[N][N],loc_B[N];
    int *receive,*final_max,*final_min,fin_min,pos[N];
    int *sendcnt,*recvnt,*offset1,*offset2;

    //Συναρτησεις για αρχικοποιήση MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

    // Κατανομή μνήμης για τους πίνακες επικοινωνίας MPI
    sendcnt=(int*)malloc(N*sizeof(int));
    offset1=(int*)malloc(N*sizeof(int));
    receive=(int*)malloc(N*sizeof(int));
    final_max=(int*)malloc(N*sizeof(int));
    final_min=(int*)malloc(N*sizeof(int));


    // Αρχικοποίηση των μετρήσεων αποστολής και των μετατοπίσεων για τη διανομή των γραμμών του πίνακα
    for(i=0; i<N; i++){
        sendcnt[i]=N;
        offset1[i]=i*N;
    }
     // Η διεργασία ρίζας εισάγει τον πίνακα Α από τον χρήστη
    if(me==mpi_root){
        for(i=0; i<N; i++){
            for(j=0; j<N; j++){
                printf("Dwse A[%d][%d]=\n",i,j);
                scanf("%d",&x[i][j]);
            }
        }
        printf("Pinakas A:\n");
        for(i=0; i<N; i++)
        {
            for(j=0; j<N; j++)
            {
               printf("|%d",x[i][j]);
            }
            printf("\n");
        }
    }

    // Διασκορπίστε τις γραμμές του πίνακα A σε όλες τις διεργασίες
    MPI_Scatterv(&x, sendcnt,offset1, MPI_INT, &y, sendcnt[me], MPI_INT, mpi_root,
    MPI_COMM_WORLD);

    //Περιμένετε να φτάσουν όλες οι διεργασίες σε αυτό το σημείο
    MPI_Barrier(MPI_COMM_WORLD);

    // Κάθε διεργασία υπολογίζει το άθροισμα των απόλυτων τιμών 
    //των μη διαγώνιων στοιχείων της γραμμής της
    for(i=0; i<N; i++){
        if(i!=me)
        {
            sum+=abs(y[i]);
        }
    }
    if(abs(y[me])>sum)
    {
        flag=1;
    }

    //Μαζεύω όλο τα flag σε ένα πίνακα receive
    MPI_Gather(&flag, 1, MPI_INT, receive, 1, MPI_INT, mpi_root, MPI_COMM_WORLD);

    //Η διεργασία 0 ελένχει αν είναι ο πίνακας αυστηρά διαγωνίος
    if (me == mpi_root) {
        for (i = 0; i <N; i++) {
            if(receive[i]==1)
             count++;
        }
        if(count==N){
         printf("\n  'YES' ");
         big_flag=1;
        } 
        else
         printf("\n  'NO' ");
    }

    //η μητρικη διεργασία μοιράζει παντού το big_flag ώστε να 
    //ξερούμε αν θα συνεχίσουμε την ασκήση ή οχι
    MPI_Bcast(&big_flag,1,MPI_INT,mpi_root,MPI_COMM_WORLD);

    if(big_flag)
    {
    //Καθε διεργασία βρίσκει το max του τοπικού πίνακα της
    for(i=0; i<N; i++)
    {
        abs_value=abs(y[i]);
        if(loc_max<abs_value)
         loc_max=abs_value;
    }
    //Τα κάνω gather σε έναν τελικό πίνακα final_max
    MPI_Gather(&loc_max,1,MPI_INT,final_max,1,MPI_INT,mpi_root,MPI_COMM_WORLD);
    if(me==mpi_root)
    {

        for(i=0; i<N; i++)
        {
            if(fin_max<final_max[i])
             fin_max=final_max[i];
        }
        printf("\nTo MAX se apoliti timi einai:|%d|",fin_max);
    }
    //Βρισκέι το max η μητρική διεργασία και το διαμειράζει στις υπολοίπες διεγρασίες
    MPI_Bcast(&fin_max,1,MPI_INT,mpi_root,MPI_COMM_WORLD);

    // Κατανομή μνήμης για τη συλλογή των τροποποιημένων σειρών στον 
    //κινουρηιο πίνακα Β
    recvnt=(int*)malloc(N*sizeof(int));
    offset2=(int*)malloc(sizeof(int));
    
    for(i=0; i<N; i++){
     recvnt[i]=N;
     offset2[i]=i*N;
    }

    

    for(i=0; i<N; i++)
    {
        loc_B[i]=fin_max-abs(y[i]);
    }

    //Gather της γραμμές του Β στην μητρική διεργασία
    MPI_Gatherv(loc_B,recvnt[me],MPI_INT,&B,recvnt,offset2,MPI_INT,root,MPI_COMM_WORLD);


    //Η μητρική διεργασία εμφανίζει τον καινουργίο πίνακα
    if(me==mpi_root)
    {
        printf("\nO kainougios Pinakas B:\n");
        for (i=0; i<N; i++) {
         for (j=0; j<N; j++) {
           printf("|%4d|", B[i][j]);
           }
           printf("\n"); 
        }
    } 

     // Κάθε διεργασία βρίσκει την ελάχιστη απόλυτη τιμή στην 
     //τροποποιημένη σειρά της και τη θέση της
     min_loc = abs(loc_B[0]);
     min_pos = 0;
     for (i = 0; i < N; i++) {
            abs_value = abs(loc_B[i]);
            if (min_loc > abs_value) {
                min_loc = abs_value;
                min_pos = i;
            }
        }
        // Συγκεντρώσα τις ελάχιστες τιμές και τις θέσεις τους στη ρίζα
        MPI_Gather(&min_loc, 1, MPI_INT, final_min, 1, MPI_INT, mpi_root, MPI_COMM_WORLD);
        MPI_Gather(&min_pos, 1, MPI_INT, pos, 1, MPI_INT, mpi_root, MPI_COMM_WORLD);
        // Η διαδικασία Root βρίσκει το συνολικό ελάχιστο και τη θέση του
        if (me == mpi_root) {
            fin_min = final_min[0];
            min_pos = pos[0];
            int i_pos=0;
            for (i = 1; i < N; i++) {
                if (fin_min > final_min[i]) {
                    fin_min = final_min[i];
                    i_pos = i;
                    min_pos = pos[i];
                }
            }
            printf("\nTo MIN se apoliti timi einai |%d| se thesi i=%d kai j=%d",fin_min, i_pos,min_pos);
        }

    }



    free(sendcnt);
    free(offset1);
    free(receive);
    free(final_max);
    free(final_min);
    MPI_Finalize();
    
}
