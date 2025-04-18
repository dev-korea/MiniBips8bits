#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "biblioteca.h"


int main(){

    struct instrucao *nome_inst = malloc(256*sizeof(struct instrucao));
    struct mem_dados *d_dado = malloc(256 * sizeof(struct mem_dados));
    struct estado_salvo estado_Anterior;
    
    int op;
    int memoria_instrucoes_carregada = 0;
    int banco_de_registradores[8] = {0};
    int tamanho = 0;
    int PC = 0;
   

    do{
    printf("\nMENU:\n1-Carregar memoria de instrucoes\n2-Carregar Memoria de dados\n3-Imprimir memoria\n4-Imprimir Banco de registradores\n5-Imprimir todo simulador\n6-Visualizar instrucao atual\n7-Executar programa(Step)\n8-Voltar uma instrucao(Back)\n0-Sair\n");
    scanf("%i",&op);

    switch(op){
        case 1: 
            Carregar_Memoria_Instrucoes(nome_inst);
            memoria_instrucoes_carregada = 1;
            break;
        case 2:
            Carregar_M_Dados(d_dado,&tamanho);
            break;
        case 3: 
            if(memoria_instrucoes_carregada == 1){
                printf("****Memoria de Instrucoes:***\n");
                Imprimir_Memorias_Instrucoes(nome_inst);
            } else {
                printf("Memoria de instrucoes nao carregada!\n");
            }
            break;
        case 4: 
            Imprimir_bancoRG(banco_de_registradores);
            break;
        case 5:
            Imprimir_bancoRG(banco_de_registradores);
            if(memoria_instrucoes_carregada == 1){
                printf("**********MEMORIA DE INSTRUCOES**********\n\n");
                Imprimir_Memorias_Instrucoes(nome_inst);
            }
            else{
                printf("Memoria de instrucoes nao carregada!\n");
            }
                printf("********MEMORIA DE DADOS:*********\n");
                Imprimir_M_Dados(d_dado, &tamanho);

                printf("\nPC: %i\n\n\n", PC);    
            break;
        case 6:
            if(memoria_instrucoes_carregada == 1){
                Visualizar_Instrucao_Atual(&PC,nome_inst);
            }else{
                printf("Memoria de instrucoes nao carregada!\n");
            }
            break;

        case 7:
            if(memoria_instrucoes_carregada == 1){
                Salva_Estado(&PC,d_dado,&estado_Anterior,banco_de_registradores);
                Executar_instrucao_novo(&PC, nome_inst,d_dado,banco_de_registradores);
            }else{
                printf("Memoria de instrucoes nao carregada!\n");
            }
            break;

        case 8:
            Retorna_Estado(&estado_Anterior,&PC,d_dado,banco_de_registradores);
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
