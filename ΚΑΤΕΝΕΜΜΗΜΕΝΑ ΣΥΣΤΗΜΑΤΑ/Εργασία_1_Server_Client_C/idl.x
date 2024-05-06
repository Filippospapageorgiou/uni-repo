struct intvector {
    int n;                
    int vector<>; 
};

struct intpair {
	int min;
	int max;
};


struct product{
    float a;                      
    intvector vector;    
};

struct floatvector{
	int n; 
	float elements<>;
};


program INTERFACE_PROG{
	version INTERFACE_VERS{
		float calculate_average(intvector) = 1;
        intpair find_max_min(intvector) = 2;
        floatvector multiply_scalar(product) = 3;
	}=1;
}=0x23451111;
