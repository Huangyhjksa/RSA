#ifndef _WLC_BENCH_H_
#define _WLC_BENCH_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*============================================================================*/
/* Macro definitions                                                          */
/*============================================================================*/

/*============================================================================*/
/* Time Bench                                                                 */
/*============================================================================*/

#define NSPERS 1000000000

#ifdef __linux__



#elif defined(_WIN32) || defined(_WIN64)

#include <windows.h>





#else


#endif



/**
 * Runs a new benchmark.
 * Bench the time of FUNCTION
 * @param[in] LABEL			- the label for this benchmark.
 * @param[in] BENCHS         - Number of times each benchmark is ran.
 */
#define TIME_BENCH_START(_LABEL, _BENCHS)   \
    {                                       \
        uint64_t time_t[_BENCHS];           \
        int _wlc_benchs = _BENCHS;          \
        int _wlc_retrys;                    \
        printf("TIME_BENCH: " _LABEL ""); \
        for (int _b = 0; _b < _wlc_benchs; _b++) {


/**
 * Measures the time of one execution and adds it to the benchmark total.
 *
 * @param[in] FUNCTION		- the function executed.
 */
#define TIME_BENCH_ITEM(_FUNCTION, _ROUNDS)                 \
    _wlc_retrys = _ROUNDS;                                  \
    _FUNCTION;                                              \
    time_bench_before();                                    \
    for (int _r = 0; _r < _wlc_retrys; _r++) { _FUNCTION; } \
    time_bench_after(time_t, _b);


/**
 * Prints the average timing of each execution in the chosen metric.
 */
#define TIME_BENCH_FINAL()                                \
    }                                                     \
    print_time_results(time_t, _wlc_benchs, _wlc_retrys); \
    }


/**
 * Simplified print
 * Prints the average timing with simplified approach.
 */
#define TIME_BENCH_FINAL_S()                                \
    }                                                     \
    print_time_results_simplified(time_t, _wlc_benchs, _wlc_retrys); \
    }


/**
 * Detailed print
 * Prints the average timing of each execution.
 */
#define TIME_BENCH_FINAL_D()                                 \
    }                                                             \
    print_time_results_details(time_t, _wlc_benchs, _wlc_retrys); \
    }


/*============================================================================*/
/* CPU cycle Bench                                                            */
/*============================================================================*/

/**
 * Runs a new benchmark.
 * Bench the cpu-cycles of FUNCTION
 * @param[in] LABEL			- the label for this benchmark.
 * @param[in] BENCHS         - Number of times each benchmark is ran.
 */
#define CYCLE_BENCH_START(_LABEL, _BENCHS)   \
    {                                        \
        uint64_t cycle_t[_BENCHS];           \
        int _wlc_benchs = _BENCHS;           \
        int _wlc_retrys;                     \
        printf("CYCLE_BENCH: " _LABEL " "); \
        for (int _b = 0; _b < _BENCHS; _b++) {


/**
 * Measures the time of FUNCTION.
 *
 * @param[in] FUNCTION		- the function executed.
 */
#define CYCLE_BENCH_ITEM(_FUNCTION, _ROUNDS)                \
    _wlc_retrys = _ROUNDS;                                  \
    _FUNCTION;                                              \
    cycle_bench_before();                                   \
    for (int _r = 0; _r < _wlc_retrys; _r++) { _FUNCTION; } \
    cycle_bench_after(cycle_t, _b);


/**
 * Prints the average and median cpu-cycles.
 */
#define CYCLE_BENCH_FINAL()                                 \
    }                                                       \
    print_cycle_results(cycle_t, _wlc_benchs, _wlc_retrys); \
    }


/**
 * Prints the average cpu-cycles in the simplified approach.
 */
#define CYCLE_BENCH_FINAL_S()                                 \
    }                                                       \
    print_cycle_results_simplified(cycle_t, _wlc_benchs, _wlc_retrys); \
    }

/**
 * Prints the cycles of each execution.
 */
#define CYCLE_BENCH_FINAL_D()                                  \
    }                                                               \
    print_cycle_results_details(cycle_t, _wlc_benchs, _wlc_retrys); \
    }


/*============================================================================*/
/* Symmetric Cipher Bench                                                         */
/*============================================================================*/

/**
 * BITS_PER_SECOND
 * Runs a new benchmark.
 * bench the throughput of symmetric ciphers with (K/M/G)bps
 *
 * @param[in] LABEL			- the label for this benchmark.
 * @param[in] BENCHS         - Number of times each benchmark is ran.
 */
