#include <stdio.h>
#include <openssl/bn.h>
//21390174 FILIPPOS PAPAGEORGIOU
void printBN(char* msg, BIGNUM* a) {
    char* number_str = BN_bn2hex(a);
    printf("%s%s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int main() {
    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *N = BN_new();
    BIGNUM *phi = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *p_1 = BN_new();
    BIGNUM *q_1 = BN_new();
    BIGNUM *one = BN_new();

    //Ftiaxno  p, q, and e
    BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
    BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
    BN_hex2bn(&e, "0D88C3");

    // Ypologizo N = p * q
    BN_mul(N, p, q, ctx);

    // Ypologizo F(n) = (p-1) * (q-1)
    BN_hex2bn(&one, "1");
    BN_sub(p_1, p, one);
    BN_sub(q_1, q, one);
    BN_mul(phi, p_1, q_1, ctx);

    // Ypologizo d opu to d * e mod phi = 1
    BN_mod_inverse(d, e, phi, ctx);

     // Print
    printBN("N = ", N);
    printBN("F(N) = ", phi);
    printBN("d = ", d);
    
    BN_free(p);
    BN_free(q);
    BN_free(e);
    BN_free(N);
    BN_free(phi);
    BN_free(d);
    BN_free(p_1);
    BN_free(q_1);
    BN_free(one);
    BN_CTX_free(ctx);

    return 0;
}