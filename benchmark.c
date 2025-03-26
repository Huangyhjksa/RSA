/**
 * Wuhan University Library for Cryptography (WULC) is an ongoing and portable
 * cryptographic toolkit developed by Cryptography and Blockchain Technology
 * Laboratory �� Wuhan University.
 * This file is part of WULC.
 * @copyright Copyright (c) 2018-2023 WULC authors
 *
 * @file wlc_bench.c
 * @brief to descirbe
 *
 * @author PengCong (cpeng@whu.edu.cn)
 * @version 1.2
 * @date 2023-01-10
 *
 * @ingroup {group}
 */

#include "benchmark.h"

#define ANSI 5
#define TIMER ANSI


/*============================================================================*/
/* Time Bench                                                                 */
/*============================================================================*/

#ifdef __linux__

static struct {
    /** Stores the time measured before the execution of the benchmark. */
    time_s before;
    /** Stores the time measured after the execution of the benchmark. */
    time_s after;
} g_bench;


/**
 * compute the time between start and end, using the time_s struct
 *
 * @param end       -the start of the execution
 * @param start     -the end of the execution
 * @return
 */
static time_s time_sub(time_s* end, time_s* start) {
    time_s temp;
    if ((end->tv_nsec - start->tv_nsec) < 0) {
        temp.tv_sec = end->tv_sec - start->tv_sec - 1;
        temp.tv_nsec = NSPERS + end->tv_nsec - start->tv_nsec;
    }
    else {
        temp.tv_sec = end->tv_sec - start->tv_sec;
        temp.tv_nsec = end->tv_nsec - start->tv_nsec;
    }
    return temp;
}


void time_bench_before() { clock_gettime(CLOCK_MONOTONIC, &g_bench.before); }


void time_bench_after(uint64_t* t, int i) {
    clock_gettime(CLOCK_MONOTONIC, &g_bench.after);
    time_s temp = time_sub(&g_bench.after, &g_bench.before);
    t[i] = temp.tv_sec * NSPERS + temp.tv_nsec;
}

#elif defined(_WIN32) || defined(_WIN64)

static struct {
    /** Stores the time measured before the execution of the benchmark. */
    LARGE_INTEGER before;
    /** Stores the time measured after the execution of the benchmark. */
    LARGE_INTEGER after;
} g_bench;

void time_bench_before() { QueryPerformanceCounter(&g_bench.before); }


void time_bench_after(uint64_t* t, int i) {
    QueryPerformanceCounter(&g_bench.after);
    LARGE_INTEGER Frequency;
    QueryPerformanceFrequency(&Frequency);
    int64_t temp = g_bench.after.QuadPart - g_bench.before.QuadPart;
    t[i] = (NSPERS * temp) / Frequency.QuadPart;
}

#else


#endif


static int cmp_uint64(const void* a, const void* b) {
    if (*(uint64_t*)a < *(uint64_t*)b) return -1;
    if (*(uint64_t*)a > *(uint64_t*)b) return 1;
    return 0;
}

static uint64_t median(uint64_t* l, size_t llen) {
    qsort(l, llen, sizeof(uint64_t), cmp_uint64);

    if (llen % 2) return l[llen / 2];
    else
        return (l[llen / 2 - 1] + l[llen / 2]) / 2;
}


static uint64_t average(const uint64_t* t, size_t tlen) {
    size_t i;
    uint64_t acc = 0;

    for (i = 0; i < tlen; i++) acc += t[i];

    return acc / tlen;
}

static double average_f(const double* t, int tlen) {
    double acc = 0;

    for (int i = 0; i < tlen; i++) acc += t[i];

    return acc / tlen;
}


void print_time_results(uint64_t* t, int benches, int rounds) {
    printf("\n");

    if (benches < 2) {
        fprintf(stderr, "\nERROR: Need a least two bench counts!\n");
        return;
    }

    uint64_t aver = average(t, benches);
    uint64_t med = median(t, benches);

    double aver_d = (double)aver / rounds;
    double med_d = (double)med / rounds;

    if (aver_d < 1000) {
        printf("median: %9.2f ns\n", med_d);
        printf("average: %9.2f ns\n", aver_d);
    }
    else if (aver < 1000000) {
        printf("median: %9.2f us\n", med_d / 1000);
        printf("average: %9.2f us\n", aver_d / 1000);
    }
    else if (aver < 1000000000) {
        printf("median: %9.2f ms\n", med_d / 1000000);
        printf("average: %9.2f ms\n", aver_d / 1000000);
    }
    else {
        printf("median: %9.2f s\n", med_d / 1000000000);
        printf("average: %9.2f s\n", aver_d / 1000000000);
    }

    printf("\n");
}


void print_time_results_simplified(uint64_t* t, int benches, int rounds) {

    if (benches < 2) {
        fprintf(stderr, "ERROR: Need a least two bench counts!\n");
        return;
    }

    uint64_t aver = average(t, benches);

    double aver_d = (double)aver / rounds;

    if (aver_d < 1000) {
        printf(" %9.2f ns", aver_d);
    }
    else if (aver < 1000000) {
        printf(" %9.2f us\n", (double)aver_d / 1000);
    }
    else if (aver < 1000000000) {
        printf(" %9.2f ms", (double)aver_d / 1000000);
    }
    else {
        printf(" %9.2f s", (double)aver_d / 1000000000);
    }

    printf("\n");
}

