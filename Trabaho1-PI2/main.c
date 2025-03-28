#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "biblioteca.h"
#include "biblioteca.c"

int main(){

    struct instrucao *nome_inst = malloc(256*sizeof(struct instrucao));
    
    int op;
    int memoria_instrucoes_carregada = 0;
    int banco_de_registradores[8] = {0};


    do{
    printf("\nMENU:\n1-Carregar memoria de instrucoes\n2-Imprimir memoria\n3-Imprimir Banco de registradores\n0-Sair\n");
    scanf("%i",&op);

    switch(op){
        case 1: 
            Carregar_Memoria_Instrucoes(nome_inst);
            memoria_instrucoes_carregada = 1;
            break;
        case 2: 
            if(memoria_instrucoes_carregada == 1){
                printf("*********Memoria de Instrucoes:**********\n");
                Imprimir_Memorias_Instrucoes(nome_inst);
            } else {
                printf("Memoria de instrucoes nao carregada!\n");
            }
            break;
        case 3: 
            Imprimir_bancoRG(banco_de_registradores);
            break;
        case 0: 
            printf("Encerrando programa\n");
            break;
        default:
            printf("Comando inválido, tente novamente\n");
            break;

        }
    }while(op!=0);

free(nome_inst);

return 0;
}