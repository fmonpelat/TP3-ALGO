#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "bignum.h"
#include "simplecalc.h"

/* Defines para supercalc */
#define MAX_STR 10
#define VALID_ARGUMENTS 2 /* argumentos de entrada por parametro 1-> nombre del programa 2-> modo del programa (simplecalc o supercalc)*/
#define DEFAULT_PRECISION 1000
#define INPUT_MODE_SIMPLECALC "simpleCalc"
#define INPUT_MODE_SUPERCALC "superCalc"

/* typedef de supercalc */
typedef enum{ SIMPLECALC, SUPERCALC} calcMode_t;



/*##### PROTOTIPOS #########*/

void paso_linea_a_struct( char *, operation_t **, int );
char * GetLines( void );
operation_status_t parseLines( char ** ,char ** , char **, opt_t * );
char * searchEnter(char * );
char * prependChar(const char * , char );
operation_status_t ValidateArguments(int ,char **,size_t *,calcMode_t * );
void test(operation_vector_t * );
void printArrayShort(ushort *,size_t ,sign_t ,size_t );

/*#########################*/



int main(int argc,char *argv[])
{
    calcMode_t calcmode=SIMPLECALC; /* por default hacemos que sea simpleCalc */
    /* simpleCalc */
    int opt;
    
    /* superCalc */
    operation_vector_t operaciones_vect;
    char *num1=NULL;
    char *num2=NULL;
    char *input=NULL;
    operation_status_t statusLine=OK;
    size_t precision=DEFAULT_PRECISION;
    operation_status_t status_cargado=ERROR;
    size_t i=0;

    
    if (argc<VALID_ARGUMENTS)
    {
        fprintf(stderr, "Modo invalido de invocacion\n");
        fprintf(stderr, "Se debe de invocar como $%s <mode> -p <precision>\n",argv[0]);
        fprintf(stderr, "<mode> : modo de la calculadora %s o %s\n",INPUT_MODE_SIMPLECALC,INPUT_MODE_SUPERCALC);
        fprintf(stderr, "<precision> : precision del calculo antes de truncar ( Default: %d )\n",DEFAULT_PRECISION);
        return EXIT_FAILURE;
    }
    
    ValidateArguments(argc,argv,&precision,&calcmode);
    
    if ( calcmode==SUPERCALC )
    {
        test(&operaciones_vect);
        /*
        inicializarStructOperation(&operaciones_vect);
        
        while (statusLine!=_EOF)
        {
            
            input=GetLines();
            if(operaciones_vect.oper_size!=0) AddOperation(&operaciones_vect);

            statusLine=parseLines(&input, &num1, &num2, &(operaciones_vect.operaciones[operaciones_vect.oper_size]->op) );
            
            status_cargado=cargarStructNumeros(operaciones_vect.operaciones,
                                                &(operaciones_vect.oper_size),
                                                &(operaciones_vect.oper_size),
                                                num1,
                                                num2,
                                                &(operaciones_vect.operaciones[operaciones_vect.oper_size]->op),
                                                precision,
                                                statusLine
                                                );
            
            if ( status_cargado == OK )
            {
                switch (operaciones_vect.operaciones[operaciones_vect.oper_size]->op)
                {
                    case SUMA:
                                suma(&operaciones_vect, &(operaciones_vect.oper_size) );
                                break;
                    case RESTA:
                                resta(&operaciones_vect, &(operaciones_vect.oper_size) );
                                break;
                    case MULT:
                                multiplicar(&operaciones_vect, &(operaciones_vect.oper_size));
                                break;
                    default:
                        fprintf(stderr, "no se pudo efectuar ninguna operacion\n");
                        break;
                }
                printArrayShort(operaciones_vect.operaciones[operaciones_vect.oper_size]->rst, operaciones_vect.operaciones[operaciones_vect.oper_size]->q_rst,operaciones_vect.operaciones[operaciones_vect.oper_size]->sign_rst,precision);
                
                free(input);
                free(num1);
                free(num2);
                input=NULL;
                num1=NULL;
                num2=NULL;
            }
            else if(status_cargado==INF)
            {
                printf("Inf\n");
            }
            else
            {
                // si llegamos aca es que obtuvimos un #calculate
                if(operaciones_vect.oper_size==0){
                    if (!(operaciones_vect.operaciones[0]->rst = (ushort*)malloc(sizeof(ushort) )))
                    {
                        fprintf(stderr, "Error, could not find memory to allocate a result\n");
                    }
                }
                else
                {
                    if (!(operaciones_vect.operaciones[operaciones_vect.oper_size-1]->rst = (ushort*)malloc(sizeof(ushort) )))
                    {
                        fprintf(stderr, "Error, could not find memory to allocate a result\n");
                    }
                }
            }
            operaciones_vect.oper_size++;
        }
        
        /* liberamos memoria
        //free_operation_t(operaciones_vect.operaciones, operaciones_vect.oper_size,statusLine);
        free(input);
        free(num1);
        free(num2);
        input=NULL;
        num1=NULL;
        num2=NULL;
        */
        operaciones_vect.oper_size++;
        for (i=0; i<operaciones_vect.oper_size; i++)
        {
            free( operaciones_vect.operaciones[i]->op1->digits);
            operaciones_vect.operaciones[i]->op1->digits=NULL;
            free( operaciones_vect.operaciones[i]->op2->digits);
            operaciones_vect.operaciones[i]->op2->digits=NULL;
            free( operaciones_vect.operaciones[i]->op1);
            operaciones_vect.operaciones[i]->op1=NULL;
            free( operaciones_vect.operaciones[i]->op2);
            operaciones_vect.operaciones[i]->op2=NULL;
            free( operaciones_vect.operaciones[i]->rst);
            operaciones_vect.operaciones[i]->rst=NULL;
        }
        
        for (i=0; i<operaciones_vect.oper_size; i++)
        {
            free(operaciones_vect.operaciones[i]);
            operaciones_vect.operaciones[i]=NULL;
        }
        free(operaciones_vect.operaciones);
        operaciones_vect.operaciones=NULL;

        
    }
    else if( calcmode==SIMPLECALC)
    {
        
        /* modo calculadora simple */
        printf(MENU);
        scanf("%d",&opt);
        opcion(opt);
        return 0;

    }
    
    
    return 0;
}






