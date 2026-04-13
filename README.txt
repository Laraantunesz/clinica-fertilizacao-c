1. IDENTIFICAÇÃO DO GRUPO:

 - João Gabriel Menegatti - Matrícula:12511BSI221
 - João Lucas Machado Matos - Matrícula: 12511BSI229
 - Lara Zuleika Antunes Silva - Matrícula: 12511BSI218
 - Samuel Victor Moreira Oripes - Matrícula: 12511BSI234
 - Victor Emanuel Neres - Matrícula: 12511BSI253

------------------------------------------------------------------------------------------------------------------------------------------
2. TEMA DO PROJETO:  Gerenciamento de sistema de uma Clínica de fertilização

O trabalho consiste no desenvolvimento de um sistema para gerenciar os dados de uma clínica de fertilização. 
O software controlará o cadastro de Doadores , Pacientes (receptores do tratamento) e as Doações/Procedimentos realizados.

Estrutura 1: Doadores
Estrutura 2: Pacientes
Estrutura 3: Doações
------------------------------------------------------------------------------------------------------------------------------------------
3. INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO:

 - Ambiente de Desenvolvimento: CodeBlocks versão 25.03 no sistema operacional MS-Windows 11.
 - Como Compilar: 
      1. Abra o arquivo de projeto .cbp no CodeBlocks.
      2. Certifique-se de que os arquivos main.c, funcoes.c, auxiliares.c e prototipos.h estão no mesmo diretório.
      3. Pressione F9 (Build and Run).
 - Persistência de Dados: O programa carrega e salva os dados automaticamente em arquivos binários (doadores.bin, pacientes.bin e doacoes.bin) localizados na pasta principal do projeto.
------------------------------------------------------------------------------------------------------------------------------------------
4. OBSERVAÇÕES:
 - Controle de Memória: O sistema aloca 5 posições extras inicialmente e realoca conforme a necessidade, garantindo que nunca haja mais de 5 posições livres simultaneamente
 - Relatórios: O sistema gera relatórios formatados em arquivos .txt conforme as opções selecionadas pelo usuário.
 - Dados Pré-preenchidos: Estão inclusos arquivos com 10 registros para cada estrutura, gerados a partir da execução do próprio programa.
