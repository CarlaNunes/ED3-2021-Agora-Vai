#ifndef _defines_
#define _defines_

#define trash "$"

typedef struct{
    char status;
    long int topoLista;
    int nroEstacoes;
    int nroParesEstacao;
} Cabecalho;

typedef struct{

    char removido;
    int tamanhoRegistro;
    long int proxLista;


    int codEstacao;
    //nomeEstacao :na ordem csv
    int codLinha;
    //nomeLinha :na ordem csv
    int codProxEstacao;
    int distProxEstacao;
    int codLinhaIntegra;
    int codEstIntegra;

    char nomeEstacao[40];
    char nomeLinha[40];

} Dados;

/*Início Trabalho 2*/
typedef struct noh Noh;
typedef struct grafo *Grafo;

struct noh{
    char origem[40]; //Origem;
    char destino[40]; //Posição do vértice corrente
    int peso; //Peso
    Noh *prox; //Aponta para proximo noh
};

struct grafo{
    struct noh **A; //Vetor de nós (cada posicao do vetor aponta para uma lista ligada)
    int n; //Número de vertices
    int m; //Número de arestas
};

#endif