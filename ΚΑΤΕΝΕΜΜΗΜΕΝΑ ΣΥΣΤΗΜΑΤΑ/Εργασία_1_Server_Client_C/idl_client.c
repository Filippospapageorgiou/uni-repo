#include "idl.h"
#include <stdio.h>
#include <stdlib.h>

void interface_prog_1(char *host)
{
	CLIENT *clnt;
    float *result_1;
    intvector Obvector;
    intpair *result_2;
    floatvector *result_3;
    product ProductOb;

#ifndef	DEBUG
	clnt = clnt_create(host, INTERFACE_PROG, INTERFACE_VERS, "tcp");
    if (clnt == NULL) {
        clnt_pcreateerror(host);
        exit(1);
    }
#endif	/* DEBUG */
    printf("Connected to Server....\n\n");
    printf("Enter the lentgh of the integer Vector Y: ");
    if (scanf("%d", &Obvector.n) != 1) {
    	fprintf(stderr, "Invalid input\n");
    	exit(1);
	}
    Obvector.vector.vector_len=Obvector.n;
    Obvector.vector.vector_val=(int*)malloc(Obvector.n*sizeof(int));
    printf("Array of '%d' elements created....\n",Obvector.n);
    printf("Enter the elements of the integer vector Y:\n");
    for(int i=0; i<Obvector.n; i++){
    	printf("vector[%d]: ",i);
    	scanf("%d",&Obvector.vector.vector_val[i]);
    }

    int choice;
    do{
    	printf("Choose an operation:\n");
    	printf("1.Calculate Average\n");
    	printf("2.Find max and min\n");
    	printf("3.Multiply Scalar\n");
    	printf("0.Exit\n");
    	printf("Enter Choice: ");
    	scanf("%d",&choice);

    	switch(choice){
    		case 1:
                result_1 = calculate_average_1(&Obvector, clnt);
                if (result_1 == NULL) {
                   clnt_perror(clnt, "Call failed");
                } else {
                    printf("Average: %f\n", *result_1);
                }
                break;
            case 2:
                result_2 = find_max_min_1(&Obvector, clnt);
                if (result_2 == NULL) {
                    clnt_perror(clnt, "Call failed");
                }else {
                    printf("Max: %d, Min: %d\n", result_2->max, result_2->min);
                }
               	break;
            case 3:
            	printf("Enter the value 'a' you want to multiply vector: ");
            	scanf("%f",&ProductOb.a);
            	ProductOb.vector=Obvector;
                for(int j=0; j<ProductOb.vector.n; j++){
                    printf("%d",ProductOb.vector.vector.vector_val[j]);
                }
               	result_3 = multiply_scalar_1(&ProductOb, clnt);
               	if (result_3 == NULL) {
                    clnt_perror(clnt, "Call failed");
                } else {
                    printf("Product:[");
                    for (int i = 0; i < result_3->n; i++) {
                        printf("%f ", result_3->elements.elements_val[i]);
                    }
                    printf("]\n");
                }
                break;
            case 0:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");    	
		}
    }while(choice!=0);

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	interface_prog_1 (host);
exit (0);
}
