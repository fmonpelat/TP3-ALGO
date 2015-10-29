#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "bignum.h"

#define MAX_STR 10
#define VALID_ARGUMENTS 2 /* argumentos de entrada por parametro 1-> nombre del programa 2-> modo del programa (simplecalc o supercalc)*/
#define DEFAULT_PRECISION 1000
#define INPUT_MODE_SIMPLECALC "simpleCalc"
#define INPUT_MODE_SUPERCALC "superCalc"

typedef enum{ eof, ok, error, nomem, nooperation, invalidsintax} status_t;
typedef enum{ SIMPLECALC, SUPERCALC} calcMode_t;

/*##### PROTOTIPOS #########*/
void paso_linea_a_struct(char *linea,operation_t **operacion,int length);
status_t GetLines(char **line1, char **line2,opt_t operation);
char * searchEnter(char *str );
char * prependChar(const char * str, char c);
status_t ValidateArguments(int argc,char **argv,int *precision,calcMode_t *mode);
/*#########################*/



int main(int argc,char *argv[])
{
    operation_t **operaciones=NULL; /* Creo un vector de punteros a operation_t*/
    char *num1;
    char *num2;
    opt_t operation=NOOPERATION; /* para saber si existe una operacion valida */
    status_t statusgetLine=ok;
    calcMode_t calcmode=SIMPLECALC; /* por default hacemos que sea simpleCalc */
    int precision=DEFAULT_PRECISION;
    int n=0,length = 0;
    
    
    if (argc<VALID_ARGUMENTS) {
        fprintf(stderr, "Modo invalido de invocacion\n");
        fprintf(stderr, "Se debe de invocar como $%s <mode> -p <precision>\n",argv[0]);
        fprintf(stderr, "<mode> : modo de la calculadora %s o %s\n",INPUT_MODE_SIMPLECALC,INPUT_MODE_SUPERCALC);
        fprintf(stderr, "<precision> : precision del calculo antes de truncar Default: %d\n",DEFAULT_PRECISION);
        return EXIT_FAILURE;
    }
    ValidateArguments(argc,argv,&precision,&calcmode);
    
    if (calcmode==SUPERCALC) {
        
        while (statusgetLine!=eof) {
            
            statusgetLine=GetLines( &num1, &num2, operation);
            printf("num1:%s num2:%s",num1,num2);
            
            // hasta aca ya tenemos los 2 numeros y la operacion que tenemos que hacer....
            
            // falta pasar los numeros a la estructura
            // escribir las funciones que trabajaran sobre la estructura para hacer la suma resta y multiplicacion.
    
        }
        //impresion de resultados
        for(n=0;n<length;n++)   /*Flashie que quería imprimir algo desde el struct pero estaba re quemado ya.*/
            printf("%d",operaciones[0]->op1->digits[n]);
        //liberar memoria


    }
    else if( calcmode==SIMPLECALC){
        
        // modo calculadora simple
        // pegar el main del tp2!!!
    }
    
    
    

    
    return 0;
}







/* funciones */


