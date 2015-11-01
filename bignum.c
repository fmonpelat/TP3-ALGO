//
//  bignum.c
//  Tp3
//


#include "bignum.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 typedef struct bignum{
 
 unsigned short *digits;
 sign_t sign ;
 
 } bignum_t;
 
 typedef struct operation{
 
 bignum_t *op1, *op2; OK
 opt_t op;
 short *rst; OK
 result_state_t st;
 
 } operation_t;
*/

operation_status_t inicializarStructOperation(operation_t ** oper ){
    

    /* pido memoria para el array de operaciones */
    if( !(*oper=(operation_t *)malloc( sizeof(operation_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    /* pido memoria para cada bignum_t */
    if( !((*oper)->op1=(bignum_t *)malloc( sizeof(bignum_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    if( !((*oper)->op2=(bignum_t *)malloc( sizeof(bignum_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    if( !((*oper)->rst=(short *)malloc( sizeof(short) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    
    
    return OK;
}


operation_status_t rezizeStructOperation(operation_t **oper,size_t *size){
    

    (*oper)=(operation_t *)realloc((*oper),sizeof(*oper)*1);
    
    /* pido memoria para cada bignum_t */
    if( !(oper[*size]->op1=(bignum_t *)malloc( sizeof(bignum_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    if( !(oper[*size]->op2=(bignum_t *)malloc( sizeof(bignum_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    if( !(oper[*size]->rst=(short *)malloc( sizeof(short) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    (*size)++;
    
    return OK;
}



operation_status_t cargarStructNumeros(operation_t **oper,size_t *size,size_t *pos,char *num1,char *num2)
{
    
    size_t size_num1=0;
    size_t size_num2=0;
    size_t i=0;
    
    size_num1=strlen(num1);
    size_num2=strlen(num2);
    
    /* corroboracion para no pasarnos del array */
    if ( (*pos)>(*size) ) return ERROR;
    
    /* pido memoria para la cadena que contendra los digitos bignum_t*/
    if( !( oper[*pos]->op1->digits=(ushort *)malloc( sizeof(ushort)*(size_num1-1)) ) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    if( !(oper[*pos]->op2->digits=(ushort *)malloc(sizeof(ushort)*(size_num2-1))) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    if (num1[0]=='-') {
        oper[*pos]->op1->sign=NEGATIVE;
    }
    else if (num1[0]=='+') {
        oper[*pos]->op1->sign=POSITIVE;
    }
    else oper[*pos]->op1->sign=POSITIVE;

    if (num2[0]=='-') {
        oper[*pos]->op2->sign=NEGATIVE;
    }
    else if (num2[0]=='+') {
        oper[*pos]->op2->sign=POSITIVE;
    }
    else oper[*pos]->op2->sign=POSITIVE;
    
    
    /* Empezamos de 1 porque nos comemos el caracter de signo que se lo asignamos arriba */
    for (i=1; i<size_num1; i++) {
        oper[*pos]->op1->digits[i-1]=(ushort)(num1[i] - '0');
    }
    for (i=1; i<size_num2; i++) {
        oper[*pos]->op2->digits[i-1]=(ushort)(num2[i] - '0');
    }
    
    /* Agregamos q digits para saber hasta donde debemos iterar */
    oper[*pos]->op1->q_digits=size_num1-1;
    oper[*pos]->op2->q_digits=size_num2-1;
    
    return OK;

}













