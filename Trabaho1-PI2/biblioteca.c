#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


void Carregar_Memoria_Instrucoes(struct instrucao *nome_inst){


    char nomepasta[100];
    printf("Digite o nome do aquivo .mem: ");
    scanf("%s",nomepasta);

    FILE *file = fopen(nomepasta,"r");
    if(file == NULL){
        printf("Arquivo nao encontrado\n");
    }
    else{
        printf("Memoria de instrucoes carregada\n");
    }

    // Inicializa todos os 256 opcodes como -1, serve para sinalizar que o espaуo estр vazio, sem instruушes
    for(int i=0;i<256;i++){
        nome_inst[i].opcode = -1;
    }
    int posicao = 0;


    //Linha a linha 
    while(fgets(nome_inst[posicao].inst_char,sizeof(nome_inst[posicao].inst_char),file)){
        //remove caractere de nova linha, se necessario
        nome_inst[posicao].inst_char[strcspn(nome_inst[posicao].inst_char, "\n")] = '\0';

        //separa opcode
        char opcode[5]={0}; //4 bits + 1 para o caractere nulo
        strncpy(opcode,nome_inst[posicao].inst_char,4); 

        unsigned int opcode_num = (unsigned int)strtol(opcode,NULL,2); //Conversão opcode para inteiro ##DUVIDA

        //verificar tipo de instucao
        if(opcode_num == 4){//Tipo ADDI
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode,nome_inst[posicao].inst_char,4);
            strncpy(rs,nome_inst[posicao].inst_char +4,3);
            strncpy(rt,nome_inst[posicao].inst_char +7,3);
            strncpy(imm,nome_inst[posicao].inst_char +10,6);

            //verificar se o valor imediato é positivo
            if(imm[0] == '1'){
                imm[0]='0';
                for(int i=1;i<=5;i++){
                    if(imm[i]=='1'){
                        imm[i]='0';
                    }else{
                        imm[i]='1';
                    }
                }

                nome_inst[posicao].imm = (int)strtol(imm,NULL,2);//Converte para inteiro
                nome_inst[posicao].imm=nome_inst[posicao].imm +1;//add +1 no valor convertido
                nome_inst[posicao].imm = nome_inst[posicao].imm*(-1);//inverter sinal

            }
            else{
                nome_inst[posicao].imm = (int)strtol(imm,NULL,2);//converte para inteiro
            }
            
            //converte os campos para inteiros e armazena na estrutura
            nome_inst[posicao].opcode = (int)strtol(opcode,NULL,2);
            nome_inst[posicao].rs = (int)strtol(rs,NULL,2);
            nome_inst[posicao].rt = (int)strtol(rt,NULL,2);


        } else if(opcode_num == 11){ //Tipo I LW
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode,nome_inst[posicao].inst_char,4);
            strncpy(rs,nome_inst[posicao].inst_char +4,3);
            strncpy(rt,nome_inst[posicao].inst_char +7,3);
            strncpy(imm,nome_inst[posicao].inst_char +10,6);

            nome_inst[posicao].opcode = (int)strtol(opcode,NULL,2);
            nome_inst[posicao].rs = (int)strtol(rs,NULL,2);
            nome_inst[posicao].rt = (int)strtol(rt,NULL,2);
            nome_inst[posicao].imm = (int)strtol(imm,NULL,2);

        }else if(opcode_num == 15){//TIPO I SW
            char opcode[5] = {0};
            char rs[4] = {0};
            char rt[4] = {0};
            char rd[4] = {0};
            char imm[7] = {0};

            strncpy(opcode,nome_inst[posicao].inst_char,4);
            strncpy(rs,nome_inst[posicao].inst_char +4,3);
            strncpy(rt,nome_inst[posicao].inst_char +7,3);
            strncpy(rd,nome_inst[posicao].inst_char +10,3);

            nome_inst[posicao].opcode = (int)strtol(opcode,NULL,2);
            nome_inst[posicao].rs = (int)strtol(rs,NULL,2);
            nome_inst[posicao].rt = (int)strtol(rt,NULL,2);
            nome_inst[posicao].imm = (int)strtol(imm ,NULL,2);

        }else if(opcode_num == 2){//TIPO J
            char opcode[5]={0};
            char addr[8]={0};

            strncpy(opcode,nome_inst[posicao].inst_char,4);
            strncpy(addr,nome_inst[posicao].inst_char +9,7);

            nome_inst[posicao].opcode = (int)strtol(opcode,NULL,2);
            nome_inst[posicao].addr = (int)strtol(addr,NULL,2);

        }else if(opcode_num==0){ //Tipo R
            char opcode[5]={0};
            char rs[4]={0};
            char rt[4]={0};
            char rd[4]={0};
            char funct[4]={0};

            strncpy(opcode,nome_inst[posicao].inst_char,4);
            strncpy(rs,nome_inst[posicao].inst_char +4,3);
            strncpy(rt,nome_inst[posicao].inst_char +7,3);
            strncpy(rd,nome_inst[posicao].inst_char +10,3);
            strncpy(funct,nome_inst[posicao].inst_char +13,3);

            nome_inst[posicao].opcode = (int)strtol(opcode,NULL,2);
            nome_inst[posicao].rs = (int)strtol(rs,NULL,2);
            nome_inst[posicao].rt = (int)strtol(rt,NULL,2);
            nome_inst[posicao].rd = (int)strtol(rd,NULL,2);
            nome_inst[posicao].funct = (int)strtol(funct,NULL,2);


        }else{
            printf("Tipo de instrucao nao identificada\n");
        }
        posicao ++;

        if(posicao>=256){
            printf("Limite maximo de instrucoes atingido\n");
            break;
        }

        fclose(file);


    }


}