/*###############################*/
/*####### funciones #############*/

void test(operation_vector_t * oper_vect)
{
    size_t precision=DEFAULT_PRECISION;
    size_t i=0;
    /* Los numeros van con su signo para ser tomados y cargados correctamente en cargarStructNumeros */
    char num1[]="+20";
    char num2[]="+10";
    opt_t operation=RESTA;
    operation_status_t status=OK;
    
    	
    inicializarStructOperation(oper_vect);
    //AddOperation(oper_vect);
    cargarStructNumeros(&(oper_vect->operaciones[oper_vect->oper_size]), &(oper_vect->oper_size), &(oper_vect->oper_size), num1, num2, &(operation) ,precision,status);
    
    
    /*probamos las funciones una por una */
    
    /* Prueba de resta_digito_a_digito() probar con los numeros siguientes num1 > num2 en caracteres
       char num1[]="+40";
       char num2[]="+2";
    
    opt_t operation=RESTA;
    
    oper_vect->operaciones[oper_vect->oper_size]->rst = resta_digito_a_digito(
                                                                              oper_vect->operaciones[oper_vect->oper_size]->op1->digits,
                                                                              oper_vect->operaciones[oper_vect->oper_size]->op2->digits,
                                                                              oper_vect->operaciones[oper_vect->oper_size]->op1->q_digits,
                                                                              oper_vect->operaciones[oper_vect->oper_size]->op2->q_digits,
                                                                              &(oper_vect->operaciones[oper_vect->oper_size]->q_rst));
    
    printArrayShort(oper_vect->operaciones[oper_vect->oper_size]->rst,
                    oper_vect->operaciones[oper_vect->oper_size]->q_rst,
                    oper_vect->operaciones[oper_vect->oper_size]->sign_rst,
                    precision);
    */
    
    
    /* Prueba de resta()
    resta(oper_vect, &(oper_vect->oper_size));
    printArrayShort(oper_vect->operaciones[oper_vect->oper_size]->rst,
                    oper_vect->operaciones[oper_vect->oper_size]->q_rst,
                    oper_vect->operaciones[oper_vect->oper_size]->sign_rst,
                    precision);
    
    oper_vect->oper_size++;
    AddOperation(oper_vect);
    
    cargarStructNumeros(oper_vect->operaciones, &(oper_vect->oper_size), &(oper_vect->oper_size), num1, num2, &(operation) ,precision,status);
    
    resta(oper_vect, &(oper_vect->oper_size));
    printArrayShort(oper_vect->operaciones[oper_vect->oper_size]->rst,
                    oper_vect->operaciones[oper_vect->oper_size]->q_rst,
                    oper_vect->operaciones[oper_vect->oper_size]->sign_rst,
                    precision);
     */
    
    /* Prueba de suma_digito_a_digito() (no funciona si el primer op1 tiene mas caracteres que el op2 se llama a suma para contrarestar este problema.)
    oper_vect->operaciones[oper_vect->oper_size]->rst = suma_digito_a_digito(oper_vect->operaciones[oper_vect->oper_size]->op1->digits,
                                                                             oper_vect->operaciones[oper_vect->oper_size]->op2->digits,
                                                                             oper_vect->operaciones[oper_vect->oper_size]->op1->q_digits,
                                                                             oper_vect->operaciones[oper_vect->oper_size]->op2->q_digits,
                                                                             &(oper_vect->operaciones[oper_vect->oper_size]->q_rst));
    
    printArrayShort(oper_vect->operaciones[oper_vect->oper_size]->rst,oper_vect->operaciones[oper_vect->oper_size]->q_rst);
    printf("\n");
    */
    
    /* Prueba de suma()*/

    suma( oper_vect, &(oper_vect->oper_size) );
    printArrayShort(oper_vect->operaciones[oper_vect->oper_size]->rst,
                    oper_vect->operaciones[oper_vect->oper_size]->q_rst,
                    oper_vect->operaciones[oper_vect->oper_size]->sign_rst,
                    precision);

    
    oper_vect->oper_size++;
    AddOperation(oper_vect);
    
    cargarStructNumeros(oper_vect->operaciones, &(oper_vect->oper_size), &(oper_vect->oper_size), num1, num2, &(operation) ,precision,status);
    
    suma( oper_vect, &(oper_vect->oper_size) );
    printArrayShort(oper_vect->operaciones[oper_vect->oper_size]->rst,
                    oper_vect->operaciones[oper_vect->oper_size]->q_rst,
                    oper_vect->operaciones[oper_vect->oper_size]->sign_rst,
                    precision);

    
    /* Prueba de Multiplicacion */
    /*oper_vect->operaciones[oper_vect->oper_size]->rst = multiplico(
                                                                   oper_vect->operaciones[oper_vect->oper_size]->op1->digits,
                                                                   oper_vect->operaciones[oper_vect->oper_size]->op2->digits,
                                                                   oper_vect->operaciones[oper_vect->oper_size]->op1->q_digits,
                                                                   oper_vect->operaciones[oper_vect->oper_size]->op2->q_digits,
                                                                   &(oper_vect->operaciones[oper_vect->oper_size]->q_rst));
    
    oper_vect->operaciones[oper_vect->oper_size]->rst = multiplico(
                                                                oper_vect->operaciones[oper_vect->oper_size]->op1->digits,
                                                                oper_vect->operaciones[oper_vect->oper_size]->op2->digits,
                                                                oper_vect->operaciones[oper_vect->oper_size]->op1->q_digits,
                                                                oper_vect->operaciones[oper_vect->oper_size]->op2->q_digits,
                                                                 &(oper_vect->operaciones[oper_vect->oper_size]->q_rst));
    
    printArrayShort(oper_vect->operaciones[oper_vect->oper_size]->rst, oper_vect->operaciones[oper_vect->oper_size]->q_rst,oper_vect->operaciones[oper_vect->oper_size]->sign_rst,precision);
    printf("\n");
    */

    
}



