/*
//  bignum.h
//  Tp3
*/


#ifndef __Tp3__bignum__
#define __Tp3__bignum__

#include <stdio.h>
#include "simplecalc.h"

#define ACARREO suma/10
#define UNIDAD 	suma%10

typedef enum {OVERFLOWW,ISOK} result_state_t;
typedef enum {OK, ERROR, NOMEM, _EOF,INF} operation_status_t;
typedef enum {POSITIVE,NEGATIVE} sign_t;
typedef unsigned short ushort;
typedef enum{true=0,false=1}bool_t;



typedef struct bignum{
    unsigned short *digits;
    size_t q_digits;
    sign_t sign ;
    sign_t inf;
} bignum_t;

typedef struct operation{
    bignum_t *op1, *op2;
    opt_t op;
    ushort *rst;
    size_t q_rst;
    sign_t sign_rst;
    sign_t inf_rst;
    result_state_t st;
} operation_t;

typedef struct operation_vector{
    
    operation_t **operaciones;
    size_t oper_size;
    
} operation_vector_t;


operation_status_t inicializarStructOperation(operation_vector_t * );
operation_status_t AddOperation(operation_vector_t *oper);
operation_status_t cargarStructNumeros(operation_t **,size_t *,size_t *,char *,char *, opt_t *,size_t,operation_status_t);
void free_operation_t(operation_t ** oper,size_t size,operation_status_t status);

ushort * resta_digito_a_digito(ushort *, ushort *,size_t ,size_t , size_t*);
ushort * suma_digito_a_digito(ushort * ,ushort * , size_t , size_t ,size_t *);
void resta(operation_vector_t *, size_t *);
void suma(operation_vector_t *, size_t *);
ushort findCarry (ushort );
ushort *invertir(ushort *vector, size_t size);


void multiplicar(operation_vector_t *, size_t *);
/*ushort* multiplico(const ushort* , const ushort* ,size_t a_size,size_t b_size,sign_t a_sign,sign_t b_sign,sign_t a_inf,sign_t b_inf,size_t *q_res,sign_t *res_sign,sign_t *res_inf ,size_t precision);*/
ushort * multiplico(ushort * , ushort *, size_t , size_t, size_t *);




#endif /* defined(__Tp3__bignum__) */