#define BPS_BENCH_START(_LABEL, _BENCHS)                 \
    {                                                    \
        uint64_t time_t[_BENCHS];                        \
        int _wlc_benchs = _BENCHS;                       \
        int _wlc_retrys;                                 \
        printf("BLOCK_CIPHER_THROUGHPUT: " _LABEL "\n"); \
        for (int _b = 0; _b < _wlc_benchs; _b++) {


/**
 * Measures the throughput of of FUNCTION.
 *
 * @param[in] FUNCTION		- the function executed.
 */
#define BPS_BENCH_ITEM(_FUNCTION, _ROUNDS)                  \
    _wlc_retrys = _ROUNDS;                                  \
    _FUNCTION;                                              \
    time_bench_before();                                    \
    for (int _r = 0; _r < _wlc_retrys; _r++) { _FUNCTION; } \
    time_bench_after(time_t, _b);


/**
 * Prints the throughput of FUNCTION  with (K/M/G)bps
 * @param[in] DATASIZE             -bit length of data input to hash functions or block-size of block ciphers
 */
#define BPS_BENCH_FINAL(_DATASIZE)                               \
    }                                                            \
    print_sc_bps(time_t, _wlc_benchs, _wlc_retrys, (_DATASIZE)); \
    }


/**
 * CYCLES_PER_BYTE
 * Runs a new benchmark.
 * bench the throughput of symmetric ciphers with cycles/byte
 *
 * @param[in] LABEL			- the label for this benchmark.
 * @param[in] BENCHS         - Number of times each benchmark is ran.
 */
#define CPB_BENCH_START(_LABEL, _BENCHS)                      \
    {                                                         \
        uint64_t cycle_t[_BENCHS];                            \
        int _wlc_benchs = _BENCHS;                            \
        int _wlc_retrys;                                      \
        printf("BLOCK_CIPHER_CYCLES_PER_BYTE: " _LABEL "\n"); \
        for (int _b = 0; _b < _wlc_benchs; _b++) {


/**
 * Measures the throughput of FUNCTION.
 *
 * @param[in] FUNCTION		- the function executed.
 */
#define CPB_BENCH_ITEM(_FUNCTION, _ROUNDS)                  \
    _wlc_retrys = _ROUNDS;                                  \
    _FUNCTION;                                              \
    cycle_bench_before();                                   \
    for (int _r = 0; _r < _wlc_retrys; _r++) { _FUNCTION; } \
    cycle_bench_after(cycle_t, _b);


/**
 * Prints the throughput of each execution with cycles/byte.
 *
 * @param[in] DATASIZE             -bit length of data input to hash functions or block-size of block ciphers
 */
#define CPB_BENCH_FINAL(_DATASIZE)                                \
    }                                                             \
    print_sc_cpb(cycle_t, _wlc_benchs, _wlc_retrys, (_DATASIZE)); \
    }


/*============================================================================*/
/* Function definitions                                                       */
/*============================================================================*/

#ifdef __cplusplus
extern "C" { /* start of __cplusplus */
#endif

typedef struct timespec time_s;

/**
 * Measures the time before a benchmark is executed.
 */
void time_bench_before(void);

/**
 * Measures the time after a benchmark.
 */
void time_bench_after(uint64_t* t, int i);


/**
 * Prints the last benchmark.
 */
void print_time_results(uint64_t* t, int benches, int rounds);

/**
 * Prints the last benchmark in the simplified approach.
 * Only prints the average time.
 */
void print_time_results_simplified(uint64_t* t, int benches, int rounds);

/**
 * Prints every execution of  last benchmark .
 */
void print_time_results_details(const double *t, int benches, int rounds);


/*============================================================================*/
/* CPU cycle Bench                                                            */
/*============================================================================*/

#ifdef USE_RDPMC /* Needs echo 2 > /sys/devices/cpu/rdpmc */

static inline uint64_t cpucycles(void) {
        const uint32_t ecx = (1U << 30) + 1;
        uint64_t result;

        __asm__ volatile("rdpmc; shlq $32,%%rdx; orq %%rdx,%%rax" : "=a"(result) : "c"(ecx) : "rdx");

        return result;
    }

#else

static inline uint64_t cpucycles(void) {
    uint64_t result;

    __asm__ volatile("rdtsc; shlq $32,%%rdx; orq %%rdx,%%rax" : "=a"(result) : : "%rdx");

    return result;
}

#endif

/**
 * Measures the cpucycles before a benchmark is executed.
 */
void cycle_bench_before(void);

/**
 * Measures the cpucycles after a benchmark.
 */
void cycle_bench_after(uint64_t* t, int i);

/**
 * Prints the last benchmark.
 */
void print_cycle_results(uint64_t* t, size_t benches, int rounds);

/**
 * Prints the last benchmark in the simplified approach.
 * Only prints the average cycles.
 */
void print_cycle_results_simplified(uint64_t* t, size_t benches, int rounds);

/**
 * Prints every execution of  last benchmark .
 */
void print_cycle_results_details(const uint64_t* t, size_t benches, int rounds);


/*============================================================================*/
/* Symmetric Cipher Bench                                                         */
/*============================================================================*/

/**
 * Prints the last benchmark with bps.
 */
void print_sc_bps(const uint64_t* t, int benches, int rounds, int block_size);

/**
 * Prints the last benchmark with cycles/byte.
 */
void print_sc_cpb(const uint64_t* t, int benches, int rounds, int block_size);

#ifdef __cplusplus
} /* end of __cplusplus */
#endif

#endif /* !_WLC_BENCH_H_ */