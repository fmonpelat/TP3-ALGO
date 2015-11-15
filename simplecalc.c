//
//  simplecalc.c
//  Tp3
//


#include "simplecalc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>



void opcion(opt_t opt)
{
    switch(opt)
    {
        case SUMA: suma_simplecalc();
            break;
            
        case RESTA: resta_simplecalc();
            break;
            
        case MULT: multiplicacion_simplecalc();
            break;
            
        case DIVISION: division();
            break;
            
        case POT: dialogo_pot();
            break;
            
        case FACT: dialogo_fact();
            break;
            
        case COMBIN: dialogo_comb();
            break;
            
        case ALEATORIO: dialogo_alea();
            break;
            
        case GRAFICO: menu_graf();
            break;
            
        default: printf("Entrada inválida, ingrese una opción del menú \n");
            break;
    }
    
    
}


float ingreso_val1(void)
{
    float aux1;
    printf("Ingrese el primer número \n");
    scanf("%f",&aux1);
    return aux1;
}

float ingreso_val2(void)
{
    float aux2;
    printf("Ingrese el segundo número \n");
    scanf("%f",&aux2);
    return aux2;
}


void suma_simplecalc(void)
{
    float val1, val2;
    val1 = ingreso_val1();
    val2 = ingreso_val2();
    printf("El Resultado es: %.4f \n",val1+val2);
    
}

void resta_simplecalc(void)
{
    float val1, val2;
    val1 = ingreso_val1();
    val2 = ingreso_val2();
    printf("El Resultado es: %.4f \n",val1-val2);
    
}


void multiplicacion_simplecalc(void)
{
    float val1, val2;
    val1 = ingreso_val1();
    val2 = ingreso_val2();
    printf("El Resultado es: %.4f \n",val1*val2);
}



void division(void)
{
    float val1, val2;
    val1 = ingreso_val1();
    val2 = ingreso_val2();
    if (val2!=0)
    {
        printf("El Resultado es: %.4f \n",val1/val2);
    }
    else
    {
        printf("No es posible dividir por 0\n");
    }
    
}


void dialogo_pot(void)
{
    float base;
    int exponente;
    
    printf("Ingrese la base \n");
    scanf("%f",&base);
    printf("Ingrese el exponente \n");
    scanf("%d",&exponente);
    printf("El Resultado es: %f \n",potencia(base, exponente));
}

void dialogo_fact(void)
{
    int in_facto;
    
    printf("Ingrese el número \n");
    scanf("%d",&in_facto);
    printf("El Resultado es: %.lu \n",factorial(in_facto));
    
}

void dialogo_comb(void)
{
    int comb1, comb2;
    
    printf("Ingrese el primer número \n");
    scanf("%d",&comb1);
    printf("Ingrese el segundo número \n");
    scanf("%d",&comb2);
    if (comb1>=0 && comb2>=0)
    {
        if(comb1<comb2)
        {
            printf("Error, no puede calcularse");
        }
        else
        {
            printf("El Resultado es: %d \n",combinatorio(comb1,comb2));
        }
    }
    else
    {
        printf("Entrada Inválida. Solo se admiten números Naturales");
    }
    
}

void dialogo_alea(void)
{
    float min, max;
    
    printf("Ingrese el mínimo del rango \n");
    scanf("%f",&min);
    printf("Ingrese el máximo del rango \n");
    scanf("%f",&max);
    if(min > max)
    {
        printf("Error. Ha ingresado mal el intervalo");
    }
    else
    {
        printf("El Resultado es: %.4f \n",aleatorio(min, max));
    }
    
}

float potencia(float base, int exponente)
{	float eq=base;
    if(exponente>0)
    {
        while(exponente>1)
        {
            eq = eq*base;
            exponente--;
        }
        return eq;
    }
    else
    {
        if(exponente<0)
        {
            while(exponente<-1)
            {
                eq = eq*base;
                exponente++;
            }
            eq = 1/eq;
            return eq;
            
        }
        else
        {
            return 1;
        }
    }
}

unsigned long factorial(int in_facto)
{
    int i;
    unsigned long fact=1;
    
    for (i = 1; i <= in_facto; i++)
        fact = fact*i;
    return fact;
}

