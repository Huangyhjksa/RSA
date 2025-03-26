//
// Created by 24208 on 2023/10/23.
//

#include "optimizer.h"


void montgomery_exp(LONG_NUM M, LONG_NUM e, LONG_NUM n, LONG_NUM x) {

    LONG_NUM ONE_NUM = { 1, 1 };

    LONG_NUM r;
    //    LONG_NUM n_bits_e;
    LONG_NUM temp_n;
    //    memset(n_bits_e, 0, sizeof (n_bits_e));
    memset(r, 0, sizeof(r));
    memset(temp_n, 0, sizeof(temp_n));

    number_copy(temp_n, n);

    //    r = 2^{sw}
    int n_bits = get_bits(temp_n);
    int n_words = (n_bits + 31) / 32;
    //    int remain = n_bits - (n_words - 1) * 32;
    r[0] = n_words + 1;
    r[n_words + 1] = (uint32_t)(1U);

    //    printf("\nr:\n");
    //    display_number(r);
    //    mod_exp(TWO_NUM, n_bits_e, temp_n, r);
    //    LONG_NUM factor;
    //    gcd(r, temp_n, factor);
    //    if (number_compare(factor, ONE_NUM) == 0) {
    //        printf("\ntrue\n");
    //    } else {
    //        printf("\nfalse\n");
    //    }

    //        extend_binary_inverse(r, temp_n, inverse_r);
    //    inverse(r, temp_n, inverse_r);
    //
    //    DOUBLE_LONG_NUM prod_r, prod_r_1;
    //    LONG_NUM rem_n;
    //    memset(prod_r, 0, sizeof(prod_r));
    //    memset(prod_r_1, 0, sizeof(prod_r_1));
    //
    //    mul(r, inverse_r, prod_r);
    //    sub(prod_r, ONE_NUM, prod_r_1);
    //    division_v2(prod_r_1, temp_n, prime_n, rem_n);
    //    printf("\n===============================\n");
    //    display_number(prod_r_1);
    //    display_number(temp_n);
    //    display_number(prime_n);
    //    printf("\n===============================\n");

    uint32_t prime_n = 0;
    prime_n = n[1];
    prime_n += ((n[1] + 2) & 4) << 1;

    for (int i = WORD_BITS; i >= 8; i /= 2) {
        prime_n *= (2 - (n[1] * prime_n));
    }
    prime_n = ~(prime_n) + 1;


    LONG_NUM hat_M, hat_x;
    memset(hat_M, 0, sizeof(hat_M));
    memset(hat_x, 0, sizeof(hat_x));

    //    LONG_NUM temp_M;
    //    memset(temp_M, 0, sizeof(temp_M));
    //    number_copy(temp_M, M);

    mod_mul(M, r, temp_n, hat_M);
    mod_mul(ONE_NUM, r, temp_n, hat_x);

    LONG_NUM temp_x;
    memset(temp_x, 0, sizeof(temp_x));

    uint32_t* eptr, * meptr;
    eptr = e + 1;
    meptr = e + e[0];

    char binary_e[33];
    int e_length = 0;
    //   to do
    //   Converting exponential e to binary expanded form, and store it in array binary_e
    while (eptr <= meptr) {

        memset(binary_e, 0, sizeof(binary_e));
        _ultoa(*meptr, binary_e, 2);

        e_length = (int)strlen(binary_e);
        for (int j = 32; j > 0; j--) {
            if (meptr < e + e[0] || j <= e_length) {
                mon_pro_cios(hat_x, hat_x, temp_n, prime_n, temp_x);
//                mon_pro_ifios(hat_x, hat_x, temp_n, prime_n, temp_x);
//                mon_pro_sos(hat_x, hat_x, temp_n, prime_n, temp_x);
//                mon_pro(hat_x, hat_x, temp_n, prime_n, r, temp_x);
                number_copy(hat_x, temp_x);
            }
            if (j <= e_length) {
                if (binary_e[e_length - j] == '1') {
//                    mon_pro_ifios(hat_M, hat_x, temp_n, prime_n, temp_x);
//                    mon_pro_sos(hat_M, hat_x, temp_n, prime_n, temp_x);
                    mon_pro_cios(hat_M, hat_x, temp_n, prime_n, temp_x);
                    number_copy(hat_x, temp_x);
                }
            }
        }
        meptr--;
    }
    //    for (int i = n_bits - 1; i >= 0; --i) {
    //
    //        mon_pro(hat_x, hat_x, n, prime_n, r, temp_x);
    //        number_copy(hat_x, temp_x);
    //
    //        if (binary_e[i] == 1) {
    //            mon_pro(hat_M, hat_x, n, prime_n, r, temp_x);
    //            number_copy(hat_x, temp_x);
    //        }
    //
    //    }
//    mon_pro_ifios(hat_x, ONE_NUM, temp_n, prime_n, temp_x);
//    mon_pro_sos(hat_x, ONE_NUM, temp_n, prime_n, temp_x);
    mon_pro_cios(hat_x, ONE_NUM, temp_n, prime_n, temp_x);
    number_copy(x, temp_x);

    while ((x[0] > 0) && x[x[0]] == 0) {
        x[0] = x[0] - 1;
    }

}


