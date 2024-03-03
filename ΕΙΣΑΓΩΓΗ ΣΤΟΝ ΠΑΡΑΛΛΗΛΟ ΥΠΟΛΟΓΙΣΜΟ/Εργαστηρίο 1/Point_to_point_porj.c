#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

// Συνάρτηση για τη δημιουργία ενός πίνακα τυχαίων ακεραίων αριθμών
int *generateRandomArray(int n) {
    srand(time(NULL));

    int *array = (int *)malloc(n * sizeof(int));

    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        array[i] = rand() % 100 + 1;
    }

    return array;
}

int main(int argc, char *argv[]) {
    int my_rank, root = 0;
    int p, k, num;
    int *pin, pin_loc[100];
    int target, source;
    int tag1 = 50, tag2 = 60, tag3 = 70, tag4 = 80, tag5 = 50;
    int plithos;
    int finmax, max;
    int new_pin[100], new_pin2[100], final_pin[100];
    float finres, res, avg, var, finvar, avg2;
   

    //Αρχικοποιήση του MPI με όλες τις καταλληλές συναρτήσεις για το μεγεθός και rank
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    //Η κύρια διεργασία 0 αρχικοποιεί τα δεδομένα και τα διανέμει σε άλλες διεργασίες
    if (my_rank == 0) {
        printf("Enter the number of elements:\n");
        scanf("%d", &plithos);
        pin = generateRandomArray(plithos);

        // Μοιράζει το μέγεθος του πίνακα
        for (target = 1; target < p; target++)
            MPI_Send(&plithos, 1, MPI_INT, target, tag1, MPI_COMM_WORLD);

        // Διανέμετε τμήματα του πίνακα σε άλλες διεργασίες
        num = plithos / p;
        k = num;
        for (target = 1; target < p; target++) {
            MPI_Send(&pin[k], num, MPI_INT, target, tag2, MPI_COMM_WORLD);
            k += num;
        }

        // Αποθηκεύστε το τοπικό τμήμα του πίνακα στην pin_loc για την κύρια διεργασία
        for (k = 0; k < num; k++)
            pin_loc[k] = pin[k];
    } else {
       // Οι άλλες διεργασίες λαμβάνουν το μέγεθος του πίνακα και το δικό τους τμήμα του πίνακα
        MPI_Recv(&plithos, 1, MPI_INT, root, tag1, MPI_COMM_WORLD, &status);
        num = plithos / p;
        MPI_Recv(&pin_loc[0], num, MPI_INT, root, tag2, MPI_COMM_WORLD, &status);
    }

    // Υπολογισμός της μέγιστης τιμής στο τοπικό τμήμα του πίνακα
    max = 0;
    for (k = 0; k < num; k++) {
        if (max < pin_loc[k]) {
            max = pin_loc[k];
        }
    }

    // Υπολογίστε το άθροισμα των στοιχείων στο τοπικό τμήμα του πίνακα
    res = 0;
    for (k = 0; k < num; k++)
        res += pin_loc[k];

   // Αν δεν είναι η κύρια διεργασία, στείλτε το τοπικό max και το άθροισμα στην κύρια διεργασία
    if (my_rank != 0) {
        MPI_Send(&max, 1, MPI_INT, root, tag3, MPI_COMM_WORLD);
        MPI_Send(&res, 1, MPI_INT, root, tag3, MPI_COMM_WORLD);
    } else {
        // Αν είναι λαμβάνει τα δεδομένα
        finmax = max;
        finres = res;
        for (source = 1; source < p; source++) {
            MPI_Recv(&max, 1, MPI_INT, source, tag3, MPI_COMM_WORLD, &status);
            MPI_Recv(&res, 1, MPI_INT, source, tag3, MPI_COMM_WORLD, &status);
            finres += res;
            if (finmax < max) {
                finmax = max;
            }
        }

        // Υπολογίζει το μεσό όρο και το εμφανίζει μαζί με το max που έχουμε βρει
        avg = finres / plithos;
        printf("\n\n\nA). Final Result MAX: %d\n", finmax);
        printf("\n\n\nB). Final Result AVG: %f\n", avg);
        printf("\n----------------------------VAR---------------------------\n\n\n");
    }

    //Αν είναι η κυρία διεργασία στέλνει τα δεδομένα για το δευτερό μέρος της ασκ
    if (my_rank == 0) {
        for (target = 1; target < p; target++) {
            MPI_Send(&finmax, 1, MPI_INT, target, tag4, MPI_COMM_WORLD);
            MPI_Send(&avg, 1, MPI_FLOAT, target, tag4, MPI_COMM_WORLD);
        }
    } else {
        // Οι υπολοίπες διεργασίες λαμβάνουν τα δεδομένα
        MPI_Recv(&finmax, 1, MPI_INT, root, tag4, MPI_COMM_WORLD, &status);
        MPI_Recv(&avg, 1, MPI_FLOAT, root, tag4, MPI_COMM_WORLD, &status);
    }

    // Υπολογισμός τοπίκης διεργασίας
    var = 0;
    for (k = 0; k < num; k++) {
        new_pin[k] = abs((pin_loc[k] - finmax) * (pin_loc[k] - finmax));
        var += (pin_loc[k] - avg) * (pin_loc[k] - avg);
    }

    // Καθε διεργασία στέλνει τον τοπικό πινακα της και το αθροισμα var στην μητρική
    if (my_rank != 0) {
        MPI_Send(&new_pin, num, MPI_INT, root, tag5, MPI_COMM_WORLD);
        MPI_Send(&var, 1, MPI_FLOAT, root, tag5, MPI_COMM_WORLD);
    } else {
        //λαμβάνει δεδομένα η μητρική διεργασία
        finvar = var;
        //Μαζεμα τον πινακων και εκτυπώση αποτελεσματός
        printf("\n\nD). Final Result Array:\n");
        for (k = 0; k < num; k++) {
            final_pin[k] = new_pin[k];
            printf("%d ", final_pin[k]);
        }
        for (source = 1; source < p; source++) {
            MPI_Recv(&new_pin2, num, MPI_INT, source, tag5, MPI_COMM_WORLD, &status);
            for (k = 0; k < num; k++) {
                final_pin[k] = new_pin2[k];
                printf("%d ", final_pin[k]);
            }
            MPI_Recv(&var, 1, MPI_FLOAT, source, tag5, MPI_COMM_WORLD, &status);
            finvar += var;
        }

        //Υπολογιμσός του τελικου μέσου όρου και ελτυπ´βση αποτελεσματός απ'ο μητρική διεργασία
        avg2 = finvar / plithos;
        printf("\n\nC). Final Result: %f\n\n\n", avg2);
    }

    // Free την μνήμη του πίνακα
    free(pin);

   
    // Finalize MPI
    MPI_Finalize();
    return 0;
}