int combinatorio(int comb1, int comb2)
{
    double resultado;
    
    if(comb2==0)
    {
        return 1;
    }
    else
    {
        if(comb1==0)
        {
            return 0;
        }
        else
        {
            resultado = (factorial(comb1))/(factorial(comb2)*factorial((comb1-comb2)));
            return resultado;
        }
    }
    return 0;
}

float aleatorio(float min, float max)
{
    float num;
    srand((int)time(NULL));
    num = (((((rand() %11) *0.1)+((rand() %11) *0.01)+((rand() %11) *0.01)+((rand() %11) *0.001))*(max-min)) + min);
    return num;
}

void menu_graf(void)
{
    FILE * pbm;
    int flag_opt=0; /* flag_opt = 0 si no entro a ninguna funcion a graficar */
    typedef enum {SEN=1,COS,POL0,POL1,POL2,POL3,LN,EXP,DEFAULT} opt_graf_t;
    opt_graf_t optgraf;
    char option[MAX_CHAR];
    int matriz[RESOLUCION][RESOLUCION];
    float vect_x[RESOLUCION];
    float vect_y[RESOLUCION];
    
    cargo_x(vect_x);
    
    printf(MENU_GRAF);
    limpiarbuffer();
    
    fgets(option, MAX_CHAR, stdin);
    option[strlen(option)-1]='\0';
    optgraf=atoi(option);
    
    /* si se ingreso algo que no es una opcion debe ir al default */
    if (optgraf==0) optgraf=DEFAULT;
    
    
    while (optgraf) {
        
        switch(optgraf)
        {
            case SEN: seno(vect_x, vect_y);
                flag_opt=1;
                break;
                
            case COS: coseno(vect_x, vect_y);
                flag_opt=1;
                break;
                
            case POL0: pol0(vect_x, vect_y);
                flag_opt=1;
                break;
                
            case POL1: pol1(vect_x, vect_y);
                flag_opt=1;
                break;
                
            case POL2: pol2(vect_x, vect_y);
                flag_opt=1;
                break;
                
            case POL3: pol3(vect_x, vect_y);
                flag_opt=1;
                break;
                
            case LN: ln(vect_x, vect_y);
                flag_opt=1;
                break;
                
            case EXP: expo(vect_x, vect_y);
                flag_opt=1;
                break;
                
            default: printf("Entrada inválida!\n");
                
        }
        /* Este if corta la ejecuccion del programa si ya grafico sale del bucle while(optgraf) */
        if(flag_opt==1) break;
        
        printf("Presione enter para volver al menu \n");
        limpiarbuffer();
        system(CLS);
        printf(MENU_GRAF);
        
        fgets(option, MAX_CHAR, stdin);
        option[strlen(option)-1]='\0';
        optgraf=atoi(option);
        
        /* Si se ingreso una letra o algo que no es valido*/
        if (!optgraf) optgraf=255;
        
    }
    
    /* Abrimos el pbm para guardar datos como file */
    /*
     make_pbm_file(&pbm);
     */
    
    inicializo_matriz(matriz);
    inicializo_ejes(matriz);
    cargo_matriz(matriz, vect_y);
    imprimo_matriz(matriz);
    
    
    /* grabamos la info y luego cerramos el file* */
    /*
     write_pbm_file(&pbm, matriz, RESOLUCION, RESOLUCION);
     close_pbm_file(&pbm);
     */
    
}

void cargo_x (float vect_x[RESOLUCION])
{
    /* Acá cargo el vector de x con las 600 componentes, tal que entren en el rango de 0 a 10.
     Queda vector_x=(0  0.016 0.032 ... 9,9834) */
    int i;
    float factor, a=RANGO, b=RESOLUCION;
    
    factor = (float) (a/b);
    for(i=0; i<RESOLUCION; i++)
    {
        vect_x[i] = factor*i;
    }
}