void paso_linea_a_struct(char *linea,operation_t **operacion,int length)
{
    char *ptr=NULL;
    char aux[MAX_STR],num1[MAX_STR],num2[MAX_STR];
    int i;
    char calc;
    
    strcpy(aux,linea);
    /*if(aux[0]=='-')
     {
     *operacion->op1->sign=NEGATIVE;    Esta parte es para chequear el signo del primer numero, y en consecuencia mover el puntero
     para que si hay un signo menos, despues se empiece a leer desde el segundo caracter.
     ptr=strtok(aux,"-");
     }
     else operacion->op1->sign=POSITIVE;
     */
    //(*operacion)->op=busco_opcion(aux,length);
    if((*operacion)->op==SUMA) calc='+';    /* Calc es el simbolo de la operacion en sí*/
    else if((*operacion)->op==RESTA) calc='-';
    else if((*operacion)->op==MULT) calc='x';
    ptr=strtok(linea,&calc);  /*guardo en ptr la cadena desde donde estaba antes, hasta que encuentra el simbolo de la operacion*/
    strcpy(num1,ptr);
    (*operacion)->op1=(bignum_t*)malloc(sizeof(bignum_t));
    (*operacion)->op1->digits=(unsigned short*)malloc(sizeof(unsigned short)*(strlen(num1)+1)); /*Genero memoria, revisar*/
    for(i=0;i<strlen(num1);i++)
        (*operacion)->op1->digits[i]=atoi(&num1[i]); /*Voy guardando en digits cada numero en la cadena num1*/
    
    strcpy(num2,ptr);
    (*operacion)->op2=(bignum_t*)malloc(sizeof(bignum_t));
    (*operacion)->op2->digits=(unsigned short*)malloc(sizeof(unsigned short)*(strlen(num2)+1));
    for(i=0;i<strlen(num2);i++)
        (*operacion)->op2->digits[i]=atoi(&num2[i]);  /*Lo mismo para el segundo numero, faltaría hacer que verifique su signo*/
}






status_t ValidateArguments(int argc,char **argv,int *precision,calcMode_t *mode){
    
    size_t i=0;
    
    
    for (i=1; i<argc; i++) {
        if ( !(strcmp(argv[i],INPUT_MODE_SIMPLECALC)) )
        {
            *mode=SIMPLECALC;
        }
        else if( !(strcmp(argv[i],INPUT_MODE_SUPERCALC)) )
        {
            *mode=SUPERCALC;
        }
        else *mode=SIMPLECALC;
        
        if (!(strcmp(argv[i],"-p")))
        {
            *precision=atoi(argv[i+1]);
            if (!*precision) *precision=DEFAULT_PRECISION;
        }
        else *precision=DEFAULT_PRECISION;
    }
    return ok;
    
}





