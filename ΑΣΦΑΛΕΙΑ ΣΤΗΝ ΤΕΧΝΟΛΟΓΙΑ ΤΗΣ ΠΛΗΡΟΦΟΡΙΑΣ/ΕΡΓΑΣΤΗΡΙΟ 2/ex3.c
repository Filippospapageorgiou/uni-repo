#include <stdio.h>
#include <openssl/bn.h>

int main() {
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *N = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *phi = BN_new();
    BIGNUM *msg = BN_new();
    BIGNUM *sig = BN_new();
    char *sig1_str;
    char *sig2_str;

    
    BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
    BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
    BN_hex2bn(&e, "0D88C3");

    BN_mul(N, p, q, ctx);
    
    BIGNUM *p1 = BN_new();
    BIGNUM *q1 = BN_new();
    BN_sub(p1, p, BN_value_one());  // p-1
    BN_sub(q1, q, BN_value_one());  // q-1
    BN_mul(phi, p1, q1, ctx);

    
    BN_mod_inverse(d, e, phi, ctx);

  	//Dilosi hex
    //University of West attica
    BN_hex2bn(&msg, "556e6976657263697479206f66207765737420417474696361");

    
    BN_mod_exp(sig, msg, d, N, ctx);
    sig1_str = BN_bn2hex(sig);
    printf("Signature Original Message: %s\n",sig1_str);
    OPENSSL_free(sig1_str);

    //Allagi minimatos
    BN_hex2bn(&msg, "5556e6976657263697479206f662077657374204174746963611");
    BN_mod_exp(sig, msg, d, N, ctx);
    sig2_str = BN_bn2hex(sig);
    printf("Signature Original Message: %s\n",sig2_str);
    OPENSSL_free(sig2_str);
    

    
 // Cleanup
    BN_free(p);
    BN_free(q);
    BN_free(N);
    BN_free(e);
    BN_free(d);
    BN_free(phi);
    BN_free(p1);
    BN_free(q1);
    BN_free(msg);
    BN_CTX_free(ctx);
    return 0;
}