float pido_parametro_a(void)
{
    int err_flag=1;
    int i;
    char vect[MAX_CHAR];
    
    printf("Ingrese el parametro a:\n");
    fgets(vect, MAX_CHAR, stdin);
    vect[strlen(vect)-1]='\0';
    
    while (err_flag==1) {
        
        err_flag=0;
        if (vect[0]=='-'){
            for (i=1; i<strlen(vect); i++){
                if ( !(isdigit(vect[i])) ){
                    if (vect[i]!='.' &&  vect[i]!=',') err_flag=1;
                }
            }
        }
        else {
            for (i=0; i<strlen(vect); i++)
            {
                if ( !(isdigit(vect[i])) ){
                    if (vect[i]!='.' &&  vect[i]!=',') err_flag=1;
                }
            }
        }
        
        if (err_flag==1) {
            printf("Numero Invalido!\n");
            printf("Ingrese nuevamente el parametro a:\n");
            fgets(vect, MAX_CHAR, stdin);
            vect[strlen(vect)-1]='\0';
        }
    }
    
    return atof(vect);
}

float pido_parametro_b(void)
{
    int err_flag=1;
    int i;
    char vect[MAX_CHAR];
    
    printf("Ingrese el parametro b:\n");
    fgets(vect, MAX_CHAR, stdin);
    vect[strlen(vect)-1]='\0';
    
    while (err_flag==1) {
        
        err_flag=0;
        if (vect[0]=='-'){
            for (i=1; i<strlen(vect); i++){
                if ( !(isdigit(vect[i])) ){
                    if (vect[i]!='.' &&  vect[i]!=',') err_flag=1;
                }
            }
        }
        else {
            for (i=0; i<strlen(vect); i++)
            {
                if ( !(isdigit(vect[i])) ){
                    if (vect[i]!='.' &&  vect[i]!=',') err_flag=1;
                }
            }
        }
        
        if (err_flag==1) {
            printf("Numero Invalido!\n");
            printf("Ingrese nuevamente el parametro b:\n");
            fgets(vect, MAX_CHAR, stdin);
            vect[strlen(vect)-1]='\0';
        }
    }
    
    return atof(vect);
}

float pido_parametro_c(void)
{
    int err_flag=1;
    int i;
    char vect[MAX_CHAR];
    
    printf("Ingrese el parametro c:\n");
    fgets(vect, MAX_CHAR, stdin);
    vect[strlen(vect)-1]='\0';
    
    while (err_flag==1) {
        
        err_flag=0;
        if (vect[0]=='-'){
            for (i=1; i<strlen(vect); i++){
                if ( !(isdigit(vect[i])) ){
                    if (vect[i]!='.' &&  vect[i]!=',') err_flag=1;
                }
            }
        }
        else {
            for (i=0; i<strlen(vect); i++)
            {
                if ( !(isdigit(vect[i])) ){
                    if (vect[i]!='.' &&  vect[i]!=',') err_flag=1;
                }
            }
        }
        
        if (err_flag==1) {
            printf("Numero Invalido!\n");
            printf("Ingrese nuevamente el parametro c:\n");
            fgets(vect, MAX_CHAR, stdin);
            vect[strlen(vect)-1]='\0';
        }
    }
    
    return atof(vect);}

float pido_parametro_d(void)
{
    int err_flag=1;
    int i;
    char vect[MAX_CHAR];
    
    printf("Ingrese el parametro d:\n");
    fgets(vect, MAX_CHAR, stdin);
    vect[strlen(vect)-1]='\0';
    
    while (err_flag==1) {
        
        err_flag=0;
        if (vect[0]=='-'){
            for (i=1; i<strlen(vect); i++){
                if ( !(isdigit(vect[i])) ){
                    if (vect[i]!='.' &&  vect[i]!=',') err_flag=1;
                }
            }
        }
        else {
            for (i=0; i<strlen(vect); i++)
            {
                if ( !(isdigit(vect[i])) ){
                    if (vect[i]!='.' &&  vect[i]!=',') err_flag=1;
                }
            }
        }
        
        if (err_flag==1) {
            printf("Numero Invalido!\n");
            printf("Ingrese nuevamente el parametro d:\n");
            fgets(vect, MAX_CHAR, stdin);
            vect[strlen(vect)-1]='\0';
        }
    }
    
    return atof(vect);
}