status_t GetLines( char **line1, char **line2,opt_t operation){
    

    char lines[MAX_STR];
    char *totalLines=NULL;
    char *aux=NULL;
    char *ptr;
    char *ptr2;
    /* como pedimos memoria esta hardcodeado de a init chop chars por llamada */
    size_t used_size = 0;
    size_t alloc_size = 0, init_chop = MAX_STR, chop_size = MAX_STR*2;
    size_t counterMemoryCallouts=0;
    size_t i; /*contador para parsear con strtok*/
    
    
    
    
    /* pedimos memoria por primera vez antes de reallocar si es que necesitamos memoria.
     */
    if (!(totalLines = (char*)malloc(sizeof(char)*init_chop))) {
        fprintf(stderr, "Error, could not find memory\n");
        return nomem;
    }
    
    
    alloc_size = init_chop;
    
    
    while ( !(searchEnter( lines )) ){
        fgets(lines, MAX_STR, stdin);
        
        
        /* nos preguntamos si necesitamos memoria ... pedimos de a chops o de a pedazos
         */
        if (used_size == alloc_size) {
            
            if (!(aux = (char*)realloc(totalLines, sizeof(char)*(alloc_size + chop_size)))) {
                fprintf(stderr, "Error, could not find memory\n");
                free(totalLines);
                totalLines = NULL;
                return nomem;
            }
            totalLines = aux;
            alloc_size += chop_size; /* incremento en suma o escalonada */
            counterMemoryCallouts++;
            /* debugging alloc size callouts
            printf("counter:%lu alloc:%lu chop_size:%lu\n",counterMemoryCallouts,alloc_size,chop_size);*/
             
        }
        /* concatenamos line con totallines para obtener el string final */
        strcat(totalLines, lines);
        /* incrementamos en MAX_STR el used size asi si nos falta obtener del stdin pedimos memoria */
        used_size=used_size+MAX_STR;
        /* debug totallines printf("%s\n",totalLines); */
    }
    
    /* quitamos el \n y hacemos null terminated string */
    totalLines[strlen(totalLines)-1]='\0';
        
        
    
    if ( strcmp(totalLines,"#calculate") ) {
        /* Aca calculo como separar las cadenas de caracteres en line1 y line2 */
        
        while ( ptr!=NULL ) {
            
            if (totalLines[0]=='*') {
                return invalidsintax;
            }
            else if ( totalLines[0]=='+') {
                
                // que pasa si no hay un - o un + en el medio?
                for (i=1; i<strlen(totalLines); i++)
                {
                    if ( !(isdigit(totalLines[i])) )
                    {
                        
                        if (totalLines[i]=='-')
                        {
                            ptr=strtok(totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                            ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                            *line1=ptr;
                            *line2=prependChar(ptr2, '-');
                            operation=RESTA;
                            free(totalLines);
                            return ok;
                        }
                        
                        if (totalLines[i]=='+')
                        {
                            ptr=strtok(totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                            ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                            *(searchEnter(ptr2))='\0';
                            *line1=ptr;
                            *line2=prependChar(ptr2,'+');
                            operation=SUMA;
                            free(totalLines);
                            return ok;
                        }
                    }
                }
                ptr=NULL; /* si llegamos hasta aca es porque no se ingreso una operacion */
            }
            else if (totalLines[0]=='-' ) {
                
                // que pasa si no hay un - o un + en el medio?
                for (i=1; i<strlen(totalLines); i++)
                {
                    if ( !(isdigit(totalLines[i])) )
                    {
                        
                        if (totalLines[i]=='-')
                        {
                            ptr=strtok(totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                            ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                            *line1=prependChar(ptr, '-');
                            *line2=prependChar(ptr2, '-');
                            operation=RESTA;
                            free(totalLines);
                            return ok;
                        }
                        
                        if (totalLines[i]=='+')
                        {
                            ptr=strtok(totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                            ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                            *line1=ptr;
                            *line2=prependChar(ptr2,'+');
                            free(totalLines);
                            operation=SUMA;
                            return ok;
                        }
                    }
                }
                ptr=NULL; /* Si llegamos hasta aca es porque no se ingreso una operacion */
            }
            else
            {
                for (i=1; i<strlen(totalLines); i++)
                {
                    if ( !(isdigit(totalLines[i])) )
                    {
                        if (totalLines[i]=='-')
                        {
                            if (totalLines[i+1]=='-')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001--222 */
                                ptr=strtok(totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                operation=SUMA;
                                free(totalLines);
                                return ok;
                            }
                            else
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001-222 */
                                ptr=strtok(totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'-');
                                operation=SUMA;
                                free(totalLines);
                                return ok;

                            }
                        }
                        
                        if (totalLines[i]=='+')
                        {
                            if (totalLines[i+1]=='-')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001+-222 */
                                ptr=strtok(totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'-');
                                free(totalLines);
                                operation=SUMA;
                                return ok;
                            }
                            else if(totalLines[i+1]=='+')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001++222 */
                                ptr=strtok(totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                free(totalLines);
                                operation=SUMA;
                                return ok;

                            }
                        }
                        
                        if (totalLines[i]=='*')
                        {
                            if (totalLines[i+1]=='-')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001+-222 */
                                ptr=strtok(totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'-');
                                free(totalLines);
                                operation=MULT;
                                return ok;
                            }
                            else if(totalLines[i+1]=='+')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001++222 */
                                ptr=strtok(totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                free(totalLines);
                                operation=MULT;
                                return ok;
                                
                            }
                        }
                    }
                }
                ptr=NULL; /* Si llegamos hasta aca es porque no se ingreso una operacion */
            }
        }
        if (!ptr) return nooperation;
    }
    else return eof;
    
    return ok;
}


char * searchEnter(char *str ){
    size_t i;
    for (i=0; i<strlen(str)+1; i++) {
        if (str[i]=='\n') {
            return str+i;
        }
    }
    return NULL;
}

char * prependChar(const char * str, char c)
{
    char * string = (char *)malloc( strlen(str)+2 );/* añadimos 2 posiciones una para el caracter y otra para el \0 */
    string[0] = c;
    strcpy(string + 1, str);
    return string;
}

