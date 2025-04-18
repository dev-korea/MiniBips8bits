#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
        //caractere nulo
        nome_inst[posicao].inst_char[strcspn(nome_inst[posicao].inst_char, "\n")] = '\0';


        if(strlen(nome_inst[posicao].inst_char)!=16){
            continue;
        }

        //separa opcode
        char opcode[5]={0}; //4 bits + 1 para o caractere nulo
        strncpy(opcode,nome_inst[posicao].inst_char,4); 

        unsigned int opcode_num = (unsigned int)strtol(opcode,NULL,2); //Conversão opcode para inteiro ##DUVIDA

        //verificar tipo de instucao
        if(opcode_num == 11){ //Tipo I LW
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
            strncpy(imm, nome_inst[posicao].inst_char + 10, 6);

            nome_inst[posicao].opcode = (int)strtol(opcode,NULL,2);
            nome_inst[posicao].rs = (int)strtol(rs,NULL,2);
            nome_inst[posicao].rt = (int)strtol(rt,NULL,2);
            nome_inst[posicao].imm = (int)strtol(imm ,NULL,2);

        
        }
        else if (opcode_num == 8) {
            // Instruусo tipo I (BEQ)
            char opcode[5] = {0};// 4 bits + 1 para nulo
            char rs[4] = {0};
            char rt[4] = {0};
            char imm[7] = {0};

            strncpy(opcode, nome_inst[posicao].inst_char, 4);
            strncpy(rs, nome_inst[posicao].inst_char + 4, 3);
            strncpy(rt, nome_inst[posicao].inst_char + 7, 3);
            strncpy(imm, nome_inst[posicao].inst_char + 10, 6);

        //Verificar se o valor do imm ж positivo ou negativo, se for negativo, desfazer a operaусo de complemento de 2.
        if (imm[0] == '1'){ // Se for 1 ж negativo, invertemos os bits.
            imm[0] = '0';
            for(int i=1; i<=5; i++){
                if(imm[i] == '1'){
                    imm[i] = '0';
                }else{
                    imm[i] = '1';
                }
            }
            nome_inst[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
            nome_inst[posicao].imm = nome_inst[posicao].imm +1; //add +1 no valor convertido
            nome_inst[posicao].imm = nome_inst[posicao].imm*(-1); //inverte o sinal
        }

        else{
            nome_inst[posicao].imm = (int)strtol(imm, NULL, 2); //converte p/ inteiro
        }

            // Converte os campos para inteiros e armazena na estrutura
            nome_inst[posicao].opcode = (int)strtol(opcode, NULL, 2);
            nome_inst[posicao].rs = (int)strtol(rs, NULL, 2);
            nome_inst[posicao].rt = (int)strtol(rt, NULL, 2);

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


        }
        
        
        
        else if(opcode_num == 4){//Tipo ADDI
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

             }
        else{
            printf("Tipo de instrucao nao identificada. Opcode %i\n",opcode_num);
        }
        posicao ++;

        if(posicao>=256){
            printf("Limite maximo de instrucoes atingido\n");
            break;
        }

    }
    fclose(file);

}


void Imprimir_Memorias_Instrucoes(struct instrucao *nome_inst){

    for(int i=0;i<256;i++){
        if(nome_inst[i].opcode == -1){
            continue;
        }
        else if(nome_inst[i].opcode == 0){
            printf("Tipo R - opcode: %i, rs: %i, rt:%i, rd:%i, funct: %i\n\n",nome_inst[i].opcode, nome_inst[i].rs,nome_inst[i].rt,nome_inst[i].rd,nome_inst[i].funct);
        }
        else if(nome_inst[i].opcode == 2){
            printf("Tipo J - opcode: %i, addr: %i\n\n",nome_inst[i].opcode,nome_inst[i].addr);
        }
        else if(nome_inst[i].opcode == 15){
            printf("Tipo I SW - opcode: %i, rs: %i, rt: %i, imm:%i\n\n",nome_inst[i].opcode,nome_inst[i].rs,nome_inst[i].rt,nome_inst[i].imm);
        }
        else if(nome_inst[i].opcode==11){
            printf("Tipo I LW - opcode: %i,rs: %i, rt: %i, imm: %i\n\n",nome_inst[i].opcode, nome_inst[i].rs,nome_inst[i].rt,nome_inst[i].imm);
        }
        else if(nome_inst[i].opcode == 4){
            printf("Tipo I ADDI opcode: %i, rs: %i, rt: %i, imm: %i\n\n",nome_inst[i].opcode,nome_inst[i].rs,nome_inst[i].rt,nome_inst[i].imm);
        }
        else if(nome_inst[i].opcode == 8) {
            printf("Tipo BEQ - opcode: %d, rs: %d, rt: %d, imm: %d\n\n", nome_inst[i].opcode, nome_inst[i].rs, nome_inst[i].rt, nome_inst[i].imm);
        }
        else{
            printf("Tipo de instrucao nao identificada\n");
        }
    }
    printf("\n");
}

