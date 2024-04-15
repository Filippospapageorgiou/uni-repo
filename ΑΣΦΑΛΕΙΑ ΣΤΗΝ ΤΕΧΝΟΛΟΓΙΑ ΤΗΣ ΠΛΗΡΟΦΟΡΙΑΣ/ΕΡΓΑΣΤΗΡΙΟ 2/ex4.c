#include <stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a) {
    char *number_str = BN_bn2dec(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int main() {
    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *N = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *s = BN_new();
    BIGNUM *m_decrypted = BN_new();
    BIGNUM *m_original = BN_new();
    BIGNUM *tampered_s = BN_new();

    // Case 1
    printf("Case Α:\n");
    BN_hex2bn(&N, "AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115");
    BN_hex2bn(&e, "010001"); //65537 to dec
    BN_hex2bn(&s, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F");
    BN_mod_exp(m_decrypted, s, e, N, ctx);
    BN_hex2bn(&m_original, "4c61756e63682061206d697373696c652e"); // "Launch a missile."
    printBN("Encrypted msg: ", m_decrypted);
    printBN("Original msg: ", m_original);

    if (BN_cmp(m_decrypted, m_original) == 0)
        printf("sig is correct.\n");
    else
        printf("sig is not correct.\n");

    printf("\nCase A  Forged Signature\n");
    BN_hex2bn(&tampered_s, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6803F");
    BN_mod_exp(m_decrypted,tampered_s, e, N, ctx);
    printBN("Encrypted msg: ", m_decrypted);
    if (BN_cmp(m_decrypted, m_original) == 0)
        printf("sig is correct.\n");
    else
        printf("sig is not correct.\n");

    printf("\nCase Β:\n");
    BN_hex2bn(&N, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
    BN_hex2bn(&e, "010001");
    BN_hex2bn(&s, "DB3F7CDB93483FC1E70E4EACA650E3C6505A3E5F49EA6EDF3E95E9A7C6C7A320");
    BN_mod_exp(m_decrypted, s, e, N, ctx);
    BN_hex2bn(&m_original, "506c65617365207472616e73666572206d652024323030302e416c6963652e"); // "Please transfer me $2000.Alice."
    printBN("Encrypted msg: ", m_decrypted);

    printBN("Original msg: ", m_original);
    if (BN_cmp(m_decrypted, m_original) == 0)
        printf("sig is correct.\n");
    else
        printf("sig is not correct.\n");

    BN_free(N);
    BN_free(e);
    BN_free(s);
    BN_free(m_decrypted);
    BN_free(m_original);
    BN_CTX_free(ctx);

    return 0;
}