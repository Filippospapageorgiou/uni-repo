

#include "idl.h"

float *calculate_average_1_svc(intvector *argp, struct svc_req *rqstp)
{
	static float  result;

	int i,size = argp->n;	
	int sum = 0;
    for (i = 0; i < size; i++) {
    	printf("%d , ",argp->vector.vector_val[i]);
        sum += argp->vector.vector_val[i];
    }
    result = (double) sum / argp->n;

	return &result;
}


intpair *find_max_min_1_svc(intvector *argp, struct svc_req *rqstp)
{
	static intpair  result;

	int min = argp->vector.vector_val[0];
    int max = argp->vector.vector_val[0];
    for (int i = 1; i < argp->n; i++) {
        if (argp->vector.vector_val[i] < min) {
            min = argp->vector.vector_val[i];
        }
        if (argp->vector.vector_val[i] > max) {
            max = argp->vector.vector_val[i];
        }
    }
    result.min = min;
    result.max = max;

	return &result;
}


floatvector *multiply_scalar_1_svc(product *argp, struct svc_req *rqstp) {
    static floatvector result;
    static float *previous_allocation = NULL;

    if (previous_allocation) {
        free(previous_allocation);  
        previous_allocation = NULL;
    }

    int n = argp->vector.n;
    result.elements.elements_len = n;
    result.elements.elements_val = (float*) malloc(n * sizeof(float));
    previous_allocation = result.elements.elements_val;  

    if (result.elements.elements_val == NULL) {
        fprintf(stderr, "Memory allocation failed for multiply_scalar operation.\n");
        return NULL;  
    }

    for (int i = 0; i < n; i++) {
        result.elements.elements_val[i] = argp->a * argp->vector.vector.vector_val[i];
    }
    result.n=n;
    return &result;
}
