#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"
#include "../auxiliar/functions.h"
#include "../Ferramentas/Ferramentas.h"




void aplicacao1(FILE* file1,FILE* file2){
    fseek(file1,101,SEEK_SET);//posicao em que comeca as iformacoes que serao lidas
    Dados* d = (Dados*) malloc(sizeof(Dados));// d armazena o registro q sera lido e armazenado
    d->removido='0';
    d->proxLista=-1;
    limpad(d);
    Cabecalho ca; 
    ca.status='0';
    ca.topoLista=-1;
    ca.nroEstacoes=0;
    ca.nroParesEstacao=0;
    fwrite(&(ca.status),sizeof(char),1,file2); //criando o cabecalho do arquivo
    fwrite(&(ca.topoLista),sizeof(long int),1,file2);
    fwrite(&(ca.nroEstacoes),sizeof(int),1,file2);
    fwrite(&(ca.nroParesEstacao),sizeof(int),1,file2);
    char c;// carac. que eh usado para pegar o \n
    while(getint(&(d->codEstacao),file1)==1){// enquanto tiver leitura
        getstr(file1,d->nomeEstacao);
        getint(&(d->codLinha),file1);
        getstr(file1,d->nomeLinha);
        getint(&(d->codProxEstacao),file1);
        getint(&(d->distProxEstacao),file1);
        getint(&(d->codLinhaIntegra),file1);
        getint(&(d->codEstIntegra),file1);
        fread(&c,sizeof(char),1,file1);// pega o \n
        insereg(file2,d,1);//insere registro sem limitacao de espaco
        limpad(d);}
 
    ca.status='1';
    atualiza_ca(file2,&ca);
    free(d);}


void aplicacao2(FILE* file){
    fseek(file,17,SEEK_SET);
    Dados* d = (Dados*) malloc(sizeof(Dados));
    int flag=1;
    int status;
    while((status=pegaRegistro(d,file))!=0){
        if(status==-1) continue;//registro removido
        flag=0;//Algum registro valido foi lido
        imprimeRegistro(d);}
    free(d);
    if(flag==1)printf("Registro inexistente.\n");}


void aplicacao3(FILE* file){
    int n;
    scanf("%i\n",&n);
    Dados* d = (Dados*) malloc(sizeof(Dados));// dados que serao buscados
    Dados* r = (Dados*) malloc(sizeof(Dados));// registros que serao lidos
    generalize(d);
    
    for(int i=0;i<n;i++) restrinja(d); // executa n restricoes
    int status=0;
    int flag=1;
    fseek(file,17,SEEK_SET);
    while((status=pegaRegistro(r,file))!=0){
        if (status==-1 || compativel(r,d)!=1) continue; //registro removido ou invalido     
        flag=0;//Algum registro valido foi lido
        imprimeRegistro(r);}

free(d);
free(r);
if(flag==1)printf("Registro inexistente.\n"); 
}


void aplicacao4(FILE* file){
    int n;
    int x;
    scanf("%i\n",&n);
    Dados* d = (Dados*) malloc(sizeof(Dados));
    Dados* r = (Dados*) malloc(sizeof(Dados));
    Cabecalho ca;
    fread(&(ca.status),sizeof(char),1,file);//leitura do cabecalho
    fread(&(ca.topoLista),sizeof(long int),1,file);
    fread(&(ca.nroEstacoes),sizeof(int),1,file);
    fread(&(ca.nroParesEstacao),sizeof(int),1,file);
    
    for(int i=0;i<n;i++){
        if(i>0) fseek(file,17,SEEK_SET);//volta ao inicio dos registros
        generalize(d);
        scanf("%i ",&x);
        for(int j=0;j<x;j++) restrinja(d);// executa x restricoes
        int status;
        while((status=pegaRegistro(r,file))!=0){
            if (status==-1 || compativel(r,d)!=1) continue; //registro removido ou invalido   
            r->removido='1';
            r->proxLista=ca.topoLista;//botando r no topo da lista
            ca.topoLista = ftell(file)-r->tamanhoRegistro -5;//bts atual - tamanho registro -(int do campo do tamanho)- char do removido
            fseek(file,ca.topoLista,SEEK_SET);
            fwrite(&(r->removido),sizeof(char),1,file);
            fwrite(&(r->tamanhoRegistro),sizeof(int),1,file);
            fwrite(&(r->proxLista),sizeof(long int),1,file);
            fseek(file,r->tamanhoRegistro-8,SEEK_CUR);//vai para o final do registro
            }}
    free(d);
    free(r);
    atualiza_ca(file,&ca);}