void mon_pro(LONG_NUM hat_a, LONG_NUM hat_b, LONG_NUM n, LONG_NUM prime_n, LONG_NUM r, LONG_NUM result) {

    LONG_NUM temp_m, temp_u;
    LONG_NUM temp2, temp3, temp4;
    DOUBLE_LONG_NUM temp_t, temp1;

    memset(temp_t, 0, sizeof(temp_t));
    memset(temp_m, 0, sizeof(temp_m));
    //    memset(temp_u0, 0, sizeof (temp_u0));
    //    memset(temp_u1, 0, sizeof (temp_u1));

    //    t = \hat{a} * \hat{b}
    mul(hat_a, hat_b, temp_t);

    //    m = t * n^{\prime} mod r
    mod_n(temp_t, r, temp1);
    mod_mul(temp1, prime_n, r, temp_m);

    //    u = (t + m * n) / r
    mul(temp_m, n, temp1);
    //    division(temp1, r, temp_u0, temp3);
    add(temp_t, temp1, temp2);
    division_v2(temp2, r, temp_u, temp3);
    //    division_v2(temp_t, r, temp_u1, temp3);
    //    add(temp_u0, temp_u1, temp_u);

    if (number_compare(temp_u, n) >= 0) {
        sub(temp_u, n, temp4);
        number_copy(result, temp4);
    }
    else {
        number_copy(result, temp_u);
    }

    while ((result[0] > 0) && (result[result[0]] == 0)) {
        result[0] = result[0] - 1;
    }

}


void mon_pro_sos(LONG_NUM hat_a, LONG_NUM hat_b, LONG_NUM n, const uint32_t prime_n, LONG_NUM r, LONG_NUM result) {

    DOUBLE_LONG_NUM temp_t, temp_u;
    memset(temp_t, 0, sizeof(temp_t));
    memset(temp_u, 0, sizeof(temp_u));

    uint32_t* maptr, * mbptr;
    uint32_t* tptr, * midtptr, * endtptr;
    uint32_t* acir, * bcir, * tcir, * ncir;
    uint32_t hatb_words = 0;
    uint64_t carry = 0;

    maptr = hat_a + hat_a[0];
    mbptr = hat_b + hat_b[0];
    temp_t[0] = *hat_a + *hat_b;

    for (bcir = hat_b + 1, tptr = temp_t + 1; bcir <= mbptr; bcir++, tptr++) {

        carry = 0;
        hatb_words = *bcir;

        for (acir = hat_a + 1, tcir = tptr; acir <= maptr; acir++, tcir++) {
            carry = (uint64_t)*tcir + (uint64_t)hatb_words * (uint64_t)*acir + (uint64_t)((uint32_t)(carry >> WORD_BITS));
            *tcir = (uint32_t)carry;
        }
        *tcir = (uint32_t)(carry >> WORD_BITS);
    }

    uint32_t m = 0;
    uint32_t s = hat_a[0];
    midtptr = temp_t + s;
    endtptr = temp_t + 2 * s;

    for (tptr = temp_t + 1; tptr <= midtptr; tptr++) {

        carry = 0;
        m = (uint32_t)((*tptr) * (prime_n));

        for (tcir = tptr, ncir = n + 1; tcir < tptr + s; tcir++, ncir++) {
            carry = (uint64_t)*tcir + (uint64_t)m * (uint64_t)*ncir + (uint64_t)(uint32_t)(carry >> WORD_BITS);
            *tcir = (uint32_t)carry;
        }

        for (tcir = tptr + s; tcir <= endtptr; tcir++) {
            carry = (uint64_t)*tcir + (uint64_t)(uint32_t)(carry >> WORD_BITS);
            *tcir = (uint32_t)carry;
        }

    }
    temp_t[2 * s + 1] = (uint32_t)(carry >> WORD_BITS);

    temp_u[0] = s + 1;
    for (int j = 1; j <= s + 1; j++) {
        temp_u[j] = temp_t[j + s];
    }

    if (number_compare(temp_u, n) >= 0) {
        sub(temp_u, n, result);
    }
    else {
        number_copy(result, temp_u);
    }

//    while ((result[0] > 0) && (result[result[0]] == 0)) {
//        result[0] = result[0] - 1;
//    }

}


