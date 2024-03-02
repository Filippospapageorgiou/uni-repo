#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv)
{
	int my_rank;
	int size;
	int namelen;
	char proc_name[MPI_MAX_PROCESSOR_NAME];

	/* η συνάρτηση αρχικοποίησης του MPI */
	MPI_Init(&argc, &argv);
	/* επιστροφή της ταυτότητας κάθε διεργασίας */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	/* επιστροφή του συνολικού πλήθους των διεργασιών */
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	/* επιστροφή στην proc_name του ονόματος της μηχανής στην
	οποία τρέχει η διεργασία */
	MPI_Get_processor_name(proc_name, &namelen);
	printf("Hello from process %d of %d on %s\n", my_rank, size, proc_name);
	MPI_Finalize();
}
