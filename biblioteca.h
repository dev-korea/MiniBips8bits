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

struct mem_dados{
    int dado;
};

struct estado_salvo{
    int copia_PC;
    int copia_banco_de_registradores[8];
    struct mem_dados copia_memoria[256];
};


void Carregar_Memoria_Instrucoes(struct instrucao *nome_inst);
void Imprimir_Memorias_Instrucoes(struct instrucao *nome_inst);
void Escrever_Registrador(int *banco_de_registradores,int indice,int valor);
int Ler_Registrador (int *banco_de_registradores,int indice);
void Imprimir_bancoRG(int *banco_de_registradores);
void Carregar_M_Dados(struct mem_dados *d_dado,int *tamanho);
void Imprimir_M_Dados(struct mem_dados *d_dado,int *tamanho);
int Ler_M_Dados(int endereco,struct mem_dados *d_dado);
void Escrever_M_Dados(int endereco, int valor, struct mem_dados *d_dado);
int calculosULA(int *PC, struct instrucao *nome_inst, struct mem_dados *d_dado, int *banco_de_registradores);
int novaULA(struct instrucao  instr, int *banco_de_registradores,struct mem_dados *d_dados);
void Visualizar_Instrucao_Atual(int *PC, struct instrucao *nome_inst);
void Executar_Instrucao(int *PC, struct instrucao *nome_inst, struct mem_dados *d_dado, int *banco_de_registradores);
void Executar_instrucao_novo(int *PC, struct instrucao *nome_inst,struct mem_dados *d_dado, int *banco_de_registradores);
void Salva_Estado(int *PC, struct mem_dados *d_dado,struct estado_salvo *estado,int *banco_de_registradores);
void Retorna_Estado(struct estado_salvo *estado,int *PC, struct mem_dados *d_dado, int *banco_de_registradores);




