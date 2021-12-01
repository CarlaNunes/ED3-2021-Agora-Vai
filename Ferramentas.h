#ifndef _FE_METRO_
#define _FE_METRO_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <limits.h>
#include "../defines.h"


void getstr(FILE* file1,char* string);
int getint(int* p,FILE* file );
void insereg(FILE* file,Dados* d,int flag);
void limpad(Dados* d);
int pegaRegistro(Dados* d,FILE* file);
void imprimeRegistro(Dados* d);
void restrinja(Dados* d);
void generalize(Dados* d);
int compativel(Dados* r,Dados* d);
void firstfit(FILE* file,Dados* d,long int* topolista);
int intteclado(FILE* file);
void atualiza_ca(FILE* file,Cabecalho* pca);
Grafo inicializaGrafo(int n);
void insereArcoGrafo(Grafo G, int i, int j, int peso);
void liberaGrafo(Grafo G);
void ordenacaoTopologica(Grafo G, int *ordenado);
void dijkstra(Grafo G, int src);
void depthfsRec(Grafo G, int v, int *ref_rotulo, int *visitado, int *ordenado);

#endif