void mon_pro_cios(LONG_NUM hat_a, LONG_NUM hat_b, LONG_NUM n, const uint32_t prime_n, LONG_NUM result) {

    DOUBLE_LONG_NUM temp_t;
    memset(temp_t, 0, sizeof(temp_t));

    uint32_t* mbptr;
    uint32_t* tptr, * midtptr;
    uint32_t* acir, * bcir, * tcir, * ncir;
    uint64_t carry = 0;

    temp_t[0] = *hat_a + *hat_b;

    uint32_t m = 0;
    uint32_t s = hat_a[0];
    mbptr = hat_b + s;
    tptr = temp_t + 1;
    midtptr = temp_t + s + 1;

    for (bcir = hat_b + 1; bcir <= mbptr; bcir++) {

        carry = 0;

        for (tcir = tptr, acir = hat_a + 1; tcir < tptr + s; tcir++, acir++) {

            carry = (uint64_t)*tcir + (uint64_t)*bcir * (uint64_t)*acir + (uint64_t)((uint32_t)(carry >> WORD_BITS));
            *tcir = (uint32_t)carry;
        }

        carry = (uint64_t)*midtptr + (uint64_t)((uint32_t)(carry >> WORD_BITS));
        *midtptr = (uint32_t)carry;
        *(midtptr + 1) = (uint32_t)(carry >> WORD_BITS);

        m = (*tptr) * (prime_n);
        carry = (uint64_t)*tptr + (uint64_t)m * (uint64_t)*(n + 1);

        for (tcir = tptr + 1, ncir = n + 2; tcir < tptr + s; tcir++, ncir++) {

            carry = (uint64_t)*tcir + (uint64_t)m * (uint64_t)*ncir + (uint64_t)(uint32_t)(carry >> WORD_BITS);
            *(tcir - 1) = (uint32_t)carry;
        }
        carry = (uint64_t)*midtptr + (uint64_t)((uint32_t)(carry >> WORD_BITS));
        *(midtptr - 1) = (uint32_t)carry;
        *midtptr = *(midtptr + 1) + (uint32_t)(carry >> WORD_BITS);

    }

    if (number_compare(temp_t, n) >= 0) {
        sub(temp_t, n, result);
    }
    else {
        number_copy(result, temp_t);
    }

    while ((result[0] > 0) && (result[result[0]] == 0)) {
        result[0] = result[0] - 1;
    }

}

void mon_pro_ifios(LONG_NUM hat_a, LONG_NUM hat_b, LONG_NUM n, const uint32_t prime_n, LONG_NUM r, LONG_NUM result) {

    DOUBLE_LONG_NUM temp_t;
    memset(temp_t, 0, sizeof(temp_t));

    uint32_t* mbptr;
    uint32_t* tptr, * midtptr;
    uint32_t* acir, * bcir, * tcir, * ncir;

    uint64_t carry = 0;
    uint64_t rs0 = 0, rs1 = 0;

    temp_t[0] = *hat_a + *hat_b;

    uint32_t m = 0;
    uint32_t s = hat_a[0];
    mbptr = hat_b + s;
    tptr = temp_t + 1;
    midtptr = temp_t + s + 1;

    for (bcir = hat_b + 1; bcir <= mbptr; bcir++) {

        rs0 = (uint64_t)*tptr + (uint64_t)*(hat_a + 1) + (uint64_t)*bcir;
        m = (uint32_t)rs0 + prime_n;
        rs1 = (uint64_t)(uint32_t)rs0 + (uint64_t)m * (uint64_t)*(n + 1);


        for (tcir = tptr + 1, acir = hat_a + 2, ncir = n + 2; tcir < tptr + s; tcir++, acir++, ncir++) {

            rs0 = (uint64_t)*tcir + (uint64_t)*acir * (uint64_t)*bcir + (uint64_t)(uint32_t)(rs0 >> WORD_BITS);
            rs1 = (uint64_t)(uint32_t)rs0 + (uint64_t)m * (uint64_t)*ncir + (uint64_t)(uint32_t)(rs1 >> WORD_BITS);
            *(tcir - 1) = (uint32_t)rs1;
        }

        carry = (uint64_t)(uint32_t)(rs0 >> WORD_BITS) + (uint64_t)((uint32_t)(rs1 >> WORD_BITS));
        *(midtptr + 1) = *(midtptr + 1) + (uint32_t)(carry >> WORD_BITS);

        carry = (uint64_t)*midtptr + (uint64_t)((uint32_t)carry);
        *(midtptr - 1) = (uint32_t)carry;
        *midtptr = *(midtptr + 1) + (uint32_t)(carry >> WORD_BITS);
        *(midtptr + 1) = 0;

    }

    if (number_compare(temp_t, n) >= 0) {
        sub(temp_t, n, result);
    }
    else {
        number_copy(result, temp_t);
    }

    while ((result[0] > 0) && (result[result[0]] == 0)) {
        result[0] = result[0] - 1;
    }

}

