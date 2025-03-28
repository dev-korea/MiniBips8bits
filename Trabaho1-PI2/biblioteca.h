#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

struct instrucao{
    char inst_char[17];
    int opcode;
    int rs;
    int rt;
    int rd;
    int funct;
    int imm;
    int addr;
};

void Carregar_Memoria_Instrucoes(struct instrucao *nome_inst);
void Imprimir_Memorias_Instrucoes(struct instrucao *nome_inst);
void Escrever_Registrador(int *banco_de_registradores,int indice,int valor);
int Ler_Registrador (int *banco_de_registradores,int indice);
void Imprimir_bancoRG(int *banco_de_registradores);

#endif

