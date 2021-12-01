#include <stdio.h>
#include <stdlib.h>
#include "./defines.h"
#include "./IO/IO.h"

#include "./auxiliar/functions.h"



int main(){

    int cmd;
    char *nfile1;
    scanf("%d", &cmd);
    scanf(" %ms",&nfile1);
    FILE *file1 = fopen(nfile1, "r+b");
    if(file1== NULL){
        printf("Falha no processamento do arquivo.\n");
        return 0;}
    char *nfile2;   
    
    switch (cmd)
    {
    case 1:
        scanf(" %ms",&nfile2);
        FILE *file2 = fopen(nfile2, "w+b");
        aplicacao1(file1,file2);
        fclose(file1);
        fclose(file2);
        binarioNaTela(nfile2);        
        
        break;
    
    case 2:
        aplicacao2(file1);
        fclose(file1);
        
        break;

    case 3:
        aplicacao3(file1);
        fclose(file1);
        
        break;

    case 4:
        aplicacao4(file1);
        fclose(file1);
        binarioNaTela(nfile1);
        
        break;

    case 5:
        aplicacao5(file1);
        fclose(file1);
        binarioNaTela(nfile1);
        
        break;

    case 6:
        aplicacao6(file1);
        fclose(file1);
        binarioNaTela(nfile1);
        
        break;
    default:
    	printf("Falha no processamento do arquivo.\n");    	
        

return 0;
}}
