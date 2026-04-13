🏥 **Sistema de Gerencimento -  Clínica de Fertilização**

  Este é um sistema  desenvolvido em **linguagem C** para o gerenciamento de doadores, pacientes e procedimentos (doações) em uma clínica de fertilização. O projeto foca em modularização, persistência de dados binários e gerenciamento dinâmico de memória.

💡 **Destaques do Projeto :**

   - Arquitetura Modular:*Divisão clara de responsabilidades entre lógica de CRUD e operações principais (funcoes.c), utilitários de validação (auxiliares.c) e o fluxo principal (main.c).

   - Persistência Binária: Todos os dados são salvos em arquivos .bin dentro da pasta database/,garantindo que as informações não sejam perdidas ao fechar o programa.

   - Gerenciamento Dinâmico de Memória: O sistema utiliza malloc, realloc e free para otimizar o uso da RAM, ajustando a capacidade dos vetores conforme a necessidade através de uma função dedicada de gerenciamento.

   - Validações Rigorosas: Implementação de verificações para CPFs (11 dígitos), tipos sanguíneos válidos, datas reais (incluindo anos bissextos) e limites de idade.

🛠️ **Funcionalidades:**

**1. Módulos de Cadastro e Gestão**
  - Doadores: Cadastro com nome, CPF único, idade, sexo e tipo sanguíneo.

  - Pacientes: Registro de receptores mantendo a integridade de CPFs únicos no sistema.

  - Doações (Procedimentos): Vinculação entre um doador e um paciente, com controle de status (Em andamento, Fecundado, Não Fecundado) e data.

**2. Consultas e Relatórios**
  - Busca Específica: Consulta detalhada por CPF ou Código de Doação.

  - Relatórios em Tela: Listagem formatada de todos os registros.

  - Exportação de Relatórios (.txt): Geração de arquivos de texto externos para:

  - Doações por período específico.

  - Histórico completo de um Doador.

  - Prontuário de procedimentos de um Paciente.

**3. Integridade de Dados**

  - Proteção de Exclusão: O sistema impede a exclusão de doadores ou pacientes que possuam doações ativas vinculadas, evitando órfãos de dados.

🏗️ **Estrutura do Arquivo**

O projeto está organizado da seguinte forma:

- 📂 src/

   - main.c: Ponto de entrada e loop principal do menu.

   - funcoes.c: Implementação das funcionalidades de CRUD e relatórios.

   - auxiliares.c: Funções de persistência, validação e gestão de memória.

   - prototipos.h: Definição das structs e assinaturas das funções.

- 📂 database/: Local onde os arquivos binários (doadores.bin, pacientes.bin, doacoes.bin) são armazenados.

- 📄 trabalho.cbp: Arquivo de projeto do Code::Blocks para fácil importação.

💾 **Persistência de Dados**

O sistema gerencia os dados de forma automática em arquivos binários localizados na pasta database/:

  - Carregamento: AAo iniciar, o programa lê os arquivos doadores.bin, pacientes.bin e doacoes.bin da pasta database/.

  - Salvamento: Todas as alterações (cadastros, edições ou exclusões) são persistidas nos arquivos binários imediatamente ou ao encerrar o programa através do menu.

  - Arquivos de Saída: Relatórios detalhados gerados pelo usuário são salvos em formato 
  .txt na raiz do projeto

💻 **Como Executar**

O sistema pode ser compilado e executado de duas maneiras:

**Opção 1: Via Code::Blocks (Recomendado)**

  - Ambiente: Desenvolvido no Code::Blocks 25.03 para Windows 11.

  - Abra o arquivo de projeto trabalho.cbp no Code::Blocks.

  - Certifique-se de que os arquivos main.c, funcoes.c, auxiliares.c e prototipos.h estão no diretório src/.

  - Pressione F9 (Build and Run).

**Opção 2: Via Terminal (GCC)**

  - Pré-requisito: Ter o compilador GCC instalado e configurado no PATH.

  - Clone o repositório para sua máquina local.

  - Navegue até a pasta raiz do projeto.

  - Compile todos os módulos com o comando:gcc src/main.c src/funcoes.c src/auxiliares.c -o clinica_sistema

  - Execute o programa: ./clinica_sistema ou ./clinica_sistema.exe

  

 Projeto desenvolvido como trabalho acadêmico para demonstrar conceitos avançados de manipulação de ponteiros e arquivos e gerenciamento de memória em C.