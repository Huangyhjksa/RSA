//
// Created by 24208 on 2024/6/30.
//

#include "longprime_generate.h"
#include "optimizer.h"


void RSA_KeyGen(LONG_NUM e, LONG_NUM d, LONG_NUM n, LONG_NUM p, LONG_NUM q);

void RSA_Encryption(LONG_NUM a, LONG_NUM e, LONG_NUM n, LONG_NUM c);
void RSA_Decryption(LONG_NUM c, LONG_NUM d, LONG_NUM p, LONG_NUM q, LONG_NUM m);
