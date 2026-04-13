
#include<stdio.h>
#include "prototipos.h"
#include <string.h>

// ============================================================
// MENUS
// ============================================================
int menuPrincipal() {
    int op;

    printf("\n======= CLINICA DE FERTILIZACAO =======\n");
    printf("1. Gerenciar DOADORES\n");
    printf("2. Gerenciar PACIENTES\n");
    printf("3. Gerenciar DOACOES\n");
    printf("4. Relatorios e Listas\n");
    printf("0. Sair\n");
    printf("===================================\n");
    printf("Digite sua escolha: ");

    op = lerOpcaoMenu();

    return op;
}
int subMenu() {
    int opcao;
    do{
        printf("\n======= MENU DE OPCOES ======\n");
        printf("1. Cadastrar\n");
        printf("2. Consultar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("0. Voltar ao menu principal\n");
        printf("===================================\n");
        printf("Digite sua escolha: ");

        opcao = lerOpcaoMenu();

        if (opcao < 0 || opcao > 4) {
            printf("Opcao inválida! Tente novamente.\n");
        }

    }while(opcao < 0 || opcao > 4);

    return opcao;
}
int menuListas() {
    int op;
    do{
        printf("\n======= RELATORIOS E LISTAGENS =======\n");
        printf("1. Listar todos os DOADORES\n");
        printf("2. Listar todos os PACIENTES\n");
        printf("3. Relatorio de Doacoes por PERIODO\n");
        printf("4. Relatorio de Doacoes a partir do DOADOR\n");
        printf("5. Relatorio de Doacoes a partir do PACIENTE\n");
        printf("0. Voltar ao menu principal\n");
        printf("===================================\n");
        printf("Digite sua escolha: ");

        op = lerOpcaoMenu();

        if (op < 0 || op > 5) {
            printf("Opcao invalida! Tente novamente.\n");
        }
    }while(op < 0 || op > 5);

    return op;
}

// ============================================================
// FUNÇÕES DE BUSCA
// ============================================================

// Busca Paciente pelo CPF
int buscarPaciente(Paciente *vetor, int quant, char *cpf){
    for(int i=0;i<quant;i++){
        if(strcmp(vetor[i].cpf,cpf)==0){
            return i; // achou
        }
    }
    return -1;// não achou esse paciente
}

// Busca Doador pelo CPF

int buscarDoador(Doador *vetor, int quant, char *cpf){
    for(int i=0; i<quant; i++){
        if(strcmp(vetor[i].cpf, cpf) == 0) return i;
    }
    return -1;// não achou
}

int buscarDoacao(Doacao *vetor, int quant, int codigo){
    for(int i=0;i<quant;i++){
        if(vetor[i].codigo == codigo){
            return i;
        }
    }
    return -1;// não achou
}

// ============================================================
// FUNÇÕES DE CADASTRO
// ============================================================


void cadastrarDoador(Doador **vetor, int *qtd, int *capacidade,Paciente *vPaciente,int qtdPaciente) {

    gerenciarMemoria((void**) vetor, *qtd, capacidade, sizeof(Doador));

    Doador *novoDoador = (*vetor) + (*qtd);

    printf("Cadastro doador\n-------------------\n");

    char tempCpf[20];
    int valido = 0;

    do{
        printf("Entre com seu CPF: ");

        scanf(" %19s", tempCpf);
        // LIMPEZA DE BUFFER
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if(validarCpf(tempCpf) != 1){
            printf("Nao eh possivel cadastrar um novo doador.\nO CPF precisa ter 11 digitos numericos.\n");
            printf("Tente novamente!\n");
            continue;
        }
        else if(buscarDoador(*vetor, *qtd, tempCpf) != -1){
            printf("Nao eh possivel cadastrar um novo doador.\nCPF ja cadastrado.\n");
            printf("Tente novamente!\n");
            continue;
        }
        else if(buscarPaciente(vPaciente, qtdPaciente, tempCpf) != -1){
            printf("Nao eh possivel cadastrar um novo doador.\nCPF ja cadastrado.\n");
            printf("Tente novamente!\n");
            continue;
        }

        valido = 1;
    }while(valido == 0);

    strcpy(novoDoador->cpf, tempCpf);

    do {
        printf("Nome: ");
        scanf(" %[^\n]", novoDoador->nome);
        if(!validarNome(novoDoador->nome)){
            printf("ERRO: Nome invalido (minimo 3 letras)!\n");
        }
    } while (!validarNome(novoDoador->nome));

    do {
        printf("Idade (18-100): ");
        scanf(" %d", &(novoDoador->idade));
        if(!validarIdade(novoDoador->idade)){
            printf("ERRO: Idade invalida! Idade deve ser entre 18 e 100.\n");
        }
    } while (!validarIdade(novoDoador->idade));

    do {
        printf("Sexo (M/F): ");
        scanf(" %c", &(novoDoador->sexo));

        if(novoDoador->sexo >= 'a' && novoDoador->sexo <= 'z'){
            novoDoador->sexo -= 32;
        }

        if(novoDoador->sexo != 'M' && novoDoador->sexo != 'F'){
            printf("ERRO: Sexo invalido! Use M ou F.\n");
        }
    } while (novoDoador->sexo != 'M' && novoDoador->sexo != 'F');

    do {
        printf("Tipo Sanguineo (ex: A+, O-): ");
        scanf(" %[^\n]", novoDoador->sangue);

        if(!validarTipoSanguineo(novoDoador->sangue)){
            printf("ERRO: Tipo invalido! (Use maiusculo, ex: A+, AB-)\n");
        }
    } while (!validarTipoSanguineo(novoDoador->sangue));

    (*qtd)++;
    salvarDoadores((*vetor), *qtd);
    printf("Doador cadastrado com sucesso!\n-----------------------------\n");
}

void cadastrarPaciente(Paciente **vetor, int *qtd, int *capacidade,Doador *vDoador,int qtdDoador) {

    gerenciarMemoria((void**) vetor, *qtd, capacidade, sizeof(Paciente));

    Paciente *novoPaciente = (*vetor) + (*qtd);

    printf("Cadastro paciente\n-------------------\n");

    char tempCpf[20];
    int valido = 0;

    do{
        printf("Entre com seu CPF: ");
        scanf("%19s", tempCpf);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if(validarCpf(tempCpf) != 1){
            printf("Nao eh possivel cadastrar um novo paciente.\nO CPF precisa ter 11 digitos numericos.\n");
            printf("Tente novamente!\n");
            continue;
        }
        else if(buscarPaciente(*vetor, *qtd, tempCpf) != -1){
            printf("Nao eh possivel cadastrar um novo paciente.\nCPF ja cadastrado.\n");
            printf("Tente novamente!\n");
            continue;
        }
        else if(buscarDoador(vDoador, qtdDoador, tempCpf) != -1){
            printf("Nao eh possivel cadastrar um novo paciente.\nCPF ja cadastrado.\n");
            printf("Tente novamente!\n");
            continue;
        }
        valido = 1;
    }while(valido == 0);

    strcpy(novoPaciente->cpf, tempCpf);

    do {
        printf("Nome: ");
        scanf(" %[^\n]", novoPaciente->nome);

        if(!validarNome(novoPaciente->nome)){
            printf("ERRO: Nome invalido (minimo 3 letras)!\n");
        }
    } while (!validarNome(novoPaciente->nome));

    do {
        printf("Idade (18-100): ");
        scanf(" %d", &(novoPaciente->idade));

        if(!validarIdade(novoPaciente->idade)){
            printf("ERRO: Idade invalida! Idade deve estar entre 18 e 100.\n");
        }
    } while (!validarIdade(novoPaciente->idade));

    do {
        printf("Sexo (M/F): ");
        scanf(" %c", &(novoPaciente->sexo));

        // Converte minúsculo para maiúsculo
        if(novoPaciente->sexo >= 'a' && novoPaciente->sexo <= 'z'){
            novoPaciente->sexo -= 32;
        }

        if(novoPaciente->sexo != 'M' && novoPaciente->sexo != 'F'){
            printf("ERRO: Sexo invalido! Use M ou F.\n");
        }
    } while (novoPaciente->sexo != 'M' && novoPaciente->sexo != 'F');

    (*qtd)++;
    salvarPacientes((*vetor), *qtd);
    printf("Paciente cadastrado com sucesso!\n-----------------------------\n");
}

void cadastrarDoacao(Doacao **vDoacao, int *qtdDoacao, Doador *vDoador, int qtdDoador, Paciente *vPaciente, int qtdPaciente, int *capacidade) {

    gerenciarMemoria((void**) vDoacao, *qtdDoacao, capacidade, sizeof(Doacao));

    Doacao *novaDoacao = (*vDoacao) + (*qtdDoacao);

    printf("Cadastro doacao\n-------------------\n");

    int tempCodigo;
    printf("Digite um Codigo para esta doacao: ");
    scanf(" %d", &tempCodigo);

    if (buscarDoacao(*vDoacao, *qtdDoacao, tempCodigo) != -1) {
        printf("Nao eh possivel cadastrar uma nova doacao.\nCodigo ja existe!\n");
        return;
    }

    novaDoacao->codigo = tempCodigo;

    char tempCpf[12];

    printf("Entre com o CPF do paciente: ");
    scanf(" %11s", tempCpf);

    int posicao = buscarPaciente(vPaciente, qtdPaciente, tempCpf);

    if(posicao == -1){
        printf("Nao eh possivel cadastrar uma nova doacao.\nPaciente nao encontrado.\n");
        return;
    }

    // Nota: Como vPaciente é recebido com *, podemos usar aritmética nele também
    strcpy(novaDoacao->cpf_paciente, (vPaciente + posicao)->cpf);

    printf("Entre com o CPF do doador: ");
    scanf("  %[^\n]", tempCpf);

    posicao = buscarDoador(vDoador, qtdDoador, tempCpf);

    if(posicao == -1){
        printf("Nao eh possivel cadastrar uma nova doacao.\nDoador nao encontrado.\n");
        return;
    }

    strcpy(novaDoacao->cpf_doador, (vDoador + posicao)->cpf);

    int d, m, a;

    lerDataFormatada("Data do procedimento (dd/mm/aaaa): ", &d, &m, &a);

    novaDoacao->data_procedimento.dia = d;
    novaDoacao->data_procedimento.mes = m;
    novaDoacao->data_procedimento.ano = a;

    novaDoacao->status = 1;

    (*qtdDoacao)++;
    salvarDoacoes((*vDoacao), *qtdDoacao);
    printf("Doacao realizada com sucesso!\n");
}
// ============================================================
// FUNÇÕES DE UPDATE
// ============================================================

// Altere dados de um doador a partir de seu CPF.
int updateDoador(Doacao *vetorDoacao, int qtdDoacao, Doador *vetorDoador, int qtdDoador)
{
    char cpf[15];
    do {
        printf("CPF do doador (cujos dados serao alterados): ");

        fgets(cpf, 15, stdin);
        cpf[strcspn(cpf, "\n")] = 0;

        if (!(validarCpf(cpf)))
        {
            printf("Por favor, busque por um CPF valido.\n");
        }
    } while (!(validarCpf(cpf)));

    int idx_doador = buscarDoador(vetorDoador, qtdDoador, cpf);
    if (idx_doador == -1)
    {
        printf("Doador nao encontrado!\n");
        return -1;
    }

    Doador *pDoador = vetorDoador + idx_doador;

    int option;
    do
    {
        printf("\n\nMENU UPDATE - DOADOR\n\n");
        printf("Alterar dados do doador: %s", pDoador->nome);

        printf("\n1 - Alterar nome");
        printf("\n2 - Alterar cpf");
        printf("\n3 - Alterar idade");
        printf("\n4 - Alterar sexo");
        printf("\n5 - Alterar tipo sanguineo");
        printf("\n0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &option);
        getchar();

        if (option == 1)
        {
            char new_name[50];
            do {
                printf("Digite o nome: ");

                fgets(new_name, 50, stdin);
                new_name[strcspn(new_name, "\n")] = 0;

                if (!(validarNome(new_name)))
                {
                    printf("Nome invalido.\n");
                }
            } while (!(validarNome(new_name)));

            printf("Alterando nome de %s para %s...\n", pDoador->nome, new_name);
            strcpy(pDoador->nome, new_name);
        }

        else if (option == 2)
        {
            char new_cpf[15];
            do {
                printf("Digite o CPF: ");

                fgets(new_cpf, 15, stdin);
                new_cpf[strcspn(new_cpf, "\n")] = 0;

                if (!(validarCpf(new_cpf)))
                {
                    printf("CPF invalido.\n");
                }

                if(buscarDoador(vetorDoador, qtdDoador, new_cpf) != -1){
                    printf("O CPF ja existe, tente novamente.\n");
                }
            } while (!(validarCpf(new_cpf)) || buscarDoador(vetorDoador, qtdDoador, new_cpf) != -1);

            printf("Alterando CPF de %s para %s...\n", pDoador->cpf, new_cpf);
            strcpy(pDoador->cpf, new_cpf);

            for (int i = 0; i < qtdDoacao; i++)
            {
                if (strcmp((vetorDoacao + i)->cpf_doador, cpf) == 0)
                {
                    strcpy((vetorDoacao + i)->cpf_doador, new_cpf);
                }
            }
        }

        else if (option == 3)
        {
            int new_age;
            do {
                printf("Digite a idade (18-100): ");

                scanf("%d", &new_age);
                getchar();

                if (!(validarIdade(new_age)))
                {
                    printf("Idade invalida.\n");
                }
            } while (!(validarIdade(new_age)));

            printf("Alterando idade de %d para %d...\n", pDoador->idade, new_age);
            pDoador->idade = new_age;
        }

        else if (option == 4)
        {
            char sexo;
            do {
                printf("Digite o sexo: ");

                scanf("%c", &sexo);
                getchar();

                if (!(validarSexo(sexo)))
                {
                    printf("Sexo invalido.\n");
                }
            } while (!(validarSexo(sexo)));

            printf("Alterando sexo de %c para %c...\n", pDoador->sexo, sexo);
            pDoador->sexo = sexo;
        }

        else if (option == 5)
        {
            char new_btype[6];
            do {
                printf("Digite o tipo sanguineo: ");

                fgets(new_btype, 6, stdin);
                new_btype[strcspn(new_btype, "\n")] = 0;

                if (!(validarTipoSanguineo(new_btype)))
                {
                    printf("Tipo sanguíneo invalido.\n");
                }
            } while (!(validarTipoSanguineo(new_btype)));

            printf("Alterando tipo sanguineo de %s para %s...\n", pDoador->sangue, new_btype);
            strcpy(pDoador->sangue, new_btype);
        }

        else if (option != 0)
        {
            printf("\nEscolha invalida!\n");
        }

    } while (option != 0);

    printf("\nSaindo...\n\n");
    salvarDoadores(vetorDoador, qtdDoador);
    salvarDoacoes(vetorDoacao, qtdDoacao);
    return 1;
}

// Altere dados de um paciente a partir de seu CPF.
int updatePaciente(Doacao *vetorDoacao, int qtdDoacao, Paciente *vetorPaciente, int quant)
{
    char cpf[15];
    do {
        printf("CPF do paciente (cujos dados serao alterados): ");
        fgets(cpf, 15, stdin);
        cpf[strcspn(cpf, "\n")] = 0;

        if (!(validarCpf(cpf)))
        {
            printf("Por favor, busque por um CPF valido.\n");
        }
    } while (!(validarCpf(cpf)));

    int idx_paciente = buscarPaciente(vetorPaciente, quant, cpf);
    if (idx_paciente == -1) {
        printf("Paciente nao encontrado!\n");
        return -1;
    }

    Paciente *pPaciente = vetorPaciente + idx_paciente;

    int option;
    do
    {
        printf("\n\nMENU UPDATE - PACIENTE\n\n");

        printf("Alterar dados do paciente: %s", pPaciente->nome);
        printf("\n1 - Alterar nome");
        printf("\n2 - Alterar cpf");
        printf("\n3 - Alterar idade");
        printf("\n4 - Alterar sexo");
        printf("\n0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &option);
        getchar();

        if (option == 1)
        {
            char new_name[50];
            do {
                printf("Digite o nome: ");

                fgets(new_name, 50, stdin);
                new_name[strcspn(new_name, "\n")] = 0;

                if (!(validarNome(new_name)))
                {
                    printf("Nome invalido.\n");
                }
            } while (!(validarNome(new_name)));

            printf("Alterando nome de %s para %s...\n", pPaciente->nome, new_name);
            strcpy(pPaciente->nome, new_name);
        }

        else if (option == 2)
        {
            char new_cpf[15];
            do {
                printf("Digite o CPF: ");

                fgets(new_cpf, 15, stdin);
                new_cpf[strcspn(new_cpf, "\n")] = 0;

                if (!(validarCpf(new_cpf)))
                {
                    printf("CPF invalido.\n");
                }

                if(buscarPaciente(vetorPaciente, quant, new_cpf) != -1){
                    printf("O CPF ja existe, tente novamente.\n");
                }
            } while (!(validarCpf(new_cpf)) || buscarPaciente(vetorPaciente, quant, new_cpf) != -1);

            printf("Alterando CPF de %s para %s...\n", pPaciente->cpf, new_cpf);
            strcpy(pPaciente->cpf, new_cpf);

            for (int i = 0; i < qtdDoacao; i++)
            {
                if (strcmp((vetorDoacao + i)->cpf_paciente, cpf) == 0)
                {
                    strcpy((vetorDoacao + i)->cpf_paciente, new_cpf);
                }
            }
        }

        else if (option == 3)
        {
            int new_age;
            do {
                printf("Digite a idade (18-100): ");

                scanf("%d", &new_age);
                getchar();

                if (!(validarIdade(new_age)))
                {
                    printf("Idade invalida.\n");
                }
            } while (!(validarIdade(new_age)));

            printf("Alterando idade de %d para %d...\n", pPaciente->idade, new_age);
            pPaciente->idade = new_age;
        }

        else if (option == 4)
        {
            char sexo;
            do {
                printf("Digite o sexo: ");

                scanf("%c", &sexo);
                getchar();

                if (!(validarSexo(sexo)))
                {
                    printf("Sexo invalido.\n");
                }
            } while (!(validarSexo(sexo)));

            printf("Alterando sexo de %c para %c...\n", pPaciente->sexo, sexo);
            pPaciente->sexo = sexo;
        }

        else if (option != 0)
        {
            printf("\nEscolha invalida!\n");
        }

    } while (option != 0);

    printf("\nSaindo...\n");
    salvarPacientes(vetorPaciente, quant);
    salvarDoacoes(vetorDoacao, qtdDoacao);
    return 1;
}


// Altere dados de uma doação a partir de seu código.
int updateDoacao(Doacao *vetorDoacao, int qtdDoacao, Doador *vetorDoador, int qtdDoador, Paciente *vetorPaciente, int qtdPaciente)
{
    int code;
    printf("Codigo da doacao (cujos dados serao alterados): ");
    scanf("%d", &code);
    getchar();

    int idx_doacao = buscarDoacao(vetorDoacao, qtdDoacao, code);
    if (idx_doacao == -1) {
        printf("Doacao nao encontrada!\n");
        return -1;
    }

    Doacao *pDoacao = vetorDoacao + idx_doacao;

    int option;
    do
    {
        printf("\n\nMENU UPDATE - DOACAO\n\n");
        printf("Alterar dados de doacao: %d", pDoacao->codigo);

        printf("\n1 - Alterar status");
        printf("\n2 - Alterar doador");
        printf("\n3 - Alterar paciente");
        printf("\n4 - Alterar data do procedimento");
        printf("\n0 - Sair\n");

        printf("\nEscolha: ");
        scanf("%d", &option);
        getchar();

        if (option == 1)
        {
            printf("Digite o novo status (1-Em Andamento; 2-Fecundado; 3-Nao Fecundado): ");

            int new_status;
            scanf("%d", &new_status);
            getchar();

            pDoacao->status = new_status;
        }

        else if (option == 2)
        {
            char new_cpf[15];

            do
            {
                do {
                    printf("Digite o CPF do novo doador: ");

                    fgets(new_cpf, 15, stdin);
                    new_cpf[strcspn(new_cpf, "\n")] = 0;

                    if (!validarCpf(new_cpf))
                    {
                        printf("CPF invalido.\n");
                    }
                } while (!(validarCpf(new_cpf)));

                if (buscarDoador(vetorDoador, qtdDoador, new_cpf) == -1)
                {
                    printf("Doador nao encontrado.\n");
                }
            } while (buscarDoador(vetorDoador, qtdDoador, new_cpf) == -1);

            printf("Alterando doador de CPF %s para doador de CPF %s...\n", pDoacao->cpf_doador, new_cpf);
            strcpy(pDoacao->cpf_doador, new_cpf);
        }

        else if (option == 3)
        {
            char new_cpf[15];
            do
            {
                do {
                    printf("Digite o CPF do novo paciente: ");

                    fgets(new_cpf, 15, stdin);
                    new_cpf[strcspn(new_cpf, "\n")] = 0;

                    if (!(validarCpf(new_cpf)))
                    {
                        printf("CPF invalido.\n");
                    }
                } while (!(validarCpf(new_cpf)));

                if (buscarPaciente(vetorPaciente, qtdPaciente, new_cpf) == -1)
                {
                    printf("Paciente nao encontrado.\n");
                }
            } while (buscarPaciente(vetorPaciente, qtdPaciente, new_cpf) == -1);

            printf("Alterando paciente de CPF %s para paciente de CPF %s...\n", pDoacao->cpf_paciente, new_cpf);
            strcpy(pDoacao->cpf_paciente, new_cpf);
        }

        else if (option == 4)
        {
            Data new_date;

            lerDataFormatada("Digite a nova data da doacao: ", &(new_date.dia), &(new_date.mes), &(new_date.ano));

            printf("Alterando data de: %d/%d/%d\n", pDoacao->data_procedimento.dia, pDoacao->data_procedimento.mes, pDoacao->data_procedimento.ano);
            printf("Para: %d/%d/%d\n", new_date.dia, new_date.mes, new_date.ano);
            pDoacao->data_procedimento = new_date;
        }

        else if (option != 0)
        {
            printf("\nEscolha invalida!\n");
        }
    } while (option != 0);

    printf("\nSaindo...\n");
    salvarDoacoes(vetorDoacao, qtdDoacao);
    return 1;
}

// ============================================================
// FUNÇÕES DE EXCLUIR
// ============================================================

// Deleta Doador pelo index
void deletarDoador(Doador **vetor, int *quant_doadores, Doacao *vetorD, int qtdDoacoes,int *capacidade){
    printf("\n======= DELETAR DOADOR =======\n");

    char cpf[12];
    printf("Digite o CPF do doador que deseja excluir: ");
    scanf(" %[^\n]", cpf);

    int index = buscarDoador((*vetor), *quant_doadores, cpf);
    int quantComZero = *quant_doadores - 1;

    if (index == -1) {
        printf("Erro: Doador com CPF %s nao encontrado.\n", cpf);
        return;
    }

    for (int i = 0; i < qtdDoacoes; i++) {
        if (strcmp(vetorD[i].cpf_doador, cpf) == 0) {
            printf("Esse doador possui uma doacao ativa e por isso nao pode ser deletado\n");
            printf("Se voce deseja deletar esse paciente, primeiro delete suas doacoes do sistema\n");
            return;
        }
    }

    if (index == quantComZero) {
        *((*vetor)[index]).cpf = '\0';
        ((*vetor)[index]).idade = '0';
        *((*vetor)[index]).nome = '\0';
        ((*vetor)[index]).sexo = '\0';
    } else {
        for(int i = index; i < quantComZero; i++) {
            (*vetor)[i] = (*vetor)[i + 1];
        }
        ((*vetor)[quantComZero]).cpf[0] = '\0';
        ((*vetor)[quantComZero]).idade = '0';
        ((*vetor)[quantComZero]).nome[0] = '\0';
        ((*vetor)[quantComZero]).sexo = '\0';
    }

    (*quant_doadores)--;
    gerenciarMemoria((void**)vetor, *quant_doadores, capacidade, sizeof(Doador));

    salvarDoadores((*vetor), *quant_doadores);
    printf("O doador foi deletado com sucesso\n");
    printf("===================================\n");

}

// Deleta Paciente pelo index
void deletarPaciente(Paciente **vetor, int *quant_pacientes, Doacao *vetorD, int qtdDoacoes,int *capacidade){
    printf("\n======= DELETAR PACIENTE =======\n");

    char cpf[12];

    printf("Digite o CPF do paciente que deseja excluir: ");
    scanf(" %[^\n]", cpf);

    int index = buscarPaciente((*vetor), *quant_pacientes, cpf);
    int quantComZero = *quant_pacientes - 1;

    if (index == -1) {
        printf("Paciente nao encontrado no sistema\n");
        return;
    }

    for (int i = 0; i < qtdDoacoes; i++) {
        if (strcmp(vetorD[i].cpf_paciente, cpf) == 0) {
            printf("Esse paciente possui uma doacao ativa e por isso nao pode ser deletado\n");
            printf("Se voce deseja deletar esse paciente, primeiro delete suas doacoes do sistema\n");
            return;
        }
    }

    if (index == quantComZero) {
        ((*vetor)[index]).cpf[0] = '\0';
        ((*vetor)[index]).idade = '0';
        ((*vetor)[index]).nome[0] = '\0';
        ((*vetor)[index]).sexo = '\0';
    } else {
        for(int i = index; i < quantComZero; i++) {
            (*vetor)[i] = (*vetor)[i + 1];
        }
        ((*vetor)[quantComZero]).cpf[0] = '\0';
        ((*vetor)[quantComZero]).idade = '0';
        ((*vetor)[quantComZero]).nome[0] = '\0';
        ((*vetor)[quantComZero]).sexo = '\0';
    }

    (*quant_pacientes)--;
    gerenciarMemoria((void**)vetor, *quant_pacientes, capacidade, sizeof(Paciente));

    salvarPacientes((*vetor), *quant_pacientes);
    printf("O paciente foi deletado com sucesso\n");
    printf("===================================\n");

}

// Deleta Doação pelo index
void deletarDoacao(Doacao **vetor, int *quant_doacoes,int *capacidade){
    printf("\n======= DELETAR DOACAO =======\n");

    int codigo;

    printf("Digite o CODIGO da doacao que deseja excluir: ");
    scanf("%d",&codigo);

    int index = buscarDoacao((*vetor), *quant_doacoes, codigo);
    int quantComZero = *quant_doacoes - 1;

    if (index == -1) {
        printf("Erro: Doacao com codigo %d nao encontrada.\n", codigo);
        return;
    }

    for (int i = index; i < quantComZero; i++) {
        (*vetor)[i] = (*vetor)[i + 1];
    }
    (*quant_doacoes)--;

    gerenciarMemoria((void**)vetor, *quant_doacoes,capacidade, sizeof(Doacao));

    salvarDoacoes((*vetor), *quant_doacoes);
    printf("A doacao foi deletada com sucesso\n");
    printf("===================================\n");
}


// ============================================================
// FUNÇÕES DE CONSULTA ESPECÍFICA (BUSCA ÚNICA)
// ============================================================

// 1. Consultar um único Doador pelo CPF
void consultarDoadorEspecifico(Doador *vetor, int qtd) {
    char cpfBusca[12];
    printf("\n--- CONSULTA DE DOADOR ---\n");
    printf("Digite o CPF do doador: ");
    scanf(" %[^\n]", cpfBusca);
    getchar();

    int indice = buscarDoador(vetor, qtd, cpfBusca);

    if (indice != -1) {

        Doador *p = (vetor + indice);

        printf("\n>>> Doador Encontrado:\n");
        printf("Nome:   %s\n", p->nome);
        printf("CPF:    %s\n", p->cpf);
        printf("Idade:  %d\n", p->idade);
        printf("Sexo:   %c\n", p->sexo);
        printf("Sangue: %s\n", p->sangue);
    } else {
        printf("\nErro: Doador com CPF %s nao encontrado.\n", cpfBusca);
    }

    printf("--------------------------\n");
    printf("Pressione ENTER para retornar...");
    getchar();
}

// 2. Consultar um único Paciente pelo CPF
void consultarPacienteEspecifico(Paciente *vetor, int qtd) {
    char cpfBusca[12];
    printf("\n--- CONSULTA DE PACIENTE ---\n");
    printf("Digite o CPF do paciente: ");
    scanf(" %[^\n]", cpfBusca);
    getchar();

    int indice = buscarPaciente(vetor, qtd, cpfBusca);

    if (indice != -1) {

        Paciente *p = (vetor + indice);

        printf("\n>>> Paciente Encontrado:\n");
        printf("Nome:  %s\n", p->nome);
        printf("CPF:   %s\n", p->cpf);
        printf("Idade: %d\n", p->idade);
        printf("Sexo:  %c\n", p->sexo);
    } else {
        printf("\nErro: Paciente com CPF %s nao encontrado.\n", cpfBusca);
    }

    printf("--------------------------\n");
    printf("Pressione ENTER para retornar...");
    getchar();
}

// 3. Consultar uma única Doação pelo Código

void consultarDoacaoEspecifica(Doacao *vDoacao, int qtdDoacao, Doador *vDoador, int qtdDoador, Paciente *vPaciente, int qtdPaciente) {

    int codigoBusca;
    printf("\n--- CONSULTA DE DOACAO ---\n");
    printf("Digite o CODIGO da doacao: ");
    scanf("%d", &codigoBusca);
    getchar();

    int idxDoacao = buscarDoacao(vDoacao, qtdDoacao, codigoBusca);

    if (idxDoacao != -1) {

        Doacao *pDoacao = (vDoacao + idxDoacao);

        int idxDoador = buscarDoador(vDoador, qtdDoador, pDoacao->cpf_doador);
        int idxPaciente = buscarPaciente(vPaciente, qtdPaciente, pDoacao->cpf_paciente);

        char *nomeDoador;
        char *nomePaciente;

        if (idxDoador != -1)
            nomeDoador = (vDoador + idxDoador)->nome;
        else
            nomeDoador = "Desconhecido";

        if (idxPaciente != -1)
            nomePaciente = (vPaciente + idxPaciente)->nome;
        else
            nomePaciente = "Desconhecido";

        printf("\n>>> Doacao Encontrada:\n");
        printf("Codigo:   %d\n", pDoacao->codigo);
        printf("Data:     %02d/%02d/%d\n", pDoacao->data_procedimento.dia, pDoacao->data_procedimento.mes, pDoacao->data_procedimento.ano);
        printf("Status:   %d\n", pDoacao->status);
        printf("--------------------------\n");
        printf("Doador:   %s (CPF: %s)\n", nomeDoador, pDoacao->cpf_doador);
        printf("Paciente: %s (CPF: %s)\n", nomePaciente, pDoacao->cpf_paciente);

    } else {
        printf("\nErro: Doacao com codigo %d nao encontrada.\n", codigoBusca);
    }

    printf("--------------------------\n");
    printf("Pressione ENTER para retornar...");
    getchar();
}

// ============================================================
// FUNÇÕES DE RELATÓRIO
// ============================================================

long transformarData(int dia, int mes, int ano) {
    return (ano * 10000) + (mes * 100) + dia;
}

// 1. Relatório Geral de Doadores
void relatorioDoadores(Doador *vetor, int qtd) {

    if (qtd == 0) {
        printf("\nNenhum doador cadastrado.\n");
        return;
    }

    Doador *ptr;
    Doador *fim = vetor + qtd;

    printf("\n=== LISTA DE DOADORES ===\n");

    printf("+-------------------------------------------------------------------------+\n");
    printf("| %-30s | %-14s | %-5s | %-4s | %-6s |\n", "NOME", "CPF", "IDADE", "SEXO", "SANGUE");
    printf("+--------------------------------+----------------+-------+------+--------+\n");

    for (ptr = vetor; ptr < fim; ptr++) {

        printf("| %-30.30s | %-14s | %-5d | %-4c | %-6s |\n",
               ptr->nome,
               ptr->cpf,
               ptr->idade,
               ptr->sexo,
               ptr->sangue);
    }

    printf("---------------------------------------------------------------------------\n");
    printf("Total: %d registros.\n", qtd);

    printf("\nPressione ENTER para voltar...");
    getchar();
}

// 2. Relatório Geral de Pacientes
void relatorioPacientes(Paciente *vetor, int qtd) {
    if (qtd == 0) {
        printf("\nNenhum paciente cadastrado.\n");
        return;
    }

    Paciente *ptr;
    Paciente *fim = vetor + qtd;

    printf("\n=== LISTA DE PACIENTES ===\n");

    // Cabeçalho
    printf("------------------------------------------------------------------\n");
    printf("| %-30s | %-14s | %-5s | %-4s |\n", "NOME", "CPF", "IDADE", "SEXO");
    printf("|--------------------------------|----------------|-------|------|\n");

    for (ptr = vetor; ptr < fim; ptr++) {
        printf("| %-30.30s | %-14s | %-5d | %-4c |\n",
                ptr->nome,
                ptr->cpf,
                ptr->idade,
                ptr->sexo);
    }

    printf("------------------------------------------------------------------\n");
    printf("Total: %d registros.\n", qtd);

    printf("\nPressione ENTER para voltar...");
    getchar();
}



// 3. Relatório de Doações por Período
void relatorioDoacoesPeriodo(Doacao *vDoacao, int qtdDoacao, Doador *vDoador, int qtdDoador, Paciente *vPaciente, int qtdPaciente) {
    if (qtdDoacao == 0) {
        printf("\nNenhuma doacao cadastrada para gerar relatorio.\n");
        return;
    }

    int dIni, mIni, aIni, dFim, mFim, aFim;
    printf("\n=== GERAR ARQUIVO DE RELATORIO ===\n");
    lerDataFormatada("Digite a data INICIAL (dd/mm/aaaa): ", &dIni, &mIni, &aIni);
    lerDataFormatada("Digite a data FINAL (dd/mm/aaaa):   ", &dFim, &mFim, &aFim);

    long dataInicioInt = (aIni * 10000) + (mIni * 100) + dIni;
    long dataFimInt = (aFim * 10000) + (mFim * 100) + dFim;

    // Abrindo o arquivo para escrita
    FILE *arq = fopen("relatorio_periodo.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return;
    }

    // Cabeçalho do Arquivo
    fprintf(arq, "RELATORIO DE DOACOES POR PERIODO: %02d/%02d/%04d a %02d/%02d/%04d\n", dIni, mIni, aIni, dFim, mFim, aFim);
   fprintf(arq, "-----------------------------------------------------------------------------------------------------------\n");
   fprintf(arq, "| %-6s | %-10s | %-15s | %-30s | %-30s |\n", "COD", "DATA", "STATUS", "DOADOR", "PACIENTE");
   fprintf(arq, "|--------|------------|-----------------|--------------------------------|--------------------------------|\n");

    int encontrou = 0;
    Doacao *ptrDoacao;
    Doacao *fimDoacao = vDoacao + qtdDoacao;

    for (ptrDoacao = vDoacao; ptrDoacao < fimDoacao; ptrDoacao++) {
        long dataAtualInt = (ptrDoacao->data_procedimento.ano * 10000) +
                            (ptrDoacao->data_procedimento.mes * 100) +
                            ptrDoacao->data_procedimento.dia;

        if (dataAtualInt >= dataInicioInt && dataAtualInt <= dataFimInt) {
            encontrou = 1;

            int idxDoador = buscarDoador(vDoador, qtdDoador, ptrDoacao->cpf_doador);
            int idxPaciente = buscarPaciente(vPaciente, qtdPaciente, ptrDoacao->cpf_paciente);

            char *nomeDoador = (idxDoador != -1) ? (vDoador + idxDoador)->nome : "DESCONHECIDO";
            char *nomePaciente = (idxPaciente != -1) ? (vPaciente + idxPaciente)->nome : "DESCONHECIDO";

            // Tradução do Status
            char descStatus[20];
            switch(ptrDoacao->status) {
                case 1: strcpy(descStatus, "Em Andamento"); break;
                case 2: strcpy(descStatus, "Fecundado"); break;
                case 3: strcpy(descStatus, "Nao Fecundado"); break;
                default: strcpy(descStatus, "Desconhecido"); break;
            }

            char dataFormatada[11];
            sprintf(dataFormatada, "%02d/%02d/%04d",
                    ptrDoacao->data_procedimento.dia,
                    ptrDoacao->data_procedimento.mes,
                    ptrDoacao->data_procedimento.ano);

            fprintf(arq, "| %-6d | %-10s | %-15s | %-30.30s | %-30.30s |\n",
                    ptrDoacao->codigo, dataFormatada, descStatus, nomeDoador, nomePaciente);
        }
    }

    if (!encontrou) {
        fprintf(arq, "|                                    NENHUM REGISTRO ENCONTRADO NESSE PERIODO                                  |\n");
    }

    fprintf(arq, "-----------------------------------------------------------------------------------------------------------\n");

    fclose(arq);
    printf("\nRelatorio de doacoes por periodo gerado com sucesso!\n");
    printf("Pressione ENTER para continuar...");
    getchar();
}

// 4. Relatório por Doador

void relatorioPorDoador(Doador *vDoador, int qtdDoador, Doacao *vDoacao, int qtdDoacao) {
    char cpfBusca[12];
    printf("\n--- GERAR RELATORIO TXT POR DOADOR ---\n");
    printf("Digite o CPF do doador: ");
    scanf(" %11s", cpfBusca);
    getchar();

    int idx = buscarDoador(vDoador, qtdDoador, cpfBusca);
    if (idx == -1) {
        printf("\nErro: Doador com CPF %s nao encontrado.\n", cpfBusca);
        return;
    }

    Doador *doadorAlvo = vDoador + idx;

    FILE *arq = fopen("relatorio_doador.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar arquivo TXT!\n");
        return;
    }

    // Grava o perfil no arquivo
    fprintf(arq, "==========================================\n");
    fprintf(arq, "PERFIL DO DOADOR E HISTORICO\n");
    fprintf(arq, "==========================================\n");
    fprintf(arq, "NOME: %s\n", doadorAlvo->nome);
    fprintf(arq, "CPF: %s\n", doadorAlvo->cpf);
    fprintf(arq, "TIPO SANGUINEO: %s\n", doadorAlvo->sangue);
    fprintf(arq, "SEXO: %c\n", doadorAlvo->sexo);
    fprintf(arq, "==========================================\n\n");
    fprintf(arq, "%-10s | %-12s | %-15s | %-12s\n", "ID_DOACAO", "DATA", "STATUS", "CPF PACIENTE");
    fprintf(arq, "---------------------------------------------------------------\n");

    int encontrou = 0;
    Doacao *fimDoacao = vDoacao + qtdDoacao;

    for (Doacao *ptrDoacao = vDoacao; ptrDoacao < fimDoacao; ptrDoacao++) {
        if (strcmp(ptrDoacao->cpf_doador, cpfBusca) == 0) {

            // Tradução do Status
            char descStatus[20];
            switch(ptrDoacao->status) {
                case 1: strcpy(descStatus, "Em Andamento"); break;
                case 2: strcpy(descStatus, "Fecundado"); break;
                case 3: strcpy(descStatus, "Nao Fecundado"); break;
                default: strcpy(descStatus, "Desconhecido"); break;
            }

            fprintf(arq, "%-10d | %02d/%02d/%04d | %-15s | %-12s\n",
                ptrDoacao->codigo,
                ptrDoacao->data_procedimento.dia,
                ptrDoacao->data_procedimento.mes,
                ptrDoacao->data_procedimento.ano,
                descStatus,
                ptrDoacao->cpf_paciente);
            encontrou = 1;
        }
    }

    if (!encontrou) fprintf(arq, "Nenhuma doacao registrada.\n");

    fclose(arq);
    printf("\nRelatorio salvo com sucesso em 'relatorio_doador.txt'!\n");
}

// 5. Relatório por Paciente

void relatorioPorPaciente(Paciente *vPaciente, int qtdPaciente, Doacao *vDoacao, int qtdDoacao) {
    char cpfBusca[12];
    printf("\n--- GERAR RELATORIO TXT POR PACIENTE ---\n");
    printf("Digite o CPF do paciente: ");
    scanf(" %11s", cpfBusca);
    getchar();

    int idx = buscarPaciente(vPaciente, qtdPaciente, cpfBusca);
    if (idx == -1) {
        printf("\nErro: Paciente com CPF %s nao encontrado.\n", cpfBusca);
        return;
    }

    Paciente *pacienteAlvo = vPaciente + idx;

    FILE *arq = fopen("relatorio_paciente.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar arquivo TXT!\n");
        return;
    }

    // Grava o cabeçalho no arquivo
    fprintf(arq, "==========================================\n");
    fprintf(arq, "RELATORIO DE PROCEDIMENTOS - PACIENTE\n");
    fprintf(arq, "==========================================\n");
    fprintf(arq, "NOME: %s\n", pacienteAlvo->nome);
    fprintf(arq, "CPF: %s\n", pacienteAlvo->cpf);
    fprintf(arq, "IDADE: %d anos\n", pacienteAlvo->idade);
    fprintf(arq, "==========================================\n\n");
    fprintf(arq, "%-12s | %-15s | %-12s\n", "DATA", "STATUS", "CPF DOADOR");
    fprintf(arq, "------------------------------------------------\n");

    int encontrou = 0;
    Doacao *fimDoacao = vDoacao + qtdDoacao;

    for (Doacao *ptrDoacao = vDoacao; ptrDoacao < fimDoacao; ptrDoacao++) {
        if (strcmp(ptrDoacao->cpf_paciente, cpfBusca) == 0) {

            // Tradução do Status
            char descStatus[20];
            switch(ptrDoacao->status) {
                case 1: strcpy(descStatus, "Em Andamento"); break;
                case 2: strcpy(descStatus, "Fecundado"); break;
                case 3: strcpy(descStatus, "Nao Fecundado"); break;
                default: strcpy(descStatus, "Desconhecido"); break;
            }

            fprintf(arq, "%02d/%02d/%04d   | %-15s | %-12s\n",
                ptrDoacao->data_procedimento.dia,
                ptrDoacao->data_procedimento.mes,
                ptrDoacao->data_procedimento.ano,
                descStatus,
                ptrDoacao->cpf_doador);
            encontrou = 1;
        }
    }

    if (!encontrou) fprintf(arq, "Nenhum procedimento encontrado.\n");

    fclose(arq);
    printf("\nRelatorio salvo com sucesso em 'relatorio_paciente.txt'!\n");
}
