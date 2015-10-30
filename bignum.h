//
//  bignum.h
//  Tp3
//


#ifndef __Tp3__bignum__
#define __Tp3__bignum__

#include <stdio.h>


typedef enum {OVERFLOW,ISOK} result_state_t;
typedef enum {POSITIVE,NEGATIVE} sign_t;
typedef enum {SUMA,RESTA,MULT,NOOPERATION} opt_t;
typedef enum {OK, ERROR, NOMEM } operation_status_t;
typedef unsigned short ushort;

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



operation_status_t inicializarStructOperation(operation_t ** oper,size_t size);
operation_status_t rezizeStructOperation(operation_t **oper,size_t size);
operation_status_t cargarStructNumeros(operation_t **oper,size_t size,size_t pos,char *num1,char *num2);
/*bignum_t* add_bignum( const bignum_t * , const bignum_t * ) ;
bignum_t* substract_bignum( const bignum_t * , const bignum_t * ) ;
bignum_t* multiply_bignum( const bignum_t * , const bignum_t * ) ;
*/


#endif /* defined(__Tp3__bignum__) */
