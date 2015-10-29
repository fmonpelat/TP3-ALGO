//
//  bignum.h
//  Tp3
//


#ifndef __Tp3__bignum__
#define __Tp3__bignum__

#include <stdio.h>

typedef enum {OVERFLOW,OK} result_state_t;

typedef enum {POSITIVE,NEGATIVE} sign_t;

typedef enum {SUMA,RESTA,MULT,NOOPERATION} opt_t;

typedef struct bignum{
    unsigned short *digits;
    sign_t sign ;
} bignum_t;

typedef struct operation{
    bignum_t *op1, *op2;
    opt_t op;
    short *rst;
    result_state_t st;
} operation_t;

#endif /* defined(__Tp3__bignum__) */