void aplicacao5(FILE* file){
    int n;
    scanf("%i\n",&n);
    Cabecalho ca;
    fread(&(ca.status),sizeof(char),1,file);
    fread(&(ca.topoLista),sizeof(long int),1,file);
    fread(&(ca.nroEstacoes),sizeof(int),1,file);
    fread(&(ca.nroParesEstacao),sizeof(int),1,file);
    Dados* d = (Dados*) malloc(sizeof(Dados));
    d->removido='0';
    d->proxLista=-1;
    for(int i=0;i<n;i++) {//pega todos os dados do teclado n vezes
    d->codEstacao=intteclado(file);
    scan_quote_string(d->nomeEstacao);
    d->codLinha=intteclado(file);
    scan_quote_string(d->nomeLinha);
    d->tamanhoRegistro=34+ strlen(d->nomeEstacao) + strlen(d->nomeLinha);// 32 + 2*| + as strings
    d->codProxEstacao=intteclado(file);
    d->distProxEstacao=intteclado(file);
    d->codLinhaIntegra=intteclado(file);
    d->codEstIntegra=intteclado(file);
    if(i!=n-1) while(getchar()!='\n');// Se n for a ultima linha fica esperando o \n
    firstfit(file,d,&(ca.topoLista));}
    atualiza_ca(file,&ca);    
    free(d);}


void aplicacao6(FILE* file){
    int n;
    int x;
    int y;
    scanf("%i\n",&n);
    Cabecalho ca;
    fread(&(ca.status),sizeof(char),1,file);
    fread(&(ca.topoLista),sizeof(long int),1,file);
    fread(&(ca.nroEstacoes),sizeof(int),1,file);
    fread(&(ca.nroParesEstacao),sizeof(int),1,file);
    Dados* buscado = (Dados*) malloc(sizeof(Dados));//dados buscados
    Dados* atualizado = (Dados*) malloc(sizeof(Dados));//dados que serao atualizadas
    Dados* r = (Dados*) malloc(sizeof(Dados));//registro que sera lido e possivelmente atualizado
    for(int i=0;i<n;i++) {
        if(i>0) fseek(file,17,SEEK_SET);//volta ao inicio dos registros
        generalize(buscado);
        scanf("%i ",&x);
        for(int j=0;j<x;j++) restrinja(buscado);
        generalize(atualizado);
        scanf("%i ",&y);
        for(int j=0;j<y;j++) restrinja(atualizado);
        int status;
        while((status=pegaRegistro(r,file))!=0){
            if (status==-1) continue;
            if (compativel(r,buscado)!=1) continue;// r tem que ser compatil com o que eh buscado
            if(atualizado->codEstacao!=-2) r->codEstacao=atualizado->codEstacao;// se tiver restricao no atualizado ,entao atualiza o r
            if(atualizado->codLinha!=-2) r->codLinha=atualizado->codLinha;// analogamente
            if(atualizado->codProxEstacao!=-2) r->codProxEstacao=atualizado->codProxEstacao;
            if(atualizado->distProxEstacao!=-2) r->distProxEstacao=atualizado->distProxEstacao;
            if(atualizado->codLinhaIntegra!=-2) r->codLinhaIntegra= atualizado->codLinhaIntegra;
            if(atualizado->codEstIntegra!=-2) r->codEstIntegra=atualizado->codEstIntegra;
            if(strcmp(atualizado->nomeEstacao,"Sem restrição")!=0) strcpy(r->nomeEstacao,atualizado->nomeEstacao);
            if(strcmp(atualizado->nomeLinha,"Sem restrição")!=0) strcpy(r->nomeLinha,atualizado->nomeLinha);
            int tamanho_atualizado= 34+ strlen(r->nomeEstacao)+ strlen(r->nomeLinha);
            if(tamanho_atualizado<=r->tamanhoRegistro){//cabe nesse registro a atualizacao
                fseek(file,-r->tamanhoRegistro-5,SEEK_CUR);//volta ao inicio do registro
                insereg(file,r,0);}             
            else{//nao cabe nesse
                r->removido='1';//marca como removido
                r->proxLista=ca.topoLista;//poe no topo da lista
                long int fim_regis=ftell(file);
                ca.topoLista = fim_regis-r->tamanhoRegistro -5;
                fseek(file,ca.topoLista,SEEK_SET);
                fwrite(&(r->removido),sizeof(char),1,file);
                fwrite(&(r->tamanhoRegistro),sizeof(int),1,file);
                fwrite(&(r->proxLista),sizeof(long int),1,file);
                r->removido='0';
                r->proxLista=-1;
                r->tamanhoRegistro=tamanho_atualizado;
                firstfit(file,r,&(ca.topoLista));
                fseek(file,fim_regis,SEEK_SET);}}}
    free(buscado);
    free(atualizado);
    free(r);
    atualiza_ca(file,&ca);}

void aplicacao7(FILE* file){


} 

void aplicacao8(FILE* file){

}    

void aplicacao9(FILE* file){

}

void aplicacao10(FILE* file){

}

void aplicacao11(FILE* file){

}