void print_time_results_details(const double *t, int benches, int rounds) {
    printf("\n");

    if (benches < 2) {
        fprintf(stderr, "ERROR: Need a least two bench counts!\n");
        return;
    }

    double aver = average_f(t, benches) / rounds;
    int fac = 1;
    if (aver < 1000) {
        printf("print with ns\n");
        fac = 1;
    }
    else if (aver < 1000000) {
        printf("print with us\n");
        fac = 1000;
    }
    else if (aver < 1000000000) {
        printf("print with ms\n");
        fac = 1000000;
    }
    else {
        printf("print with s\n");
        fac = 1000000000;
    }

    for (int i = 0; i < benches; ++i) { printf("%-8d  %.2f \n", i, (double)t[i] / (rounds * fac)); }
    printf("\n");
}

/*============================================================================*/
/* CPU cycle Bench                                                            */
/*============================================================================*/

static struct {
    /** Stores the time measured before the execution of the benchmark. */
    uint64_t before;
    /** Stores the time measured after the execution of the benchmark. */
    uint64_t after;
} c_bench;


static uint64_t cpucycles_overhead(void) {
    uint64_t t0, t1, overhead = -1LL;
    unsigned int i;

    for (i = 0; i < 100000; i++) {
        t0 = cpucycles();
        __asm__ volatile("");
        t1 = cpucycles();
        if (t1 - t0 < overhead) overhead = t1 - t0;
    }

    return overhead;
}


void cycle_bench_before() { c_bench.before = cpucycles(); }


void cycle_bench_after(uint64_t* t, int i) {
    c_bench.after = cpucycles();

    static uint64_t overhead = -1;

    if (overhead == (uint64_t)-1) overhead = cpucycles_overhead();

    t[i] = c_bench.after - c_bench.before - overhead;
}


void print_cycle_results(uint64_t* t, size_t benches, int rounds) {
    printf("\n");
    if (benches < 2) {
        fprintf(stderr, "ERROR: Need a least two cycle counts!\n");
        return;
    }

    uint64_t aver = average(t, benches) / rounds;
    uint64_t med = median(t, benches) / rounds;

#ifdef CSV_PRINT
    printf("%lu, %lu,", med, aver);
#else
    printf("median: %lu cycles\n", med);
    printf("average: %lu cycles\n", aver);
    printf("\n");
#endif
}

void print_cycle_results_simplified(uint64_t* t, size_t benches, int rounds) {

    if (benches < 2) {
        fprintf(stderr, "ERROR: Need a least two cycle counts!\n");
        return;
    }

    uint64_t aver = average(t, benches) / rounds;
    uint64_t med = median(t, benches) / rounds;

#ifdef CSV_PRINT
    printf("%lu, %lu,", med, aver);
#else
    printf(": %lu cycles\n", aver);
#endif
}


void print_cycle_results_details(const uint64_t* t, size_t benches, int rounds) {
    printf("\n");
    for (int i = 0; i < benches; ++i) { printf("%-8d  %lu \n", i, t[i] / rounds); }
    printf("\n");
}


/*============================================================================*/
/* Block Cipher Bench                                                         */
/*============================================================================*/

void print_sc_bps(const uint64_t* t, int benches, int rounds, int block_size) {

    if (benches < 2) {
        fprintf(stderr, "ERROR: Need a least two bench counts!\n");
        return;
    }

    uint64_t acc = 0;

    for (int i = 0; i < benches; i++) acc += t[i];

    uint64_t bits = benches * rounds * block_size;

    double kbits = (double)bits / (1 << 10);

    double mbits = (double)bits / (1 << 20);

    double gbits = (double)bits / (1 << 30);

    double secend = (double)acc / NSPERS;

    double throughpt_bits_s = (double)bits / secend;// bits/s

    double throughpt_kbits_s = (double)kbits / secend;// kbits/s

    double throughpt_mbits_s = (double)mbits / secend;// mbits/s

    double throughpt_gbits_s = (double)gbits / secend;// gbits/s

    //printf("execute time: %f s\n", secend);
    if (throughpt_bits_s < 1000) printf("throughpt: %f bps\n", throughpt_bits_s);
    else if (throughpt_kbits_s < 1000)
        printf("throughpt: %f Kbps\n", throughpt_kbits_s);
    else if (throughpt_mbits_s < 1000)
        printf("throughpt: %f Mbps\n", throughpt_mbits_s);
    else
        printf("throughpt: %f Gbps\n", throughpt_gbits_s);

    printf("\n");
}


void print_sc_cpb(const uint64_t* t, int benches, int rounds, int block_size) {

    if (benches < 2) {
        fprintf(stderr, "ERROR: Need a least two bench counts!\n");
        return;
    }

    uint64_t acc = 0;

    for (int i = 0; i < benches; i++) acc += t[i];

    double bytes = (double)(benches * rounds * block_size) / 8;

    double cpb = (double)acc / bytes;

    printf("throughpt: %f bps\n", cpb);


    printf("\n");
}