void Carregar_M_Dados(struct mem_dados *d_dado,int *tamanho){
    char nomepasta[100];
    printf("Digite o nome do arquivo .dat: ");
    scanf("%s",nomepasta);
    printf("\n");

    FILE *arquivo = fopen(nomepasta,"r");
    if(arquivo == NULL){
        printf("Arquivo nao encontrado\n");
    }
    else{
        printf("Memoria de dados carregada\n");
    }
    *tamanho = 0;

    while(fscanf(arquivo,"%i",&d_dado[*tamanho].dado) != EOF && *tamanho < 256){
        (*tamanho)++;
    }
    fclose(arquivo);

}

void Imprimir_M_Dados(struct mem_dados *d_dado,int *tamanho){
    for(int x = 0;x<16;x++){
        for(int y=0;y<16;y++){
            int mem = x*16+y;
            if(mem < *tamanho){
                printf("Mem[%i] %i\t",mem, d_dado[mem].dado);
            }
        }
        printf("\n");
    }
}

int Ler_M_Dados(int endereco,struct mem_dados *d_dado){
    if(endereco<0 || endereco>=256){
        printf("Endereco invalido\n");
    }
    return d_dado[endereco].dado;
}


void Escrever_M_Dados(int endereco, int valor, struct mem_dados *d_dado){
    if(endereco<0 || endereco>=256){
        printf("Endereco invalido\n");
    }
    d_dado[endereco].dado = valor;
}


void Imprimir_bancoRG(int *banco_de_registradores){
    printf("**********BANCO DE REGISTRADORES***********\n\n");
    for(int i=0;i<8;i++){
        printf("RG[%i] = %i\n", i, banco_de_registradores[i]);
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
        printf("Indice de registrador nao encontrado\n");
        return -1; 
    }
}


int novaULA(struct instrucao  instr, int *banco_de_registradores,struct mem_dados *d_dados){
    int resultado = 0;
    int val_rs = Ler_Registrador(banco_de_registradores, instr.rs);
    int val_rt = Ler_Registrador(banco_de_registradores, instr.rt);

    switch(instr.opcode){
        case 0://tipo R
            switch(instr.funct){
                case 0:
                    resultado = val_rs + val_rt;//add
                    break;
                case 2: 
                    resultado = val_rs - val_rt;//sub
                    break;
                case 4:
                    resultado=val_rs & val_rt;//and
                    break;
                case 5:
                    resultado = val_rs | val_rt;//or
                    break;
                default:
                    printf("Funcao tipo R invalida\n");
                    return 0;
            }
            Escrever_Registrador(banco_de_registradores, instr.rd,resultado);
            break;

        case 4://addi
            resultado = val_rs + instr.imm;
            Escrever_Registrador(banco_de_registradores, instr.rt,resultado);
            break;

        case 11://lw
            resultado = val_rs + instr.imm;
            if(resultado>=0 && resultado <256){
                Escrever_Registrador(banco_de_registradores, instr.rt,Ler_M_Dados(resultado,d_dados));
            }else{
                printf("Endereco de memoria invalido\n");
            }
            break;
        
        case 15://sw
            resultado = val_rs + instr.imm;
            if(resultado>=0 && resultado <256){
                //Escrever_M_Dados(resultado, instr.rt, d_dados);
                Escrever_M_Dados(resultado, Ler_Registrador(banco_de_registradores, instr.rt), d_dados);
            }else{
                printf("Endereco de memoria invalido\n");
            }
            break;
        default:
            printf("Opcode não suportado na ULA\n");
            break;


    }

    return resultado;
}



