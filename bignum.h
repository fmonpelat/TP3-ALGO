//
//  bignum.h
//  Tp3
//


#ifndef __Tp3__bignum__
#define __Tp3__bignum__

#include <stdio.h>
#include "simplecalc.h"


typedef enum {OVERFLOWW,ISOK} result_state_t;
typedef enum {POSITIVE,NEGATIVE} sign_t;
typedef enum {OK, ERROR, NOMEM, _EOF } operation_status_t;
typedef unsigned short ushort;


typedef struct bignum{
    unsigned short *digits;
    size_t q_digits;
    sign_t sign ;
} bignum_t;

typedef struct operation{
    bignum_t *op1, *op2;
    opt_t op;
    short *rst;
    size_t q_rst;
    sign_t sign_rst;
    result_state_t st;
} operation_t;

typedef struct operation_vector{
    
    operation_t **operaciones;
    size_t oper_size;
    
} operation_vector_t;


operation_status_t inicializarStructOperation(operation_vector_t * );
operation_status_t AddOperation(operation_vector_t *oper);
operation_status_t cargarStructNumeros(operation_t **,size_t *,size_t *,char *,char *, opt_t *);
void free_operation_t(operation_t ** ,size_t);

short * resta_digito_a_digito(ushort *, ushort *,size_t ,size_t , size_t*);
short * suma_digito_a_digito(ushort * ,ushort * , size_t , size_t ,size_t *);
short * multiplico(ushort * , ushort *, size_t , size_t, size_t *);
void resta(operation_vector_t *, size_t *);
void suma(operation_vector_t *, size_t *);
void multiplicar(operation_vector_t *, size_t *);
ushort findCarry (ushort );

/*bignum_t* add_bignum( const bignum_t * , const bignum_t * ) ;
bignum_t* substract_bignum( const bignum_t * , const bignum_t * ) ;
bignum_t* multiply_bignum( const bignum_t * , const bignum_t * ) ;
*/


#endif /* defined(__Tp3__bignum__) */