/* Funciones para cada opcion en el switch, van guardando el resultado en el vector_y*/
void seno(float vect_x[],float vect_y[])
{
    int i;
    float a,b,c;
    
    printf("La funcion senoidal es de la forma: y(x)=a*sen(bx+c)\n");
    a=pido_parametro_a();
    b=pido_parametro_b();
    c=pido_parametro_c();
    for(i=0;i<RESOLUCION;i++)
    {
        vect_y[i]=a*(sin((b*(vect_x[i]))+c));
    }
}


void coseno(float vect_x[],float vect_y[])
{
    int i;
    float a,b,c;
    
    printf("La funcion senoidal es de la forma: y(x)=a*cos(bx+c)\n");
    a=pido_parametro_a();
    b=pido_parametro_b();
    c=pido_parametro_c();
    for(i=0;i<RESOLUCION;i++)
    {
        vect_y[i]=a*cos(b*(vect_x[i])+c);
    }
}

void pol0(float vect_x[],float vect_y[])
{
    int i;
    float a;
    
    printf("El polinomio grado cero es de la forma: y(x)=a\n");
    a=pido_parametro_a();
    for(i=0;i<RESOLUCION;i++)
    {
        vect_y[i]=a;
    }
}

void pol1(float vect_x[],float vect_y[])
{
    int i;
    float a,b;
    
    printf("El polinomio grado cero es de la forma: y(x)=ax+b\n");
    a=pido_parametro_a();
    b=pido_parametro_b();
    for(i=0;i<RESOLUCION;i++)
    {
        vect_y[i]=a*(vect_x[i])+b;
    }
}

void pol2(float vect_x[],float vect_y[])
{
    int i;
    float a,b,c;
    
    printf("El polinomio grado cero es de la forma: y(x)=ax^2+bx+c\n");
    a=pido_parametro_a();
    b=pido_parametro_b();
    c=pido_parametro_c();
    for(i=0;i<RESOLUCION;i++)
    {
        vect_y[i]=a*(vect_x[i])*(vect_x[i])+b*(vect_x[i])+c;
    }
}

void pol3(float vect_x[],float vect_y[])
{
    int i;
    float a,b,c,d;
    
    printf("El polinomio grado cero es de la forma: y(x)= ax^3 + bx^2 + cx + d\n");
    a=pido_parametro_a();
    b=pido_parametro_b();
    c=pido_parametro_c();
    d=pido_parametro_d();
    for(i=0;i<RESOLUCION;i++)
    {
        vect_y[i]=a*(vect_x[i])*(vect_x[i])*(vect_x[i])+b*(vect_x[i])*(vect_x[i])+c*(vect_x[i])+d;
    }
}

void ln(float vect_x[],float vect_y[])
{
    int i;
    float a,b,c;
    
    printf("La función es de la forma y(x)= ln(ax + b) + c\n");
    
    a=pido_parametro_a();
    while (a<=0) {
        printf("El parametro ingresado es menor a 0, ingrese uno mayor\n");
        a=pido_parametro_a();
    }
    b=pido_parametro_b();
    while (b<0) {
        printf("El parametro ingresado es menor a 0, ingrese uno mayor\n");
        b=pido_parametro_b();
    }
    c=pido_parametro_c();
    
    for(i=1;i<RESOLUCION-1;i++)
    {
        if (vect_y[i]>RESOLUCION)break;
        vect_y[i]=(log(a*(vect_x[i])+b))+c;
    }
}

void expo(float vect_x[],float vect_y[])
{
    int i;
    float a,b,c;
    
    printf("La función es de la forma y(x)= e^(ax + b) + c\n");
    
    a=pido_parametro_a();
    b=pido_parametro_b();
    c=pido_parametro_c();
    for(i=0;i<RESOLUCION;i++)
    {
        if (vect_y[i]>RESOLUCION)break;
        vect_y[i]=(exp(a*(vect_x[i])+b))+c;
        
    }
}

void inicializo_matriz(int matriz[][RESOLUCION])
{
    int i,j;						/*Inicializo matriz cuadrada con todos ceros*/
    
    for(i=0;i<RESOLUCION;i++)
    {
        for(j=0;j<RESOLUCION;j++)
        {
            matriz[i][j]=COLOR_BLANCO;
        }
    }
}