void Executar_instrucao_novo(int *PC, struct instrucao *nome_inst,struct mem_dados *d_dado, int *banco_de_registradores){
    Visualizar_Instrucao_Atual(PC,nome_inst);
    struct instrucao inst = nome_inst[*PC];

    if(inst.opcode == -1){ 
        printf("PC apontando para um campo vazio\n");
        return;
    }
    if(inst.opcode == 2){ //Jump
        printf("Instrucao tipo J - Salto\n");
        *PC = inst.addr;
        return;
    }
    if(inst.opcode == 8){ //beq
        int val_rs = Ler_Registrador(banco_de_registradores,inst.rs);
        int val_rt = Ler_Registrador(banco_de_registradores,inst.rt);

        if(val_rs ==val_rt){
            printf("BEQ verdadeiro, pulando %d\n",inst.imm);
            *PC +=inst.imm;
        }else{
            printf("BEQ falso, prosseguindo\n");
            (*PC)++;
        }

    return;

    }

    int resultado = novaULA(inst,banco_de_registradores,d_dado);
    printf("Resultado ULA: %i\n",resultado);
    (*PC)++;


}











int calculosULA(int *PC, struct instrucao *nome_inst, struct mem_dados *d_dado, int *banco_de_registradores){
    int resultado= 0;
//tipo R
if(nome_inst[*PC].opcode==0){
    switch(nome_inst[*PC].funct){
        case 0:         //soma
            resultado = Ler_Registrador(banco_de_registradores, nome_inst[*PC].rs) + Ler_Registrador(banco_de_registradores,nome_inst[*PC].rt);
            if(resultado>127 || resultado<-128){
            printf("\noverflow !!!. a quantidade de armazenamento foi saturada\n");
            }
             else{
                Escrever_Registrador(banco_de_registradores, nome_inst[*PC].rd, resultado);
            }
        break;
        case 2:     //subtração
        resultado=Ler_Registrador(banco_de_registradores, nome_inst[*PC].rs) - Ler_Registrador(banco_de_registradores, nome_inst[*PC].rt);
        if(resultado>127 || resultado<-128){
            printf("\noverflow !!!. a quantidade de armazenamento foi saturada\n");
        }else{
            Escrever_Registrador(banco_de_registradores, nome_inst[*PC].rd, resultado);
        }
        break;
        case 4:      //and
            resultado=Ler_Registrador(banco_de_registradores, nome_inst[*PC].rs) & Ler_Registrador(banco_de_registradores, nome_inst[*PC].rt);
            if(resultado>127|| resultado<-128){
                printf("\noverflow!!!. a quantidade de armazenamento foi saturada\n");
            }else{
                Escrever_Registrador(banco_de_registradores, nome_inst[*PC].rd, resultado);
            }
            case 5:     //or
            resultado=Ler_Registrador(banco_de_registradores, nome_inst[*PC].rs) | Ler_Registrador(banco_de_registradores, nome_inst[*PC].rt);
            if(resultado>127|| resultado<-128){
                printf("\noverflow!!!. a quantidade de armazenamento foi saturada\n");
            }else{
                Escrever_Registrador(banco_de_registradores, nome_inst[*PC].rd, resultado);
            }
        }
       
}
else if(nome_inst[*PC].opcode==4){      //tipo I addi
        resultado=Ler_Registrador(banco_de_registradores, nome_inst[*PC]. rs) + nome_inst[*PC].imm;     //soma o valor que esta no registrador RS com um valor imediato que está na instrução (pode ser um valor negativo)
        if(resultado>127|| resultado<-128){
            printf("\noverflow!!!. a quantidade de armazenamento foi saturada\n");
        }else{
            Escrever_Registrador(banco_de_registradores, nome_inst[*PC].rt, resultado); //registrador destino nessa instrução é o RT
        }
}
else if(nome_inst[*PC].opcode== 8){     //tipo I beq
    if(Ler_Registrador(banco_de_registradores, nome_inst[*PC].rs) == Ler_Registrador(banco_de_registradores,nome_inst[*PC].rt )){     //verifica se os valores dentro dos 2 registradores operandos são iguais
            printf("\n\na instruçao gerou valor de resultado.\n\n");
            *PC+=nome_inst[*PC].imm;    //se forem iguais o pc é atualizado com um novo valor
    } 
    else{
        printf("\n\n instrucao nao gerou valor de resultado\n\n");
        (*PC)++;
    }
}
else if(nome_inst[*PC].opcode==11){ //tipo I lw
        resultado=Ler_Registrador(banco_de_registradores,nome_inst[*PC].rs)+ nome_inst[*PC].imm;        //endereço= RS + IMM.
    if(resultado < 0 || resultado > 255){
        printf("\tEndereço de memoria invalido!\n");
    }else{
        Escrever_Registrador(banco_de_registradores, nome_inst[*PC].rt, Ler_M_Dados(resultado, d_dado));      // armazena no registrador
}
}
else if(nome_inst[*PC].opcode == 15){//Tipo I SW
    resultado = Ler_Registrador(banco_de_registradores, nome_inst[*PC].rs) + nome_inst[*PC].imm;                // endere�o = rs + imm. L� da mem�ria e armazena no registrador
    if(resultado < 0 || resultado > 255){
        printf("\nEndereco de memoria invalido!\n");
    }else{
    Escrever_M_Dados(resultado, Ler_Registrador(banco_de_registradores, nome_inst[*PC].rt), d_dado);      // Armazena na mem�ria de dados
    }

}
return resultado;
}


