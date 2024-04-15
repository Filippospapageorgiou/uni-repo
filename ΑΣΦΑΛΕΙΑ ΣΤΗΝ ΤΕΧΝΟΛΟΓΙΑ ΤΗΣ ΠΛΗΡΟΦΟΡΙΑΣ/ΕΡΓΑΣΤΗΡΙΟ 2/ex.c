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
    BIGNUM *enc_msg = BN_new();
    BIGNUM *dec_msg = BN_new();
    char *enc_str;
    char *dec_str;

    
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
    BN_hex2bn(&msg, "9D368A5F8F562EB9553F6081B492C3D9527298DA5557B1895E6F7B7C8B01A308");

    /*// Encrypt to minima: enc_msg = msg^e mod N
    BN_mod_exp(enc_msg, msg, e, N, ctx);
    enc_str = BN_bn2hex(enc_msg);
    printf("Encrypted Message: %s\n", enc_str);
    OPENSSL_free(enc_str);*/

    // Decrypt to minima: dec_msg = enc_msg^d mod N
    BN_mod_exp(dec_msg,msg, d, N, ctx);
    dec_str=BN_bn2hex(dec_msg);
    printf("Decrypted Message: %s\n", dec_str);
    OPENSSL_free(dec_str);

    
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
    BN_free(enc_msg);
    BN_free(dec_msg);
    BN_CTX_free(ctx);
    return 0;
}