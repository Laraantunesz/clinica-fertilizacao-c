#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#define espaco_livre 5
// prototipos das funções e stucts

typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct{
    char nome[50];
    char cpf[12]; // Agora é CPF (texto), não ID
    int idade;
    char sexo;
    char sangue[4];
} Doador;

typedef struct{
    char nome[50];
    char cpf[12];
    int idade;
    char sexo;
} Paciente;

typedef struct{
    int codigo;
    int status;
    char cpf_doador[12];   // MUDOU: Guarda o CPF do doador
    char cpf_paciente[12];
    Data data_procedimento;
} Doacao;

//MENUS
int menuPrincipal();
int subMenu() ;
int menuListas();

//BUSCAS
int buscarPaciente(Paciente *vetor, int quant, char *cpf);
int buscarDoador(Doador *vetor, int quant, char *cpf);
int buscarDoacao(Doacao *vetor, int quant, int codigo);

// CADASTROS
void cadastrarDoador(Doador **vetor, int *qtd,int *capacidade,Paciente *vPaciente,int qtdPaciente);
void cadastrarPaciente(Paciente **vetor, int *qtd,int *capacidade,Doador *vDoador,int qtdDoador);
void cadastrarDoacao(Doacao **vDoacao, int *qtdDoacao, Doador *vDoador, int qtdDoador, Paciente *vPaciente, int qtdPaciente,int *capacidade);

// UPDATES
int updateDoador(Doacao *vetorDoacao, int qtdDoacao, Doador *vetorDoador, int qtdDoador);
int updatePaciente(Doacao *vetorDoacao, int qtdDoacao, Paciente *vetorPaciente, int quant);
int updateDoacao(Doacao *vetorDoacao, int qtdDoacao, Doador *vetorDoador, int qtdDoador, Paciente *vetorPaciente, int qtdPaciente);

// EXCLUIR
void deletarDoador(Doador **vetor, int *quant_doadores, Doacao *vetorD, int qtdDoacoes,int *capacidade);
void deletarPaciente(Paciente **vetor, int *quant_pacientes, Doacao *vetorD, int qtdDoacoes,int *capacidade);
void deletarDoacao(Doacao **vetor, int *quant_doacoes,int *capacidade);

// CONSULTAS ESPECÍFICAS
void consultarDoadorEspecifico(Doador *vetor, int qtd);
void consultarPacienteEspecifico(Paciente *vetor, int qtd);
void consultarDoacaoEspecifica(Doacao *vDoacao, int qtdDoacao, Doador *vDoador, int qtdDoador, Paciente *vPaciente, int qtdPaciente);

// RELATÓRIOS
void relatorioDoadores(Doador *vetor, int qtd);
void relatorioPacientes(Paciente *vetor, int qtd);
void relatorioDoacoesPeriodo(Doacao *vDoacao, int qtdDoacao, Doador *vDoador, int qtdDoador, Paciente *vPaciente, int qtdPaciente);
void relatorioPorDoador(Doador *vDoador, int qtdDoador, Doacao *vDoacao, int qtdDoacao);
void relatorioPorPaciente(Paciente *vPaciente, int qtdPaciente, Doacao *vDoacao, int qtdDoacao);

//FUNÇÕES DE VERIFICAÇÃO
int validarData(int dia, int mes, int ano);
int validarTipoSanguineo(char *sangue);
int validarNome(char *nome) ;
int validarIdade(int idade);
int validarCpf(char *cpf);
int validarSexo(char sexo);
void lerDataFormatada(char *mensagem, int *d, int *m, int *a);
int lerOpcaoMenu();

//PERSISTÊNCIA DE DADOS
void salvarDoadores(Doador *vetor, int qtd);
void carregarDoadores(Doador **vetor, int *qtd,int * capacidade);
void salvarPacientes(Paciente *vetor, int qtd);
void carregarPacientes(Paciente **vetor, int *qtd,int *capacidade) ;
void salvarDoacoes(Doacao *vetor, int qtd) ;
void carregarDoacoes(Doacao **vetor, int *qtd,int *capacidade);

//GERENCIAR MEMÓRIA
void gerenciarMemoria(void **vetor, int qtd, int *capacidade, size_t tamStruct);
#endif