void Visualizar_Instrucao_Atual(int *PC, struct instrucao *nome_inst){

    printf("====================INSTRUCAO ATUAL====================\n\n");
        if(nome_inst[*PC].opcode == 0){
            if(nome_inst[*PC].funct == 0){
                printf("\nADD $t%d, $t%d, $t%d\n", nome_inst[*PC].rd, nome_inst[*PC].rs, nome_inst[*PC].rt);
            }
            else if(nome_inst[*PC].funct == 2){
                printf("\nSUB $t%d, $t%d, $t%d\n", nome_inst[*PC].rd, nome_inst[*PC].rs, nome_inst[*PC].rt);
            }
            else if(nome_inst[*PC].funct == 4){
                printf("\nAND $t%d, $t%d, $t%d\n", nome_inst[*PC].rd, nome_inst[*PC].rs, nome_inst[*PC].rt);
            }
            else if(nome_inst[*PC].funct == 5){
                printf("\nOR $t%d, $t%d, $t%d\n", nome_inst[*PC].rd, nome_inst[*PC].rs, nome_inst[*PC].rt);
            }
        }
        else if(nome_inst[*PC].opcode == 4){
                printf("\nADDI $t%d, $t%d, %d\n", nome_inst[*PC].rt, nome_inst[*PC].rs, nome_inst[*PC].imm);
        }else if(nome_inst[*PC].opcode == 11){
                printf("\nLW $t%d, %d($t%d)\n", nome_inst[*PC].rt,nome_inst[*PC].imm, nome_inst[*PC].rs);
        }else if(nome_inst[*PC].opcode == 15){
                printf("\nSW $t%d, %d($t%d)\n", nome_inst[*PC].rt, nome_inst[*PC].imm, nome_inst[*PC].rs);
        }else if(nome_inst[*PC].opcode == 8){
                printf("\nBEQ $t%d, $t%d, %d\n", nome_inst[*PC].rs, nome_inst[*PC].rt, nome_inst[*PC].imm);
        }else if(nome_inst[*PC].opcode == 2){
                printf("\nJ %d\n", nome_inst[*PC].addr);
        }
    printf("\n");
}


void Executar_Instrucao(int *PC, struct instrucao *nome_inst, struct mem_dados *d_dado, int *banco_de_registradores) {   //Executa as instruções

    Visualizar_Instrucao_Atual(PC, nome_inst);

    if(nome_inst[*PC].opcode == 2) {
         printf("\nInstrução não gerou valor de resultado.\n\n");
        *PC = nome_inst[*PC].addr;                                                     //realiza as do tipo J, alterando diretamente o PC
    }
    else if(nome_inst[*PC].opcode == -1) {                                            // se o opcode estiver como -1, indica que nao tem mais instruções válidas
            printf("\nPC está apontando para um campo vazio!\n\n");
    }
    else if(nome_inst[*PC].opcode != 8){
            int resultado = calculosULA(PC, nome_inst, d_dado, banco_de_registradores);                    // chama a função da ula que verifica o opcode e executa a operação
            printf("\nResultado da ULA: %d\n\n", resultado);
            (*PC)++;
        }else{
            calculosULA(PC, nome_inst, d_dado, banco_de_registradores);
        }
}




void Salva_Estado(int *PC, struct mem_dados *d_dado,struct estado_salvo *estado,int *banco_de_registradores){
    estado->copia_PC = *PC;//salva pc
    for(int i = 0;i<8;i++){//salva registradores
        estado->copia_banco_de_registradores[i]=banco_de_registradores[i];
    }

    for(int i=0;i<256;i++){
        estado->copia_memoria[i]=d_dado[i];
    }

}

void Retorna_Estado(struct estado_salvo *estado,int *PC, struct mem_dados *d_dado, int *banco_de_registradores){
    *PC = estado->copia_PC;//restaura pc

    for(int i=0;i<8;i++){
        banco_de_registradores[i]=estado->copia_banco_de_registradores[i];
    }

    for(int i=0;i<256;i++){
        d_dado[i]=estado->copia_memoria[i];
    }
    printf("Estado retornado com sucesso\n");
}









