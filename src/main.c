#include <stdio.h>
#include <stdlib.h>
#include "prototipos.h"

int main() {

    Doador *vetorDoadores = NULL;
    int qtdDoadores = 0, capacidade_doadores = 0;

    Paciente *vetorPacientes = NULL;
    int qtdPacientes = 0,capacidade_pacientes = 0;

    Doacao *vetorDoacoes = NULL;
    int qtdDoacoes = 0,capacidade_doacoes = 0;

    int opPrincipal,subOpcao;

    carregarDoadores(&vetorDoadores, &qtdDoadores, &capacidade_doadores);
    carregarPacientes(&vetorPacientes, &qtdPacientes,&capacidade_pacientes) ;
    carregarDoacoes(&vetorDoacoes,&qtdDoacoes,&capacidade_doacoes);

    printf("\n========= SISTEMA INICIADO =========\n");
    printf("\n===========================================\n");
    printf("\n========= STATUS INICIAL DO SISTEMA =========");
    printf("\nDoadores:  %d cadastrados | Capacidade: %d", qtdDoadores, capacidade_doadores);
    printf("\nPacientes: %d cadastrados | Capacidade: %d", qtdPacientes, capacidade_pacientes);
    printf("\nDoacoes:   %d cadastrados | Capacidade: %d", qtdDoacoes, capacidade_doacoes);
    printf("\n===========================================\n");
    do{
        opPrincipal = menuPrincipal();
        if (opPrincipal == 0) break;

        switch (opPrincipal){

            // Passamos & no cadastrar e deletar pois eles podem usar realloc

            case 1: // MÓDULO  DOADORES

            subOpcao=subMenu();
            if(subOpcao == 1) cadastrarDoador(&vetorDoadores,&qtdDoadores,&capacidade_doadores,vetorPacientes,qtdPacientes);
            else if(subOpcao == 2) consultarDoadorEspecifico(vetorDoadores,qtdDoadores);
            else if(subOpcao == 3) updateDoador(vetorDoacoes, qtdDoacoes, vetorDoadores, qtdDoadores);
            else if(subOpcao == 4) deletarDoador(&vetorDoadores, &qtdDoadores, vetorDoacoes, qtdDoacoes,&capacidade_doadores);

            break;

            case 2: // MÓDULO PACIENTES

            subOpcao=subMenu();
            if(subOpcao == 1) cadastrarPaciente(&vetorPacientes,&qtdPacientes,&capacidade_pacientes,vetorDoadores,qtdDoadores);
            else if(subOpcao == 2) consultarPacienteEspecifico(vetorPacientes, qtdPacientes);
            else if(subOpcao == 3) updatePaciente(vetorDoacoes, qtdDoacoes, vetorPacientes, qtdPacientes);
            else if(subOpcao == 4) deletarPaciente(&vetorPacientes, &qtdPacientes, vetorDoacoes, qtdDoacoes,&capacidade_pacientes);

            break;

            case 3: // MÓDULO DOAÇÕES

            subOpcao=subMenu();
            if(subOpcao == 1) cadastrarDoacao(&vetorDoacoes,&qtdDoacoes, vetorDoadores,qtdDoadores, vetorPacientes,qtdPacientes,&capacidade_doacoes);
            else if(subOpcao == 2) consultarDoacaoEspecifica(vetorDoacoes,qtdDoacoes, vetorDoadores, qtdDoadores, vetorPacientes, qtdPacientes);
            else if(subOpcao == 3) updateDoacao(vetorDoacoes, qtdDoacoes, vetorDoadores, qtdDoadores, vetorPacientes, qtdPacientes);
            else if(subOpcao == 4) deletarDoacao(&vetorDoacoes,&qtdDoacoes,&capacidade_doacoes);

            break;

            case 4: // LISTAGENS


            subOpcao=menuListas();
            if(subOpcao == 1) relatorioDoadores(vetorDoadores,qtdDoadores);
            else if(subOpcao == 2) relatorioPacientes(vetorPacientes,qtdPacientes);
            else if(subOpcao == 3)relatorioDoacoesPeriodo(vetorDoacoes,qtdDoacoes,vetorDoadores, qtdDoadores,vetorPacientes, qtdPacientes);
            else if(subOpcao == 4)relatorioPorDoador(vetorDoadores,qtdDoadores,vetorDoacoes,qtdDoacoes);
            else if(subOpcao == 5)relatorioPorPaciente(vetorPacientes,qtdPacientes,vetorDoacoes,qtdDoacoes);

            break;

            default:
                printf("\nOpcao invalida, digite um numero de 0 a 4\n");
                break;
        }


    }while(opPrincipal != 0);


    salvarDoadores(vetorDoadores, qtdDoadores);
    salvarPacientes(vetorPacientes, qtdPacientes);
    salvarDoacoes(vetorDoacoes, qtdDoacoes) ;



    printf("\n===========================================\n");
    printf("\n========= STATUS FINAL DO SISTEMA =========");
    printf("\nDoadores:  %d cadastrados | Capacidade: %d", qtdDoadores, capacidade_doadores);
    printf("\nPacientes: %d cadastrados | Capacidade: %d", qtdPacientes, capacidade_pacientes);
    printf("\nDoacoes:   %d cadastrados | Capacidade: %d", qtdDoacoes, capacidade_doacoes);
    printf("\n===========================================\n");

    free(vetorDoadores);
    free(vetorPacientes);
    free(vetorDoacoes);

    printf("\n========= SISTEMA ENCERRADO =========\n");




    return 0;
}
