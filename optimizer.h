//
// Created by 24208 on 2023/10/23.
//

#include "basic_calculation.h"

#ifndef RSA2_COMBINATORICS_CALCULATION_H
#define RSA2_COMBINATORICS_CALCULATION_H

int extend_binary_gcd(LONG_NUM a, LONG_NUM b, LONG_NUM factor);
int extend_binary_inverse(LONG_NUM a, LONG_NUM n, LONG_NUM inverse_element);

void crt(LONG_NUM a, LONG_NUM b, LONG_NUM p, LONG_NUM q, LONG_NUM rem);
void montgomery_exp(LONG_NUM M, LONG_NUM e, LONG_NUM n, LONG_NUM x);

void mon_pro(LONG_NUM hat_a, LONG_NUM hat_b, LONG_NUM n, LONG_NUM prime_n, LONG_NUM r, LONG_NUM result);
void mon_pro_sos(LONG_NUM hat_a, LONG_NUM hat_b, LONG_NUM n, const uint32_t prime_n, LONG_NUM r, LONG_NUM result);
void mon_pro_cios(LONG_NUM hat_a, LONG_NUM hat_b, LONG_NUM n, const uint32_t prime_n, LONG_NUM result);
void mon_pro_ifios(LONG_NUM hat_a, LONG_NUM hat_b, LONG_NUM n, const uint32_t prime_n, LONG_NUM r, LONG_NUM result);


void pre_montgomery(LONG_NUM M, LONG_NUM n, LONG_NUM prime_n, LONG_NUM r, LONG_NUM hat_x, LONG_NUM hat_M);
void pre_montgomery_exp(LONG_NUM e, LONG_NUM n, LONG_NUM prime_n, LONG_NUM hat_x, LONG_NUM hat_M, LONG_NUM x);


#endif //RSA2_COMBINATORICS_CALCULATION_H
