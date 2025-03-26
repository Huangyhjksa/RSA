
#include "rsa.h"



void RSA_KeyGen(LONG_NUM e, LONG_NUM d, LONG_NUM n, LONG_NUM p, LONG_NUM q) {

    LONG_NUM ONE_NUM = { 1, 1 };
    LONG_NUM w;
    init_random_seed();

    prime_generate(p);
    prime_generate(q);
    mul(p, q, n);

    LONG_NUM p_1, q_1;
    sub(p, ONE_NUM, p_1);
    sub(q, ONE_NUM, q_1);
    mul(p_1, q_1, w);

//    LONG_NUM factor;
//    gcd(w, e, factor);
//    if (number_compare(factor, ONE_NUM) == 0) {
//        printf("true\n");
//    }
//    else {
//        printf("false\n");
//    }

    inverse(e, w, d);

}

void RSA_Encryption(LONG_NUM a, LONG_NUM e, LONG_NUM n, LONG_NUM c) {

//    mod_exp_quaternary(a, e, n, c);
    montgomery_exp(a, e, n, c);
//    crt(a, e, p, q, c);
//    mod_exp_binary(a, e, n, c);
}

void RSA_Decryption(LONG_NUM c, LONG_NUM d, LONG_NUM p, LONG_NUM q, LONG_NUM m) {

//    mod_exp_binary(c, d, n, m);
//    mod_exp_quaternary(c, d, n, m);
    crt(c, d, p, q, m);
//    montgomery_exp(c, d, n, m);

}