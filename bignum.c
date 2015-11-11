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
        free(*oper);
        return NOMEM;
    }
    if( !((*oper)->op2=(bignum_t *)malloc( sizeof(bignum_t) )) )
    {
        fprintf(stderr, "no memory \n");
        free((*oper)->op1);
        free(*oper);
        return NOMEM;
    }
    /* no se debe de pedir memoria para rst ya que la funcion que hace la operacio directamente pide memoria de acuerdo a la cantidad de digitos que debe de agregar
    if( !((*oper)->rst=(short *)malloc( sizeof(short) )) )
    {
        fprintf(stderr, "no memory \n");
        free((*oper)->op1);
        free((*oper)->op2);
        free(*oper);
        return NOMEM;
    }
    */
    
    
    return OK;
}


operation_status_t rezizeStructOperation(operation_t **oper,size_t *size){
    

    (*oper)=(operation_t *)realloc((*oper),(sizeof(*oper)*(*size))+1);
    
    /* pido memoria para cada bignum_t */
    if( !(oper[*size]->op1=(bignum_t *)malloc( sizeof(bignum_t) )) )
    {
        fprintf(stderr, "no memory \n");
        free_operation_t(oper, *size-1);
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
    
    
    return OK;
}



operation_status_t cargarStructNumeros(operation_t **oper,size_t *size,size_t *pos,char *num1,char *num2, opt_t operation)
{
    
    size_t size_num1=0;
    size_t size_num2=0;
    size_t i=0;
    
    size_num1=strlen(num1);
    size_num2=strlen(num2);
    
    /* corroboracion para no pasarnos del array */
    if ( (*pos)>(*size) ) return ERROR;
    
    
    if ( oper[*pos]->op!=NOOPERATION )
    {
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
        
        /* agregamos la operacion a efectuar */
        oper[*pos]->op=operation;

    }
    else return _EOF;
    
    return OK;

}


void free_operation_t(operation_t ** oper,size_t size){
    
    size_t i=0;
    
    
    for (i=0; i<=size; i++) {
        
        free( oper[i]->op1->digits);
        oper[i]->op1->digits=NULL;
        free( oper[i]->op2->digits);
        oper[i]->op2->digits=NULL;
        free( oper[i]->op1);
        oper[i]->op1=NULL;
        free( oper[i]->op2);
        oper[i]->op2=NULL;
        free( oper[i]->rst);
        oper[i]->rst=NULL;
    }
    
    for (i=0; i<=size; i++) {
        free(oper[i]);
        oper[i]=NULL;
    }
    
    *oper=NULL;
}



short * resta_digito_a_digito (ushort *dig1, ushort *dig2,size_t cant1,size_t cant2, size_t *q_resultado)
{
    short *resultado=NULL;
    size_t carry=0,dif;
    int i=0;
    
    dif=cant1-cant2;
    
    // aca hay algo raro si cant1==cant2 entonces pedimos memoria para cant1 - 1 ?? deberiamos pedir para cant que es el mas grande de los numeros aunque no utilizemos todos
    if (!(resultado = (short*)malloc(sizeof(short)*(cant1))))
    {
        fprintf(stderr, "Error, could not find memory\n");
        return NULL;
    }
    for(i=cant1-1;i>=0;i--)
    {
        if((dig1[i]-carry)<dig2[i-dif])
        {
            //le pedimos prestado un 1 al de al lado a dig1[i-1]
            resultado[i]=10+dig1[i]-carry-dig2[i];
            if(!carry) carry++;
        }
        else if ((i-dif)<0)
            resultado[i]=dig1[i]-carry;
        else
        {
            resultado[i]=(dig1[i]-carry)-dig2[i];
            carry=0;
        }
    }
    *q_resultado=cant1;
    return resultado;
}

void resta ( operation_t **oper, size_t *pos )
{
    size_t i,flag=0;
    
    if ( (oper[*pos]->op1->q_digits) > (oper[*pos]->op2->q_digits) )
        oper[*pos]->rst = resta_digito_a_digito(oper[*pos]->op1->digits,oper[*pos]->op2->digits,oper[*pos]->op1->q_digits,oper[*pos]->op2->q_digits,&(oper[*pos]->q_rst));
    
    else if((oper[*pos]->op1->q_digits)<(oper[*pos]->op2->q_digits))
        oper[*pos]->rst=resta_digito_a_digito(oper[*pos]->op2->digits,oper[*pos]->op1->digits,oper[*pos]->op2->q_digits,oper[*pos]->op1->q_digits,&(oper[*pos]->q_rst));
    
    else
    {
        for(i=0;i<(oper[*pos]->op1->q_digits)-1;i++)
        {
            if((oper[*pos]->op1->digits[i])>(oper[*pos]->op2->digits[i]))
            {
                flag=1;
                break;
            }
        }
        if (flag)
        {
            /*SIGNO POS*/
            oper[*pos]->rst=resta_digito_a_digito(oper[*pos]->op1->digits,oper[*pos]->op2->digits,oper[*pos]->op1->q_digits,oper[*pos]->op2->q_digits,&(oper[*pos]->q_rst));
        }
        else
        {
            for(i=0;i<(oper[*pos]->op1->q_digits)-1;i++)
            {
                if( (oper[*pos]->op1->digits[i]) != (oper[*pos]->op2->digits[i]))
                {
                    flag=1;
                    break;
                }
            }
            if (flag)
            {
                /*SIGNO NEG*/
                oper[*pos]->rst=resta_digito_a_digito(oper[*pos]->op2->digits,oper[*pos]->op1->digits,oper[*pos]->op2->q_digits,oper[*pos]->op1->q_digits,&(oper[*pos]->q_rst));
            }
            else
            {
                oper[*pos]->rst=(short*)malloc(sizeof(short));
                //esto lo veo muy hardcodeado.....
                oper[*pos]->rst[0]=0;				/* Si llega acá el resultado es cero, corta."*/
            }
        }
        
    }
    
}
short * suma_digito_a_digito (ushort *dig1,ushort *dig2, size_t cant1, size_t cant2)
{
    size_t carry=0;short *resultado=NULL;size_t dif=cant1-cant2;int i;
    if (!(resultado = (short*)malloc(sizeof(short)*(cant1+1))))
    {
        fprintf(stderr, "Error, could not find memory\n");
        return NULL;
    }
    for(i=cant1-1;i>=0;i--)
    {
        resultado[i+1]=dig1[i]+dig2[i-dif]+carry;
        if(resultado[i+1]>9)
        {
            resultado[i+1]=resultado[i+1]-10;
            carry++;
        }
    }
    if(carry) resultado[0]=1;
    else resultado[0]=0;
    return resultado;
}

short * multiplico (ushort *dig1,ushort *dig2, size_t cant1, size_t cant2)
{
    ushort** res_matriz=NULL;int i,k,j;ushort carry=0;short * res=NULL;
    if (!(res_matriz = (ushort**)malloc(sizeof(ushort*)*(cant2))))
    {
        fprintf(stderr, "Error, could not find memory\n");
        return NULL;
    }
    for(k=0;k<cant2;k++)
    {
        if (!( res_matriz[k] = (ushort*) malloc (  sizeof(ushort)*(cant1+1+k) )) )
        {
            fprintf(stderr, "Error, could not find memory\n");
            return NULL;
        }
    }
    for(k=0;k<cant2;k++)
    {
        for(i=cant1+1;i<=cant1+k;i++)
            res_matriz[k][i]=0;
    }
    for(k=0;k<cant2;k++)
    {
        for(j=cant2-1;j>=0;j--)
        {
            carry=0;
            for(i=cant1-1;i>=0;i--)
            {
                res_matriz[k][i+1]=(dig2[j]*dig1[i])+carry;
                if (res_matriz[k][i+1]>9)
                {
                    carry=findCarry(res_matriz[k][i+1]);
                    res_matriz[k][i+1]=res_matriz[k][i+1]-10*carry;
                }
            }
            res_matriz[k][0]=carry;
        }
    }
    if (!  ( res = (short*) malloc (  sizeof(short)*(cant1+cant2) )   ))
    {
      		fprintf(stderr, "Error, could not find memory\n");
        return NULL;
   	}
    res=suma_digito_a_digito(res_matriz[1],res_matriz[0],cant1+2,cant1+1);
    for(k=2;k<cant2;k++)
        res=suma_digito_a_digito(res_matriz[k],(ushort*)res,cant1+1+k,cant1+1+k);
    return res;	
}

ushort findCarry (ushort num)
{
    ushort i;
    for(i=0;i<10;i++)
    {
        if((10*(i+1))>num)
            break;
    }
    return i;
}