void Imprimir_Memorias_Instrucoes(struct instrucao *nome_inst){

    for(int i=0;i<256;i++){
        if(nome_inst[i].opcode == -1){
        }
        else if(nome_inst[i].opcode == 0){
            printf("Tipo R - opcode: %i, rs: %i, rt:%i, rd:%i, funct: %i\n",nome_inst[i].opcode, nome_inst[i].rs,nome_inst[i].rt,nome_inst[i].rd,nome_inst[i].funct);
        }
        else if(nome_inst[i].opcode == 2){
            printf("Tipo J - opcode: %i,addr:%i\n",nome_inst[i].opcode,nome_inst[i].addr);
        }
        else if(nome_inst[i].opcode == 15){
            printf("Tipo SW - opcode: %i, rs: %i, rt: %i, imm:%i\n",nome_inst[i].opcode,nome_inst[i].rs,nome_inst[i].rt,nome_inst[i].imm);
        }
        else if(nome_inst[i].opcode==11){
            printf("Tipo LW - opcode: %i,rs: %i, rt: %i, imm: %i\n",nome_inst[i].opcode, nome_inst[i].rs,nome_inst[i].rt,nome_inst[i].imm);
        }
        else if(nome_inst[i].opcode == 4){
            printf("Tipo LW opcode: %i, rs: %i, rt: %i, imm: %i\n",nome_inst[i].opcode,nome_inst[i].rs,nome_inst[i].rt,nome_inst[i].imm);
        }
        else{
            printf("Tipo de instrucao nao identificada\n");
        }
    }
    printf("\n");
}


void Escrever_Registrador(int *banco_de_registradores,int indice,int valor){
    if(indice >= 0 && indice <8){
        banco_de_registradores[indice] = valor;
    }
    else{
        printf("Indice de registrador invalido\n");
    }
}

int Ler_Registrador (int *banco_de_registradores,int indice){
    if(indice >=0 && indice<8){
        return banco_de_registradores[indice];
    }
    else{
        printf("Indice de tegistrador nao encontrado\n");
    }
}

void Imprimir_bancoRG(int *banco_de_registradores){
    printf("**********BANCO DE REGISTRADORES***********\n\n");
    for(int i=0;i<8;i++){
        printf("RG[%i] = %i\n", i, banco_de_registradores[i]);
    }
    printf("\n");
}