#include "rsa.h"
#include "benchmark.h"

int main() {

    //    LONG_NUM pp = {32, 0xe4a7cd01, 0xf0c8a5e4, 0x8d8f0117, 0xaba92db3, 0x3ae70cc9, 0xf982c3c4, 0xf16e274e, 0xed7fc0fb,
    //                   0xc55be915, 0x3def5d2b, 0x496c3345, 0x867a26bf, 0x24b6a2d3, 0xa71978b9, 0xac54a3e8, 0xa0e799f8,
    //                   0x9356838c, 0x8ec6d3d9, 0xa68d1fb0, 0xa9c92a20, 0x1a279804, 0xe1f31b32, 0xe90ca40e, 0x1cc6fa3,
    //                   0xc19edfad, 0xdebb1a93, 0xffc0bb54, 0x2839af55, 0x3f29f69c, 0x374c63eb, 0xf60ba4b0, 0xf35c9859
    //    };
    //    LONG_NUM qq = {32, 0xe0d4db01,  0x4bb93712,  0xd370921,  0xae9c2623,  0x3b8f438,  0x6bd5a405,  0x456e87b9,  0x9ded3c73,
    //                  0xf0483c65,  0x33c2bc11,  0xc2ed6714,  0xade9c79c,  0xb7e51023,  0xa95efc7f,  0x5fa376f3,  0xf23bcf48,
    //                  0xb9e12988,  0x3388eb73,  0xc010c854,  0x50444f30,  0x98cb6c11,  0x6075f458,  0x42a596cd,  0x476a2680,
    //                  0x15d5d707,  0xdd185a34,  0xc03416ef,  0xe18ae036,  0xf03a5ad4,  0x5084fa0b,  0x9437639f,  0x9442b47c
    //    };
    //
    //    LONG_NUM tt, ss, uu;
    //    memset(tt, 0, sizeof (tt));
    //    memset(ss, 0, sizeof (0));
    //    mod_exp(THREE_NUM, pp, pp, tt);
    //    display_number(tt);
    //
    //    LONG_NUM aa = {32,  0x42364af1, 0x6f7f757e, 0xcd8dff12, 0xa6e60b6, 0xcedf4457, 0x7e7335ff, 0x6404fecb, 0x2b277ac9,
    //                   0x6924ec81, 0x791c1e60, 0x117be54c, 0x3644400e, 0x8767ae52, 0x81a8878c, 0x29c7d65e, 0xcbf08fcf,
    //                   0xc4292c92, 0xe33a648f, 0x77ccbde3, 0x134203b3, 0x8c70e9df, 0x4cd8fb03, 0xf472044f, 0x692c97a7,
    //                   0x4cbd011a, 0x765f9302, 0x710fbe0a, 0x92f0e7ce, 0xa6fbcf52, 0x5af1a295, 0xcada61eb, 0x670e52f2
    //    };
    //    int aaa = fermat_test(aa);
    //    printf("\n=============  %d  =============\n", aaa);


    //    add(pp, qq, tt);
    //    mul(pp, qq, tt);
    //    display_number(tt);
    //    add(tt, TWO_NUM, uu);
    //    division(uu, pp, qq, ss);
    //    display_number(qq);
    //    printf("\nss:\n");
    //    display_number(ss);


    int benchs = 13, retrys = 11;

    init_random_seed();

    LONG_NUM a, c, m;
    memset(a, 0, sizeof(a));
    memset(c, 0, sizeof(c));
    memset(m, 0, sizeof(m));

    uint8_t str1[STR_SIZE] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    a[0] = NUMBER_LENGTH;
    str_to_num(a, str1);


    LONG_NUM e, n, p, q, d;
    memset(e, 0, sizeof(e));
    memset(n, 0, sizeof(n));
    memset(p, 0, sizeof(p));
    memset(q, 0, sizeof(q));
    memset(d, 0, sizeof(d));

    e[0] = 1, e[1] = 65537;

    prime_generate(p);
    prime_generate(q);

    TIME_BENCH_START("RSA_KeyGen", benchs) {

        TIME_BENCH_ITEM(RSA_KeyGen(e, d, n, p, q), retrys)

    }
    TIME_BENCH_FINAL()


    TIME_BENCH_START("RSA_Enc", benchs) {

                TIME_BENCH_ITEM(RSA_Encryption(a, e, n, c), retrys)

    }
    TIME_BENCH_FINAL()

    TIME_BENCH_START("RSA_Dec", benchs) {

                TIME_BENCH_ITEM(RSA_Decryption(c, d, p, q, m), retrys)

    }
    TIME_BENCH_FINAL()


//    start = clock();
//    mod_exp_binary(c, d, n, m);
//    finish = clock();
//    interval = (double)(finish - start);
//    printf("m:\n");
//    display_number(m);
//    printf("It takes %lf ms for decryption with binary's method\n", interval);
//
//    memset(m, 0x00, sizeof (m));
//    start = clock();
//    mod_exp_quaternary(c, d, n, m);
//    finish = clock();
//    interval = (double)(finish - start);
//    printf("m:\n");
//    display_number(m);
//    printf("It takes %lf ms for decryption with quaternary's method\n", interval);
//
//    start = clock();
//    crt(c, d, p, q, m);
//    finish = clock();
//    interval = (double)(finish - start);
//    printf("m:\n");
//    display_number(m);
//    printf("It takes %lf ms for decryption with crt\n", interval);
//
//    start = clock();
//    montgomery_exp(c, d, n, m);
//    finish = clock();
//    interval = (double)(finish - start);
//    printf("m:\n");
//    display_number(m);
//    printf("It takes %lf ms for decryption with montgomery's method\n", interval);



    char str[STR_SIZE];
    memset(str, 0x00, sizeof (str));
    num_to_str(m, str);
    printf("\nThe plaintext:\n");
    puts(str);

    return 0;
}