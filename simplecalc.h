/*
  simplecalc.h
  Tp3
*/


#ifndef __Tp3__simplecalc__
#define __Tp3__simplecalc__

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


#define MENU "\n\t CALCULADORA \n\n\n 1_Suma\n 2_Resta\n 3_Multiplicación \n 4_División\n 5_Pontencia con Exponente Entero\n 6_Factorial\n 7_Núm. Combinatorio\n 8_ Núm. Aleatorio\n 9_Graficadora de Funciones\n\n"
#define MENU_GRAF "\n\n\tSeleccione la función a graficar\n\n\n Trigonometricas\n\n   1_Seno\n   2_Coseno\n\n\n Polinomicas\n\n   3_Grado 0\n   4_Grado 1\n   5_Grado 2\n   6_Grado 3\n\n\n Especiales\n\n   7_Logaritmica Natural\n   8_Exponencial\n\n"
#define CLS "clear"
#define RESOLUCION 600
#define RANGO 10
#define COLOR_NEGRO 1
#define COLOR_BLANCO 0
#define MAX_CHAR 255

typedef enum {SUMA=1,RESTA,MULT,DIVISION,POT,FACT,COMBIN,ALEATORIO,GRAFICO,NOOPERATION} opt_t;



float potencia(float base, int exponente);
unsigned long factorial(int in_facto);
int combinatorio(int comb1, int comb2);
float aleatorio(float min, float max);
void opcion(opt_t opt);
void ingreso_val(void);
void suma_simplecalc(void);
void resta_simplecalc(void);
void multiplicacion_simplecalc(void);
void division(void);
void dialogo_pot(void);
void dialogo_fact(void);
void dialogo_comb(void);
void dialogo_alea(void);
void menu_graf(void);
void cargo_x (float vect_x[RESOLUCION]);
float pido_parametro_a(void);
float pido_parametro_b(void);
float pido_parametro_c(void);
float pido_parametro_d(void);
void seno(float vect_x[],float vect_y[]);
void coseno(float vect_x[],float vect_y[]);
void pol0(float vect_x[],float vect_y[]);
void pol1(float vect_x[],float vect_y[]);
void pol2(float vect_x[],float vect_y[]);
void pol3(float vect_x[],float vect_y[]);
void ln(float vect_x[],float vect_y[]);
void expo(float vect_x[],float vect_y[]);
void inicializo_matriz(int matriz[][RESOLUCION]);
void inicializo_ejes(int matriz[][RESOLUCION]);
void cargo_matriz(int matriz[][RESOLUCION],float vect_y[]);
void imprimo_matriz(int matriz[][RESOLUCION]);
void make_pbm_file(FILE **);
void write_pbm_file(FILE **,int matriz[RESOLUCION][RESOLUCION],int,int);
void close_pbm_file(FILE **);
void limpiarbuffer(void);


#endif /* defined(__Tp3__simplecalc__) */
