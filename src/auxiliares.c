#include <ctype.h>
#include <stdio.h>
#include "prototipos.h"
#include <string.h>
#include <stdlib.h>

// ============================================================
// FUNÇÕES DE VERIFICAÇÃO
// ============================================================

// VALIDAÇÃO DE DATAS
int validarData(int dia, int mes, int ano) {
    // Verifica ano e mês básico
    if (ano < 1900 || ano > 2100 || mes < 1 || mes > 12) return 0;

    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajuste para ano bissexto (fevereiro com 29 dias)
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasNoMes[1] = 29;
    }

    // Verifica se o dia está dentro do limite do mês
    if (dia < 1 || dia > diasNoMes[mes - 1]) return 0;

    return 1;
}

// VALIDAÇÃO DE TIPO SANGUÍNEO
int validarTipoSanguineo(char *sangue) {
    // Lista de tipos válidos
    char *tiposValidos[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};

    for (int i = 0; i < 8; i++) {

        if (strcmp(sangue, tiposValidos[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// VALIDAÇÃO DE TIPO SANGUÍNEO
int validarNome(char *nome) {
    int tam = 0;

    for (int i = 0; nome[i] != '\0'; i++) {
        char c = nome[i];

        // Se for letra maiúscula, OU minúscula, OU espaço, incrementa o tamanho
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
            tam++;
        }
        else {
            // se achar algo inválido
            return 0;
        }
    }

    // Após validar os caracteres, verifica os limites de tamanho
    if (tam >= 3 && tam <= 50) {


        for (int j = 0; nome[j] != '\0'; j++) {
            if (nome[j] != ' ') {
                return 1; // Tudo válido: caracteres ok, tamanho ok não é somente espaços
            }
        }
    }

    return 0; // Caso caia fora das condições de tamanho ou seja só espaços
}

// VALIDAÇÃO DA IDADE
int validarIdade(int idade) {

    if (idade >= 18 && idade <= 100) {
        return 1; // Retorna 1 se válida
    }


    return 0;// se for uma idade inválida
}
// VALIDAÇÃO DO CPF
int validarCpf(char *cpf){


    if(strlen(cpf)!= 11){
        return 0; //caso o tamanho do cpf seja diferente de 11
    }

    for(int i = 0; i < 11; i++){

        if(cpf[i] < '0' || cpf[i] > '9'){
            return 0; //caso tenha letras ou simbolos
        }
    }

    return 1; //CPF válido
}

// Função para validar o sexo digitado
int validarSexo(char sexo) {
    // converter para maiusculo
    sexo = toupper(sexo);

    if (sexo == 'M' || sexo == 'F') {
        return 1; // sexo válido
    }

    return 0; // sexo inválido
}



// VALIDAR CONTEÚDO DIGITADO (DATA)

// Lê uma data no formato dd/mm/aaaa, limpa o buffer e valida usando SUA função
void lerDataFormatada(char *mensagem, int *d, int *m, int *a) {
    int dataValida = 0;

    do {
        printf("%s", mensagem);

        // 1. Tenta ler 3 números separados por barras
        int retorno = scanf("%d/%d/%d", d, m, a);

        // 2. LIMPEZA DE BUFFER (Essencial para não travar se digitar letras)
        // Consome tudo o que o usuário digitou até o ENTER
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        // 3. Verificação Dupla:
        // A) retorno == 3: Significa que o usuário digitou numeros/numeros/numeros
        // B) validarData(...): Chama a SUA função para ver se a data existe
        if (retorno == 3 && validarData(*d, *m, *a)) {
            dataValida = 1; // Sai do loop
        } else {
            printf("\nERRO: Data invalida ou formato incorreto!\n");
            printf("Por favor, digite no formato dd/mm/aaaa (Ex: 25/12/2025)\n\n");
        }

    } while (!dataValida);
}

// Função auxiliar para o menu receber apenas números
int lerOpcaoMenu() {
    int opcao;
    // Se o scanf não conseguir ler um número (retorno != 1)
    if (scanf("%d", &opcao) != 1) {
        // Limpa todo o lixo que o usuário digitou até o Enter
        while (getchar() != '\n');
        return -1; // Retorna um valor inválido
    }
    getchar(); // Limpa o \n que sobra após uma leitura correta
    return opcao;
}
// ============================================================
// PERSISTÊNCIA DE DADOS
// ============================================================

// --- PERSISTÊNCIA: DOADORES ---
void salvarDoadores(Doador *vetor, int qtd) {
    FILE *arq = fopen("database/doadores.bin", "wb");
    if (arq != NULL) {
        // Grava apenas os elementos válidos presentes no vetor [cite: 37, 39]
        fwrite(vetor, sizeof(Doador), qtd, arq);
        fclose(arq);
    }
}

void carregarDoadores(Doador **vetor, int *qtd,int *capacidade) {
    FILE *arq = fopen("database/doadores.bin", "rb");
   //Se o arquivo não existir,inicializa o vetor vazio com 5 posições livres
    if (arq == NULL) {
        *qtd = 0;
        *capacidade = espaco_livre;//5 espaços
        // aloca espaço para a capcidade inicial
        *vetor = (Doador *)malloc((*capacidade)*sizeof(Doador));
        return;
    }
  // Se já existir cadastros descobrimos a quantidade para ler os dados
    fseek(arq,0,SEEK_END);
    *qtd = ftell(arq)/sizeof(Doador);
    rewind(arq);
    *capacidade = *qtd + espaco_livre;
     *vetor = (Doador *)malloc((*capacidade)*sizeof(Doador));

    if(*vetor!= NULL){
        fread(*vetor,sizeof(Doador),*qtd,arq);
    }

    fclose(arq);
}

// --- PERSISTÊNCIA: PACIENTES ---
void salvarPacientes(Paciente *vetor, int qtd) {
    FILE *arq = fopen("database/pacientes.bin", "wb");
    if (arq != NULL) {
        fwrite(vetor, sizeof(Paciente), qtd, arq);
        fclose(arq);
    }
}

void carregarPacientes(Paciente **vetor, int *qtd,int *capacidade) {
    FILE *arq = fopen("database/pacientes.bin", "rb");
    //Se o arquivo não existir,inicializa o vetor vazio com 5 posições livres
    if (arq == NULL) {
        *qtd = 0;
        *capacidade = espaco_livre;//5 espaços
        // aloca espaço para a capcidade inicial
        *vetor = (Paciente *)malloc((*capacidade)*sizeof(Paciente));
        return;
    }
    // Se já existir cadastros descobrimos a quantidade para ler os dados
    fseek(arq,0,SEEK_END);
    *qtd = ftell(arq)/sizeof(Paciente);
    rewind(arq);
    *capacidade = *qtd + espaco_livre;
     *vetor = (Paciente *)malloc((*capacidade)*sizeof(Paciente));

    if(*vetor!= NULL){
        fread(*vetor,sizeof(Paciente),*qtd,arq);
    }

    fclose(arq);
}

// --- PERSISTÊNCIA: DOAÇÕES ---
void salvarDoacoes(Doacao *vetor, int qtd) {
    FILE *arq = fopen("database/doacoes.bin", "wb");
    if (arq != NULL) {
        fwrite(vetor, sizeof(Doacao), qtd, arq);
        fclose(arq);
    }
}

void carregarDoacoes(Doacao **vetor, int *qtd,int *capacidade) {
    FILE *arq = fopen("database/doacoes.bin", "rb");
    //Se o arquivo não existir,inicializa o vetor vazio com 5 posições livres
    if (arq == NULL) {
        *qtd = 0;
        *capacidade = espaco_livre;
        *vetor = (Doacao *)malloc((*capacidade)*sizeof(Doacao));

        return;
    }
 // Se já existir cadastros descobrimos a quantidade para ler os dados
    fseek(arq, 0, SEEK_END);
    int totalNoarquivo = ftell(arq) / sizeof(Doacao);
    rewind(arq);

    *capacidade = totalNoarquivo + espaco_livre;
    *vetor = (Doacao *) malloc((*capacidade) * sizeof(Doacao));

    if (*vetor != NULL) {
        *qtd = fread(*vetor, sizeof(Doacao),totalNoarquivo,arq);
    }
    fclose(arq);
}

// ============================================================
// GERENCIAMENTO DE MEMÓRIA
// ============================================================

void gerenciarMemoria(void **vetor,int qtd,int *capacidade,size_t tamStruct){
    //
    if(qtd >= *capacidade){
        *capacidade+=espaco_livre;

        void *temp = realloc(*vetor,(*capacidade)*tamStruct);

        if(temp == NULL){
            *capacidade -= espaco_livre;//volta ao tamanho anterior a tentativa de realloc
            printf("\n[ERRO] Memoria Insuficiente\n");
        }else{
            *vetor = temp; //o endereco que **vetor aponta agora é temp
        }
    }

   // Se a folga (capacidade - quantidade) for maior que o permitido (5)
    else if((*capacidade -qtd) > espaco_livre){//ajusta se tiver mais de 5 espaços livres
      *capacidade = qtd + espaco_livre;

      //Trava de segurança: Nunca deixa a capacidade ser menor que o mínimo inicial (5)

        if(*capacidade < espaco_livre){

        *capacidade = espaco_livre; //se tiver menos de 5 posições de capacidade, ajustamos pra 5 livres;

        void *temp = realloc(*vetor,(*capacidade)*tamStruct);


        if(temp == NULL){
            printf("\n[ERRO] Memoria Insuficiente\n");
        }else{
            *vetor = temp; //o endereco que **vetor aponta agora é temp
        }
        }

    }

   // printf("\n[DEBUG] Nova capacidade: %d\n", *capacidade);
}
