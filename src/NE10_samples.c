/*
 *  Copyright 2011-16 ARM Limited and Contributors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of ARM Limited nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY ARM LIMITED AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL ARM LIMITED AND CONTRIBUTORS BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>

#include "NE10.h"

int           intro_sample_main(void);
int matrix_multiply_sample_main(void);
int     complex_fft_sample_main(void);
int        real_fft_sample_main(void);
int             fir_sample_main(void);

#include <sys/time.h>
#include <time.h>

static void my_test(void){
    printf("==========my_test() begin=========\n");   
    ne10_int32_t i;     
    ne10_float32_t thesrc[15];     
    ne10_float32_t thecst;     
    ne10_float32_t thedst1[15];      
    ne10_float32_t thedst2[15];
    ne10_float32_t thedst3[15];


    for (i=0; i<15; i++)     
    {     
        thesrc[i] = (ne10_float32_t) rand()/RAND_MAX*5.0f;     
    }     
    thecst = (ne10_float32_t) rand()/RAND_MAX*5.0f;  

    struct timespec start, end;
    uint64_t elapsed_us;

    int loops = 5000000;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (i=0;i<loops;i++) {
        ne10_addc_float_c( thedst1 , thesrc, thecst, 15 );     
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    elapsed_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("ne10_addc_float_c() elapsed %lu us\n", elapsed_us);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (i=0;i<loops;i++) {
        ne10_addc_float_neon( thedst2 , thesrc, thecst, 15 );
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    elapsed_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("ne10_addc_float_neon() elapsed %lu us\n", elapsed_us);

/*
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (i=0;i<loops;i++) {
        ne10_addc_float_asm( thedst3 , thesrc, thecst, 15 );
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    elapsed_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("ne10_addc_float_c() elapsed %lu ms\n", elapsed_us / 1000);
*/
    printf("==========my_test() end=========\n");   
}

/*
 * Run all the sample code snippets in series.
 *
 * Note that this will call `ne10_init` multiple times unnecessarily, as each sample is
 * supposed to be an isolated illustration of how to use a certain part of Ne10.
 */
int main(int argc, char **argv)
{
    printf("==== Ne10 Samples ===\n\n");

    printf("# Introduction\n");
    intro_sample_main();
    printf("\n");

    printf("# Matrix Multiply\n");
    matrix_multiply_sample_main();
    printf("\n");

    printf("# Complex-to-Complex FFT\n");
    complex_fft_sample_main();
    printf("\n");

    printf("# Real-to-Complex FFT\n");
    real_fft_sample_main();
    printf("\n");

    printf("# FIR\n");
    fir_sample_main();
    printf("\n");

    my_test();
    return 0;
}
