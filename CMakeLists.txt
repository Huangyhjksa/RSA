cmake_minimum_required(VERSION 3.26)
project(RSA2 C)

set(CMAKE_C_STANDARD 11)

add_executable(RSA2 main.c
        basic_calculation.c
        basic_calculation.h
        longprime_generate.c
        longprime_generate.h
        optimizer.c
        optimizer.h
        benchmark.c
        benchmark.h
        rsa.c
        rsa.h)