void pre_crt() {

}

void crt(LONG_NUM a, LONG_NUM b, LONG_NUM p, LONG_NUM q, LONG_NUM rem) {

    LONG_NUM ONE_NUM = { 1, 1 };

    LONG_NUM p_1, q_1;

    memset(p_1, 0, sizeof(p_1));
    memset(q_1, 0, sizeof(q_1));


    sub(p, ONE_NUM, p_1);
    sub(q, ONE_NUM, q_1);

    LONG_NUM e1, e2;
    memset(e1, 0, sizeof(e1));
    memset(e2, 0, sizeof(e2));

    //    e_1 = b mod (p - 1)
    //    e_2 = b mod (q - 1)
    mod_n(b, p_1, e1);
    mod_n(b, q_1, e2);

    LONG_NUM x1, x2;
    memset(x1, 0, sizeof(x1));
    memset(x2, 0, sizeof(x2));

    LONG_NUM prime_n, r;
    //    x_1 = a^e1 mod p
    //    x_2 = a^e2 mod q
    montgomery_exp(a, e1, p, x1);
    montgomery_exp(a, e2, q, x2);

    LONG_NUM inverse_p, y, diff_x, prod_y, temp_rem;
    memset(inverse_p, 0, sizeof(inverse_p));
    memset(y, 0, sizeof(y));
    memset(diff_x, 0, sizeof(diff_x));
    memset(prod_y, 0, sizeof(prod_y));
    memset(temp_rem, 0, sizeof(temp_rem));

    //    if (number_compare(x1, x2) >= 0) {
    //        sub(x1, x2, diff_x);
    //    } else {
    //        sub(x2, x1, diff_x);
    //    }

    //    y = (x_2 - x_1) * (p^{-1} mod q) mod q
    sub(x2, x1, diff_x);
    inverse(p, q, inverse_p);

    mod_mul(diff_x, inverse_p, q, y);

    //    x = x_1 + y * p
    mul(y, p, prod_y);
    add(x1, prod_y, temp_rem);

    number_copy(rem, temp_rem);
    while ((rem[0] > 0) && (rem[rem[0]] == 0)) {
        rem[0] = rem[0] - 1;
    }

}