operation_status_t ValidateArguments(int argc,char **argv,size_t *precision,calcMode_t *mode)
{
    
    size_t i=0;
    
    
    for (i=1; i<argc; i++)
    {
        if ( !(strcmp(argv[i],INPUT_MODE_SIMPLECALC)) )
        {
            *mode=SIMPLECALC;
            break;
        }
        else if( !(strcmp(argv[i],INPUT_MODE_SUPERCALC)) )
        {
            *mode=SUPERCALC;
            break;
        }

    }
    for (i=1; i<argc; i++)
    {
        if (!(strcmp(argv[i],"-p")))
        {
            *precision=atoi(argv[i+1]);
            if (!*precision) *precision=DEFAULT_PRECISION;
        }
    }
    return OK;
    
}





char * GetLines( void )
{
    

    char lines[MAX_STR];
    char *totalLines=NULL;
    char *aux=NULL;
    /* como pedimos memoria esta hardcodeado de a init chop chars por llamada */
    size_t used_size = 0;
    size_t alloc_size = 0, init_chop = MAX_STR, chop_size = MAX_STR*2;
    size_t counterMemoryCallouts=0;

    
    /* pedimos memoria por primera vez antes de reallocar si es que necesitamos memoria.
     */
    if (!(totalLines = (char*)calloc(init_chop,sizeof(char))))
    {
        fprintf(stderr, "Error, could not find memory\n");
        return NULL;
    }
    
    
    alloc_size = init_chop;
    
    
    while ( !(searchEnter( lines )) )
    {
        fgets(lines, MAX_STR, stdin);
        
        
        /* nos preguntamos si necesitamos memoria ... pedimos de a chops o de a pedazos
         */
        if (used_size == alloc_size)
        {
            
            if (!(aux = (char*)realloc(totalLines, sizeof(char)*(alloc_size + chop_size))))
            {
                fprintf(stderr, "Error, could not find memory\n");
                free(totalLines);
                totalLines = NULL;
                return NULL;
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
    
    return totalLines;
    
}

operation_status_t parseLines( char **totalLines,char **line1, char **line2,opt_t *operation)
{
    
    char *ptr;
    char *ptr2;
    size_t i; /*contador para parsear con strtok*/
    
    
    if ( strcmp(*totalLines,"#calculate") )
    {
        /* Aca calculo como separar las cadenas de caracteres en line1 y line2 */
        
            if (*totalLines[0]=='*')
            {
                return ERROR;
            }
            else if ( *totalLines[0]=='+')
            {
                
                /* que pasa si no hay un - o un + en el medio? */
                for (i=1; i<strlen(*totalLines); i++)
                {
                    if ( !(isdigit((*totalLines)[i])) )
                    {
                        
                        if ((*totalLines)[i]=='-')
                        {
                            ptr=strtok(*totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                            ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                            *line1=prependChar(ptr,'#');
                            *line2=prependChar(ptr2, '-');
                            *operation=RESTA;
                            return OK;
                        }
                        
                        if ((*totalLines)[i]=='+')
                        {
                            ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                            ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                            /**(searchEnter(ptr2))='\0';*/
                            *line1=prependChar(ptr,'#');
                            *line2=prependChar(ptr2,'+');
                            *operation=SUMA;
                            return OK;
                        }
                    }
                }
                ptr=NULL; /* si llegamos hasta aca es porque no se ingreso una operacion */
            }
            else if (*totalLines[0]=='-' ) {
                
                /* que pasa si no hay un - o un + en el medio? */
                for (i=1; i<strlen(*totalLines); i++)
                {
                    if ( !(isdigit((*totalLines)[i])) )
                    {
                        
                        if ((*totalLines)[i]=='-')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                            ptr=strtok(*totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                            ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                            *line1=prependChar(ptr, '-');
                            *line2=prependChar(ptr2, '+');
                            *operation=SUMA;
                            return OK;
                            }
                            else
                            {
                                ptr=strtok(*totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr, '-');
                                *line2=prependChar(ptr2, '-');
                                *operation=RESTA;
                                return OK;
                            }
                                
                        }
                        
                        if ((*totalLines)[i]=='+')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                                ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                /**line1=prependChar(ptr, '-');
                                *line2=prependChar(ptr2, '-');*/
                                *line1=prependChar(ptr,'#');
                                *line2=prependChar(ptr2,'#');
                                *operation=SUMA;
                                return OK;
                            }
                            else
                            {
                                ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'#');
                                *line2=prependChar(ptr2,'+');
                                *operation=SUMA;
                                return OK;
                            }
                        }
                        if ((*totalLines)[i]=='*')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                                ptr=strtok(*totalLines,"*"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"*"); /* este es nuestro primer numero */
                                /*line1=prependChar(ptr, '-');
                                *line2=prependChar(ptr2, '-');*/
                                *line1=prependChar(ptr,'#');
                                *line2=prependChar(ptr2,'#');
                                *operation=MULT;
                                return OK;
                            }
                            else
                            {
                                ptr=strtok(*totalLines,"*"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"*"); /* este es nuestro primer numero */
                                /**line1=prependChar(ptr, '-');*/
                                *line1=prependChar(ptr,'#');
                                *line2=prependChar(ptr2, '+');
                                *operation=MULT;
                                return OK;
                            }
                        }
                    }
                }
                ptr=NULL; /* Si llegamos hasta aca es porque no se ingreso una operacion */
            }
            else
            {
                for (i=1; i<strlen(*totalLines); i++)
                {
                    if ( !(isdigit((*totalLines)[i])) )
                    {
                        if ((*totalLines)[i]=='-')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001--222 */
                                ptr=strtok(*totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=SUMA;
                                return OK;
                            }
                            else
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001-222 */
                                ptr=strtok(*totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=RESTA;
                                return OK;

                            }
                        }
                        
                        if ((*totalLines)[i]=='+')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001+-222 */
                                ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'-');
                                *operation=RESTA;
                                return OK;
                            }
                            else if((*totalLines)[i+1]=='+')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001++222 */
                                ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=SUMA;
                                return OK;

                            }
                            else
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001+222 */
                                ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=SUMA;
                                return OK;
                            }
                        }
                        
                        if ((*totalLines)[i]=='*')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001*-222 */
                                ptr=strtok(*totalLines,"*"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'-');
                                *operation=MULT;
                                return OK;
                            }
                            else if((*totalLines)[i+1]=='+')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001*+222 */
                                ptr=strtok(*totalLines,"*"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=MULT;
                                return OK;
                                
                            }
                            else
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 10*3 */
                                ptr=strtok(*totalLines,"*"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"*"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=MULT;
                                return OK;
                            }
                        }
                    }
                }
                ptr=NULL; /* Si llegamos hasta aca es porque no se ingreso una operacion */
            }

        if (!ptr) return _EOF;
    }
    else
    {
        *line1=prependChar("00",'+');
        *line2=prependChar("00",'+');
        *operation=NOOPERATION;
        return _EOF;
    }
    
    return OK;
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
    char * string = (char *)calloc( strlen(str)+2,sizeof(char) ); /* añadimos 2 posiciones una para el caracter y otra para el \0 */
    if(c!='#')
    {
        string[0] = c;
        strcpy(string + 1, str);
    }
    else
    {
        strcpy(string, str);
    }
    return string;
}

void printArrayShort(ushort *str,size_t size,sign_t sign,size_t precision){
    
    size_t i=0;
    int flag_print=0;

    
    if (sign==NEGATIVE) printf("-");
    
    for (i=0; i<size ; i++) {
        if( (str[i]!=0) || (flag_print) )
        {
            if(i!=precision)
            {
                printf("%d",str[i]);
                flag_print=1;
            }
            else
            {
                printf("\nOverflow\n");
                break;
            }
            fflush(stdout);
        }
    }
    if (!flag_print) {
        printf("0");
    }
    printf("\n");
}