void inicializo_ejes(int matriz[][RESOLUCION])
{
    int i, j;
    int divisiones_ejes=RESOLUCION/10; /* Esta variable es para agregar los puntos en las divisiones
                                        (las marquitas en los puntos enteros para ambos ejes*/
    
    for( i=(RESOLUCION/2)-1; i<=(RESOLUCION/2)+1 ; i++ )
    {
        /* Agrego el eje X; el primer ciclo (el de la var i) es para
         darle un grosor de 3 pixeles y se vea mejor*/
        for(j=0;j<RESOLUCION;j++)
        {
            matriz[i][j]=COLOR_NEGRO;
        }
    }
    
    for(j=0;j<2;j++)			/* Agrego el eje y, tambien con un grosor de 3 pixeles*/
    {
        for(i=0;i<RESOLUCION;i++)
        {
            matriz[i][j]=COLOR_NEGRO;
        }
    }
    
    for(i=0;i<RESOLUCION;i+=divisiones_ejes)
    {  /* Este ciclo y el que sigue son para ponerle los puntos de las divisiones,
        como marqué en el primer comentario*/
        matriz[i][2]=COLOR_NEGRO;
        matriz[i][3]=COLOR_NEGRO;
    }
    
    for(j=0;j<RESOLUCION;j+=divisiones_ejes)
    {
        matriz[(RESOLUCION/2)-2][j]=COLOR_NEGRO;   /*Esto de resolucion/2 es para que arranque siempre desde la mitad de la matriz,
                                                    independientemente de la resolución*/
        matriz[(RESOLUCION/2)+2][j]=COLOR_NEGRO;
    }
}

void cargo_matriz(int matriz[][RESOLUCION],float vect_y[])
{
    int i,j,k;float pos;int pos_int;
    float a=RANGO,b=RESOLUCION;
    
    for(i=0;i<RESOLUCION;i++)
    {
        pos=((vect_y[i])+5)  *  (b/a) ; /*Transf lineal*/
        pos_int=(int) pos;	/*Casteo par redondear por defecto*/
        for(j=-1;j<=1;j++)
        {   /*Estos ciclos son para darle el grosor a la linea. Pinta con negro el punto en cuestion,
             y sus ocho pixeles colindantes*/
            for(k=-1;k<=1;k++)
            {
                if(pos_int-k<RESOLUCION)
                    matriz[pos_int+k][i+j]=1;
            }
        }
    }
    
}

void imprimo_matriz(int matriz[][RESOLUCION])
{
    int i,j;
    
    /* Agrego los magic numbers */
    fprintf(stderr,"%s\n","P1");
    
    /* Agrego la resolucion de la matriz */
    fprintf(stderr,"%d %d\n",RESOLUCION,RESOLUCION);
    
    for(i=(RESOLUCION-1);i>=0;i--)     /* La verdad no se bien como justificar esto de imprimir la matriz al reves, pero bueno asi funciona*/
    {
        for(j=0;j<RESOLUCION;j++)
        {
            fprintf(stderr,"%d",matriz[i][j]);
        }
        fputc('\n',stderr);
    }
}

void limpiarbuffer()
{
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

/* Extra funciones para crear un file y luego pisarlo cada vez que se invoca a la opcion de graficar
 mantenemos la redireccion por stderr para cumplir con el tp.
 */

void make_pbm_file( FILE **fp )
{
    *fp=fopen("graph.pbm", "w");
}


void write_pbm_file( FILE **fp, int matriz[RESOLUCION][RESOLUCION], int fil, int col )
{
    int i=0,j=0;
    
    fprintf(*fp,"%s","P1\n");
    fprintf(*fp,"%d %d\n",fil,col);
    
    for (i=(fil-1); i>=0; i--)
    {
        for (j=0; j<col; j++)
        {
            fprintf(*fp,"%d",matriz[i][j]);
        }
        fputc('\n', *fp);
    }
    fputc('\n', *fp);
}


void close_pbm_file( FILE **fp )
{
    fclose(*fp);
}