int extend_binary_gcd(LONG_NUM a, LONG_NUM b, LONG_NUM factor) {

    int flag = VALID;
    LONG_NUM N, x;

    memset(N, 0x00, sizeof (N));
    memset(x, 0x00, sizeof (x));

    if (number_compare(a, b) > 0) {
        number_copy(N, a);
        number_copy(x, b);
    } else {
        number_copy(N, b);
        number_copy(x, a);
    }


    LONG_NUM ONE_NUM = {1, 1};

//    if (N[0] == 0) {
//        number_copy(factor, x);
//        return flag;
//    }
//    if (x[0] == 0) {
//        number_copy(factor, N);
//        return flag;
//    }

    LONG_NUM T, q, u, v;
    memset(T, 0x00, sizeof (T));
    memset(q, 0x00, sizeof (T));
    memset(u, 0x00, sizeof (T));
    memset(v, 0x00, sizeof (T));

    flag = division_v2(N, x, q, T);
    number_copy(N, x);
    number_copy(x, T);

    if (x[0] == 0) {
        number_copy(factor, N);
        return flag;
    }

    LONG_NUM f;
    memset(f, 0x00, sizeof (f));
    int k = 0;

//    while (((N[1] & 1U) == 0) && ((x[1] & 1U) == 0)) {
    while ((N[1] % 2 == 0) && (x[1] % 2 == 0)) {

        k++;
        shift_right(N);
        shift_right(x);
    }

//    if ((x[1] & 1U) == 0) {
    if (x[1] % 2 == 0) {

        number_copy(T, x);
        number_copy(x, N);
        number_copy(N, T);
        f[0] = f[1] = 1;
    }

    LONG_NUM Ub, Ua, A, B;
    memset(Ub, 0x00, sizeof (Ub));
    memset(Ua, 0x00, sizeof (Ua));
    memset(A, 0x00, sizeof (A));
    memset(B, 0x00, sizeof (B));

    LONG_NUM v_prime, t_prime;
    memset(v_prime, 0x00, sizeof (v_prime));
    memset(t_prime, 0x00, sizeof (t_prime));

    Ub[0] = Ub[1] = 1;
    number_copy(A, N);
    number_copy(B, x);
    number_copy(v_prime, x);

    int t_neg = 0, ua_neg = 0;

//    if ((N[1] & 1U) == 1) {
    if (N[1] % 2 == 1) {
        memset(Ua, 0x00, sizeof (Ua));
        number_copy(t_prime, x);
        t_neg = 1;

    } else {

        add(x, ONE_NUM, Ua);
        shift_right(Ua);
        number_copy(t_prime, N);
        shift_right(t_prime);
    }

    LONG_NUM temp1, temp2;

    while (t_prime[0] != 0) {

        if (t_neg == 0) {

            number_copy(Ub, Ua);
            number_copy(A, t_prime);
        } else {

            sub(x, Ua, B);
            number_copy(v_prime, t_prime);
        }

        if (number_compare(Ub, B) > 0) {

            ua_neg = 0;
            sub(Ub, B, Ua);
        } else {

            ua_neg = 1;
            sub(B, Ub, Ua);
        }

        if (number_compare(A, v_prime) > 0) {

            t_neg = 0;
            sub(A, v_prime, t_prime);
        } else {
            t_neg = 1;
            sub(v_prime, A, t_prime);
        }

        if (ua_neg == 1) {

            memset(temp1, 0x00, sizeof (temp1));
            sub(x, Ua, temp1);
            number_copy(Ua, temp1);
            ua_neg = 0;
        }

//        while (((t_prime[1] & 1U) == 0) && (t_prime[0] != 0)) {
        while ((t_prime[1] % 2 == 0) && (t_prime[0] != 0)) {

            shift_right(t_prime);
//            if ((Ua[1] & 1U) == 0) {
            if (Ua[1] % 2 == 0) {

                shift_right(Ua);
            } else {

                memset(temp2, 0x00, sizeof (temp2));
                add(Ua, x, temp2);
                number_copy(Ua, temp2);
                shift_right(Ua);
            }
        }

    }

    memset(temp1, 0x00, sizeof (temp1));
    memset(temp2, 0x00, sizeof (temp2));
//        LONG_NUM temp3;
//        memset(temp3, 0x00, sizeof (temp3));

    number_copy(u, Ub);
    mul(x, u, temp1);

//    int u_neg = 0, v_neg = 0;

    if (number_compare(A, temp1) > 0) {

        sub(A, temp1, temp2);
    } else {

//        v_neg = 1;
        sub(temp1, A, temp2);
    }

    division_v2(temp2, x, v, temp1);
    number_copy(factor, A);

    for (int i = 0; i < k; i++) {
        shift_left(factor);
    }

    return flag;

}

