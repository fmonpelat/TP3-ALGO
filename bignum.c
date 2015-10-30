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

operation_status_t inicializarStructOperation(operation_t ** oper,size_t size){
    
    if( !(oper=(operation_t **)malloc( sizeof(operation_t*) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
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
    
    
    size=1;
    
    return OK;
}


operation_status_t rezizeStructOperation(operation_t **oper,size_t size){
    
    (*oper)=(operation_t *)realloc((*oper),sizeof(*oper));
    
    /* pido memoria para cada bignum_t */
    if( !(oper[size]->op1=(bignum_t *)malloc( sizeof(bignum_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    if( !(oper[size]->op2=(bignum_t *)malloc( sizeof(bignum_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    if( !(oper[size]->rst=(short *)malloc( sizeof(short) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    size++; /* aumentamos el array en 1 */
    
    return OK;
}



operation_status_t cargarStructNumeros(operation_t **oper,size_t size,size_t pos,char *num1,char *num2)
{
    
    size_t size_num1=0;
    size_t size_num2=0;
    size_t i=0;
    
    size_num1=strlen(num1);
    size_num2=strlen(num2);
    
    /* corroboracion para no pasarnos del array */
    if (pos>size) return ERROR;
    
    /* pido memoria para la cadena que contendra los digitos bignum_t*/
    if( !( oper[pos]->op1->digits=(ushort *)malloc( sizeof(ushort)*size_num1) ) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    if( !(oper[pos]->op2->digits=(ushort *)malloc(sizeof(ushort)*size_num2)) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    for (i=0; i<size_num1; i++) {
        oper[pos]->op1->digits[i]=(ushort)(num1[i] - '0');
    }
    for (i=0; i<size_num2; i++) {
        oper[pos]->op2->digits[i]=(ushort)(num2[i] - '0');
    }
    
    return OK;

}