int extend_binary_inverse(LONG_NUM a, LONG_NUM n, LONG_NUM inverse_element) {
    int flag = VALID;
    LONG_NUM N, x;

    memset(N, 0x00, sizeof (N));
    memset(x, 0x00, sizeof (x));

    if (number_compare(a, n) > 0) {
        number_copy(N, a);
        number_copy(x, n);
    }
    else {
        number_copy(N, n);
        number_copy(x, a);
    }

//    number_copy(N, n);
//    number_copy(x, a);


    LONG_NUM ONE_NUM = {1, 1};

    LONG_NUM T, q, u, v, d;
    memset(T, 0x00, sizeof (T));
    memset(q, 0x00, sizeof (q));
    memset(u, 0x00, sizeof (u));
    memset(v, 0x00, sizeof (v));
    memset(d, 0x00, sizeof (d));

    flag = division_v2(N, x, q, T);
    number_copy(N, x);
    number_copy(x, T);

    if (x[0] == 0) {
        inverse_element[0] = 0;
        return flag;
    }

    LONG_NUM f;
    memset(f, 0x00, sizeof (f));
    int k = 0;

//    while (((N[1] & 1U) == 0) && ((x[1] & 1U) == 0)) {
    while ((N[1] % 2 == 0) && (x[1] % 2 == 0)) {

        k++;
        shift_right(N);
        shift_right(x);
    }

//    if ((x[1] & 1U) == 0) {
    if (x[1] % 2 == 0) {

        number_copy(T, x);
        number_copy(x, N);
        number_copy(N, T);
        f[0] = f[1] = 1;
    }

    LONG_NUM Ub, Ua, A, B;
    memset(Ub, 0x00, sizeof (Ub));
    memset(Ua, 0x00, sizeof (Ua));
    memset(A, 0x00, sizeof (A));
    memset(B, 0x00, sizeof (B));

    LONG_NUM v_prime, t_prime;
    memset(v_prime, 0x00, sizeof (v_prime));
    memset(t_prime, 0x00, sizeof (t_prime));

    Ub[0] = Ub[1] = 1;
    number_copy(A, N);
    number_copy(B, x);
    number_copy(v_prime, x);

    int t_neg = 0, ua_neg = 0;

//    if ((N[1] & 1U) == 1) {
    if (N[1] % 2 == 1) {
        memset(Ua, 0x00, sizeof (Ua));
        number_copy(t_prime, x);
        t_neg = 1;

    } else {

        add(x, ONE_NUM, Ua);
        shift_right(Ua);
        number_copy(t_prime, N);
        t_neg = 0;
        shift_right(t_prime);
    }

    LONG_NUM temp1, temp2;

    while (t_prime[0] != 0) {

        if (t_neg == 0) {

            number_copy(Ub, Ua);
            number_copy(A, t_prime);
        } else {

            sub(x, Ua, B);
            number_copy(v_prime, t_prime);
        }

        if (number_compare(Ub, B) > 0) {

            ua_neg = 0;
            sub(Ub, B, Ua);
        } else {

            ua_neg = 1;
            sub(B, Ub, Ua);
        }

        if (number_compare(A, v_prime) > 0) {

            t_neg = 0;
            sub(A, v_prime, t_prime);
        } else {

            t_neg = 1;
            sub(v_prime, A, t_prime);
        }

        if (ua_neg == 1) {

            memset(temp1, 0x00, sizeof (temp1));
            sub(x, Ua, temp1);
            number_copy(Ua, temp1);
            ua_neg = 0;
        }

//        while (((t_prime[1] & 1U) == 0) && (t_prime[0] != 0)) {
        while ((t_prime[1] % 2 == 0) && (t_prime[0] != 0)) {

            shift_right(t_prime);
//            if ((Ua[1] & 1U) == 0) {
            if (Ua[1] % 2 == 0) {

                shift_right(Ua);
            } else {

                memset(temp2, 0x00, sizeof (temp2));
                add(Ua, x, temp2);
                number_copy(Ua, temp2);

                shift_right(Ua);
            }
        }

    }

    memset(temp1, 0x00, sizeof (temp1));
    memset(temp2, 0x00, sizeof (temp2));
//        LONG_NUM temp3;
//        memset(temp3, 0x00, sizeof (temp3));


    number_copy(u, Ub);
    mul(N, u, temp1);

    int u_neg = 0, v_neg = 0;

    if (number_compare(A, temp1) > 0) {

        v_neg = 0;
        sub(A, temp1, temp2);
        number_copy(v, temp2);

        memset(temp1, 0x00, sizeof (temp1));
        memset(temp2, 0x00, sizeof (temp2));
        division_v2(v, x, temp1, temp2);
        number_copy(v, temp1);

        number_copy(d, A);
        for (int i = 0; i < k; i++) {
            shift_left(d);
        }

    } else {

        v_neg = 1;
        sub(temp1, A, temp2);
        number_copy(v, temp2);

        memset(temp1, 0x00, sizeof (temp1));
        memset(temp2, 0x00, sizeof (temp2));
        division_v2(v, x, temp1, temp2);
        number_copy(v, temp1);

        number_copy(d, A);
        for (int i = 0; i < k; i++) {
            shift_left(d);
        }

    }

//    division_v2(temp2, N, v, temp1);
//    number_copy(d, A);
//
//    for (int i = 0; i < k; i++) {
//        shift_left(d);
//    }

    if (number_compare(f, ONE_NUM) == 0) {

        number_copy(T, u);
        number_copy(u, v);
        number_copy(v, T);
        u_neg = v_neg;
        v_neg = 0;
    }

    memset(temp1, 0x00, sizeof (temp1));
    memset(temp2, 0x00, sizeof (temp2));


    if (v_neg == 0) {

        mul(v, q, temp1);
//        sub(n, u, temp2);
//        sub(temp2, temp1, inverse_element);
        sub(u, temp1, temp2);
    } else {

        mul(v, q, temp1);
        add(u, temp1, temp2);
    }

    number_copy(inverse_element, temp2);

    return flag;
}

//void pre_montgomery(LONG_NUM M, LONG_NUM n, LONG_NUM prime_n, LONG_NUM r, LONG_NUM hat_x, LONG_NUM hat_M) {
//
//
//    LONG_NUM ONE_NUM = { 1, 1 };
//    LONG_NUM inverse_r, temp_n;
//
//    //    r = 2^{sw}
//    int n_bits = get_bits(n);
//    int n_words = (n_bits + 31) / 32;
//    //    int remain = n_bits - (n_words - 1) * 32;
//    memset(r, 0x00, sizeof (*r));
//    r[0] = n_words + 1;
//    r[n_words + 1] = (uint32_t)(1U);
//    number_copy(temp_n, n);
//    inverse(r, n, inverse_r);
//
//    DOUBLE_LONG_NUM prod_r, prod_r_1;
//    LONG_NUM rem_n;
//    memset(prod_r, 0, sizeof(prod_r));
//    memset(prod_r_1, 0, sizeof(prod_r_1));
//
//    mul(r, inverse_r, prod_r);
//    sub(prod_r, ONE_NUM, prod_r_1);
//    division_v2(prod_r_1, n, prime_n, rem_n);
//
//    mod_mul(M, r, n, hat_M);
//    mod_mul(ONE_NUM, r, n, hat_x);
//}
//
//void pre_montgomery_exp(LONG_NUM e, LONG_NUM n, LONG_NUM prime_n, LONG_NUM hat_x, LONG_NUM hat_M, LONG_NUM x) {
//
//    LONG_NUM ONE_NUM = { 1, 1 };
//
//    LONG_NUM temp_n;
//    memset(temp_n, 0, sizeof(temp_n));
//    number_copy(temp_n, n);
//
//    LONG_NUM temp_x;
//    memset(temp_x, 0, sizeof(temp_x));
//
//    uint32_t* eptr, * meptr;
//    eptr = e + 1;
//    meptr = e + e[0];
//
//    char binary_e[33];
//    int e_length = 0;
//
//    while (eptr <= meptr) {
//
//        memset(binary_e, 0, sizeof(binary_e));
//        _ultoa(*meptr, binary_e, 2);
//
//        e_length = (int)strlen(binary_e);
//        for (int j = 32; j > 0; j--) {
//            if (meptr < e + e[0] || j <= e_length) {
//                mon_pro_cios(hat_x, hat_x, temp_n, prime_n, temp_x);
////                mon_pro_sos(hat_x, hat_x, temp_n, prime_n, r, temp_x);
//                number_copy(hat_x, temp_x);
//            }
//            if (j <= e_length) {
//                if (binary_e[e_length - j] == '1') {
//                    mon_pro_cios(hat_M, hat_x, temp_n, prime_n, temp_x);
////                    mon_pro_sos(hat_M, hat_x, temp_n, prime_n, r, temp_x);
//                    number_copy(hat_x, temp_x);
//                }
//            }
//        }
//        meptr--;
//    }
//
//    mon_pro_cios(hat_x, ONE_NUM, temp_n, prime_n, temp_x);
////    mon_pro_sos(hat_x, ONE_NUM, temp_n, prime_n, r, temp_x);
//    number_copy(x, temp_x);
//
//    while ((x[0] > 0) && x[x[0]] == 0) {
//        x[0] = x[0] - 1;
//    }
//
//}