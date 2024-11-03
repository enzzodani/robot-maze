Ideia Geral
Um robô vai sair do ponto (0,0) e durante o caminho ira pegar pacotes para montar uma chave de criptografia. Esse mapa é um labirinto. Apos ele pegar todas as chaves, ele precisa chegar ao final do labirinto para pegar um pacote mestre. Apos isso, ele precisa voltar para o ponto (0,0)
Estruturas usadas até o momento
Lista ligada: Cada ponto do labirinto é um Node da lista, com ponteiros que apontam para os 4 pontos cardiais.
Fila: Existe uma fila de prioridade de pacotes, eles devem ser pegos em ordem.
Pilha: Apos pegar o ultimo pacote ou chegar em um beco sem saída, o robô precisa desempilhar seus movimentos para voltar a um ponto anterior
Árvores de estados: Armazena todos os possíveis estados visitados pelo robô (Posição, pacotes coletados,...), onde cada nó representa uma posição que o robô já tomou.
Uso Conjunto para Evitar Caminhos Redundantes
Navegação Inicial: Quando o robô explora o labirinto, ele armazena cada posição nova na árvore de estados, criando um nó filho para cada decisão (movimento). Ele também adiciona cada movimento na pilha.
Encontro de Obstáculos ou Becos sem Saída:
Pilha: Permite ao robô voltar rapidamente ao último ponto onde havia uma escolha alternativa. Ele desempilha posições uma a uma, retrocedendo no caminho.
Árvore de Estados: Ajuda o robô a saber quais caminhos ele já tentou ao retornar a um ponto de decisão, impedindo-o de seguir o mesmo caminho bloqueado. O robô pode consultar a árvore para escolher um caminho alternativo, evitando redundâncias e becos sem saída.
Exploração Completa:
A árvore mantém uma visão geral de todos os estados do labirinto explorados, e a pilha agiliza a movimentação de volta.
Quando o robô precisar retornar para o ponto inicial (após coletar o pacote mestre), ele pode seguir a pilha para refazer o caminho em ordem inversa, sem precisar reavaliar posições já exploradas.
Exemplo
Imagine que o robô está em uma posição X e tem três direções possíveis: A, B, e C. Ele segue A, que leva a um beco sem saída. Com a pilha, ele rapidamente volta para X. Com a árvore de estados, ele sabe que A já foi tentado, então ele ignora A e tenta B ou C sem repetição.

Esse uso conjunto evita caminhos redundantes e garante que o robô explore o labirinto de forma inteligente e eficiente.

Estrutura Básica
main.c: Ponto de entrada do programa.
labirinto.c e labirinto.h: Definições e implementações relacionadas ao labirinto.
pilha.c e pilha.h: Implementação da pilha.
fila_prioridade.c e fila_prioridade.h: Implementação da fila de prioridade.
estado.c e estado.h: Implementação da árvore de estados.
Labirinto
Cada ponto é um node de uma lista ligada
A estrutura será parecido com a abaixo:
// Estrutura do Node do Labirinto
typedef struct MazeNode {
    int x, y;  // Coordenadas do nó no labirinto
    int type; //1,2,3=ponto de pacote 0=vazio 7=obstáculo 9=pacote mestre
    struct MazeNode *north, *south, *east, *west;  // Vizinhos
} MazeNode;
1,2,3 é um ponto de pacote. Segue a ordem de prioridade que será definida pela Fila
0 é um ponto vazio
7 é um obstaculo, parede do labirinto █
9 é o pacote mestre, o qual tem o conteúdo a ser descriptografado
Pilha
Vai servir para o robô voltar por um caminho, como para o ponto 0,0 por exemplo
A pilha desempenha um papel crucial no projeto de navegação do robô no labirinto pelas seguintes razões:

Retrocesso Eficiente: Quando o robô chega a um ponto onde não há mais movimentos possíveis, ele pode usar a pilha para voltar rapidamente ao último ponto de decisão, economizando tempo e evitando o reexame de caminhos já percorridos.
Registro de Movimentos: A pilha mantém um registro sequencial dos movimentos do robô. Isso é fundamental, pois permite que o robô refaça seu caminho de volta para o ponto inicial após coletar todos os pacotes necessários.
Estratégia de Exploração: Usar uma pilha junto com uma árvore de estados ajuda a evitar que o robô explore caminhos já visitados. Quando ele retorna a um ponto de decisão, ele pode consultar a pilha para decidir quais direções ainda não foram tentadas.
// Estrutura do Node da Pilha
typedef struct StackNode {
    MazeNode *mazeNode;         // Aponta para o nó do labirinto atual
    struct StackNode *previous; // Aponta para o nó anterior da pilha
} StackNode;

// Estrutura da Pilha com um Descritor
typedef struct {
    StackNode *top; // Ponteiro para o topo da pilha
} Stack;
Fila de prioridade
Define a ordem que deve ser pegado os pacotes
1 => 2 => 3 => PM
#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da fila de prioridade
typedef struct PriorityQueueNode {
    int packageID;                    // Identificador do pacote (por exemplo, 1, 2, 3, 9)
    int priority;                     // Prioridade do pacote (ordem de coleta)
    struct PriorityQueueNode *next;   // Ponteiro para o próximo nó
} PriorityQueueNode;

// Estrutura da fila de prioridade
typedef struct {
    PriorityQueueNode *head; // Ponteiro para o início da fila (pacote de maior prioridade)
} PriorityQueue;
Árvores de estados
Usado para rastrear se o robô já passou por esse caminho
Ainda não sei se iremos reiniciar ela a cada captura de pacote
Vamos lá! Vou te explicar a árvore de estados de forma simples e direta, cobrindo os pontos essenciais e como ela pode ser útil no seu projeto.
O que é uma Árvore de Estados?
Uma árvore de estados é uma estrutura de dados que armazena diferentes "estados" de uma situação ao longo de uma exploração ou navegação. O estado representa a posição do robô no labirinto e as condições daquele momento (como quais pacotes ele já pegou).

Cada nó da árvore representa um "estado" do robô, incluindo:

Coordenadas do robô (posição atual, ex: (x, y)).
Pacotes coletados até aquele ponto.
Movimentos feitos (isso pode ser implícito na estrutura da árvore).
A árvore se expande a partir do estado inicial e cria um novo ramo para cada nova direção que o robô toma. Dessa forma, ela vai representando todas as escolhas possíveis que ele pode fazer no labirinto.

Pontos de Atenção
Estrutura e Crescimento da Árvore:

A árvore cresce com cada novo estado, criando "ramos" para todas as decisões possíveis.
Como o robô explora o labirinto, a árvore vai se expandindo.
Balanceamento da Árvore:

Não é necessário balanceamento. Como ela serve apenas para armazenar as posições exploradas e evitar caminhos redundantes, não precisamos que ela esteja organizada para buscas rápidas.
Uso de Memória:

A árvore pode crescer muito dependendo do tamanho do labirinto, mas os dados armazenados são relativamente pequenos: coordenadas e pacotes coletados. É importante liberar memória quando estados antigos não são mais necessários.
Como Usar a Árvore no Projeto
Cada nó da árvore vai armazenar informações importantes sobre o estado do robô:

Coordenadas (x, y):

A posição atual do robô no labirinto, essencial para entender onde ele está em cada estado.
Pacotes Coletados:

Um registro de quais pacotes o robô já pegou para evitar duplicações. Pode ser uma lista ou um valor de flag para cada pacote.
Referência ao Estado Pai:

Cada nó pode ter um ponteiro para o estado anterior (ou "pai"), que representa de onde o robô veio. Isso é útil para traçar o caminho de volta, se necessário.
Exemplo Visual Simplificado
Imaginando que o robô começa no ponto (0,0) e se move para três posições diferentes (1,0), (0,1), (1,1):

              (0,0) [pacotes: nenhum]
             /      \
        (1,0)       (0,1)
        [pacotes: 1]   [pacotes: 1, 2]
                |
            (1,1)
        [pacotes: 1, 2, 3]
Estrutura da Árvore de Estados
typedef struct StateNode {
    int x, y;                   // Coordenadas do estado no labirinto
    int collectedPackages;      // Estado dos pacotes coletados representado por bits
    struct StateNode *parent;   // Estado anterior
    struct StateNode *north;    // Estado ao norte
    struct StateNode *south;    // Estado ao sul
    struct StateNode *east;     // Estado a leste
    struct StateNode *west;     // Estado a oeste
} StateNode;

Detalhes da Estrutura
Coordenadas (x, y): Define a posição do robô no labirinto para cada estado.
collectedPackages: Armazena os pacotes que o robô já coletou até aquele ponto, para garantir que o robô não tente recolher o mesmo pacote duas vezes.
Ponteiro parent: Aponta para o estado anterior, o que permite rastrear o caminho que o robô percorreu até aquele estado. Isso é útil para o caso de precisar retroceder na árvore.
Direções (north, south, east, west): Cada ponteiro conecta o estado atual aos estados vizinhos no labirinto. Esses ponteiros ajudam o robô a explorar novos estados a partir da posição atual.
Funcionamento Geral
Navegação: Quando o robô se move para uma nova posição, ele cria um novo StateNode na árvore que representa o estado alcançado após o movimento.
Verificação de Estados Visitados: Antes de adicionar um novo estado, o robô verifica se esse estado já existe na árvore (baseado em x, y e collectedPackages). Se o estado já foi visitado, ele é ignorado.
Exploração Completa: O robô usa a árvore para explorar todas as direções possíveis (norte, sul, leste, oeste) a partir de cada posição, mas evita revisitar estados, o que ajuda a reduzir o número de movimentos redundantes.
Retrocesso: Quando o robô atinge um beco sem saída ou um ponto sem novos caminhos viáveis, ele pode retroceder usando o ponteiro parent, voltando ao último estado antes de explorar um novo caminho.
Equilíbrio da Árvore
A árvore de estados cresce conforme o robô explora o labirinto, mas não há necessidade de balanceá-la, pois ela não é usada para buscas rápidas ou binárias. Em vez disso, a árvore representa uma estrutura que se ramifica de acordo com os caminhos possíveis no labirinto.

Resumo
A árvore de estados ajuda a:

Mapear todos os caminhos explorados pelo robô.
Armazenar pacotes coletados e posições, evitando exploração de caminhos redundantes.
Evitar loops e becos sem saída, permitindo ao robô saber onde já esteve e o que já coletou.
Em resumo, com essa árvore, nosso robô consegue explorar o labirinto de forma mais inteligente, sabendo onde já esteve, o que já coletou e, se necessário, refazendo o caminho sem voltar para becos sem saída.

No nosso caso, usaremos uma árvore baseada em direções (Norte, sul, leste, oeste) em relação ao primeiro ponto

Diferença Entre a Árvore de Estados e a Pilha
Árvore de Estados:

Armazena um registro permanente dos estados que o robô já visitou, incluindo as coordenadas e pacotes coletados em cada ponto.
Serve para o robô saber onde já esteve e, principalmente, evitar revisitar caminhos que levariam a becos sem saída ou duplicar caminhos já explorados.
Ajuda a escolher novas direções a partir de um ponto ao evitar repetição.
Pilha:

Funciona como um histórico de movimentos recente, permitindo ao robô voltar rapidamente ao último ponto de decisão quando encontra um beco sem saída.
Permite um retrocesso rápido para estados anteriores, sem que o robô precise reavaliar posições e decisões.
Após pegar o pacote mestre e querer retornar ao ponto inicial, a pilha permite que o robô retorne sem reavaliar o labirinto.
Resumindo o Papel de Cada Estrutura
A árvore de estados ajuda a evitar redundância e fornece uma visão global do que já foi explorado no labirinto.
A pilha dá ao robô a habilidade de "voltar no tempo" para revisitar posições de maneira rápida e eficiente, especialmente em casos de becos sem saída ou na necessidade de retornar ao ponto inicial.
Essas duas estruturas juntas garantem que o robô navegue pelo labirinto de forma mais eficiente e organizada, aproveitando o melhor de cada estrutura de dados.

Documentação das Tarefas do Projeto Robot Maze
Este documento descreve cada tarefa principal do projeto Robot Maze e detalha o que cada módulo e funcionalidade precisa implementar. Essa documentação serve como guia para desenvolvimento e organização das etapas.

📌 Configuração Inicial do Repositório
Descrição:
Configurar o repositório com arquivos essenciais, incluindo .gitignore, Makefile ou CMakeLists.txt, para gerenciar a compilação. Inclua instruções de contribuição e organize a estrutura de diretórios conforme necessário.

Objetivos:

Adicionar um .gitignore adequado.
Configurar um sistema de compilação para facilitar o desenvolvimento e testes.
Definir o padrão de commits.
📌 Implementar Estrutura do Labirinto (maze.c e maze.h)
Descrição:
Desenvolver a estrutura de dados que representa o labirinto, com cada posição representada como um MazeNode, contendo informações de posição, tipo (vazio, obstáculo, pacote, etc.), e conexões com vizinhos.

Objetivos:

Criar o MazeNode com coordenadas, tipo e ponteiros para os vizinhos.
Implementar funções para inicializar e definir o tipo de cada posição.
Implementar funções para carregar e exibir o labirinto.
📌 Implementar Fila de Prioridade (queue.c e queue.h)
Descrição:
Implementar a fila de prioridade que organiza a ordem de coleta dos pacotes com base no tipo (1, 2, 3 e 9, sendo 9 o pacote mestre). A fila deve permitir a inserção e remoção em ordem de prioridade.

Objetivos:

Criar funções para inserir e remover elementos da fila com base na prioridade.
Garantir que os pacotes sejam priorizados corretamente.
📌 Implementar Pilha de Movimentos (movementsStack.c e movementsStack.h)
Descrição:
Criar uma pilha que armazene o histórico dos movimentos do robô. Cada movimento armazenado deve incluir a posição anterior para possibilitar o retorno.

Objetivos:

Implementar funções de empilhar e desempilhar movimentos.
Acompanhar o caminho percorrido e possibilitar "desfazer" movimentos.
📌 Implementar Árvore de Estados (stateTree.c e stateTree.h)
Descrição:
Implementar a árvore de estados, onde cada nó representa um estado explorado pelo robô. A árvore ajudará a controlar quais caminhos já foram explorados.

Objetivos:

Definir o nó da árvore para armazenar posição e estado dos pacotes.
Criar funções para inserir novos estados e verificar estados visitados.
📌 Desenvolver Funções de Navegação do Robô (robot.c e robot.h)
Descrição:
Implementar as funções que permitem ao robô se mover pelo labirinto e decidir o próximo movimento, baseando-se nas informações da árvore de estados e no labirinto.

Objetivos:

Implementar lógica de movimentação e navegação.
Atualizar o estado do robô ao se mover para novos nós.
📌 Implementar Interface com o Usuário (userInterface.c e userInterface.h)
Descrição:
Desenvolver uma interface de terminal para exibir o estado do robô e o labirinto ao usuário, permitindo interações como iniciar uma nova partida ou carregar um estado salvo.

Objetivos:

Exibir o labirinto e o progresso do robô.
Aceitar comandos do usuário para iniciar, carregar, ou sair do jogo.
📌 Implementar Funções de Impressão do Labirinto e Estado (print.c e print.h)
Descrição:
Desenvolver funções para imprimir o labirinto no terminal, incluindo a posição atual do robô e o status dos pacotes.

Objetivos:

Mostrar o labirinto e o robô de maneira visualmente clara.
Atualizar a exibição a cada movimento.
📌 Desenvolver a Função Principal (main.c)
Descrição:
Implementar a função principal do projeto que será responsável por iniciar o programa, carregar o labirinto e iniciar o loop principal do jogo.

Objetivos:

Coordenar a inicialização do labirinto e do robô.
Controlar o loop do jogo até a conclusão.
📌 Implementar Testes Unitários (tests/)
Descrição:
Criar testes para verificar a funcionalidade individual de cada módulo, cobrindo todos os casos importantes de uso e de erro.

Objetivos:

Testar cada função dos módulos Maze, Queue, Stack, Tree, e Robot.
Garantir que o código esteja funcionando corretamente e identificar falhas rapidamente.
📌 Implementar Funções de Liberação de Memória (memory.c e memory.h)
Descrição:
Desenvolver funções que liberem toda a memória alocada dinamicamente em cada módulo para evitar vazamentos.

Objetivos:

Garantir que todos os ponteiros alocados sejam liberados ao final do programa.
Documentar onde cada função deve ser chamada.
📌 Implementar Funcionalidade de Salvar e Carregar Estado do Robô
Descrição:
Desenvolver uma funcionalidade que permita salvar o estado atual do robô (posição, pacotes coletados, caminho percorrido) em um arquivo e carregá-lo futuramente.

Objetivos:

Salvar o estado completo do robô e do labirinto.
Carregar o estado salvo ao iniciar o programa para continuar o progresso.
📌 Otimizar Estruturas de Dados para Melhor Performance
Descrição:
Revisar e otimizar as estruturas de dados usadas para melhorar a performance e reduzir o uso de memória. Focar na eficiência de acesso e manipulação de dados.

Objetivos:

Implementar otimizações na árvore de estados e no armazenamento dos pacotes.
Reduzir o tempo de execução e o uso de memória.
📌 Adicionar Logs e Debugging
Descrição:
Adicionar logs que registrem ações importantes do robô e mudanças de estado, facilitando o processo de debugging.

Objetivos:

Implementar logging detalhado.
Permitir ativar/desativar logs para facilitar o debugging.
📌 Integração de Módulos e Testes Finais
Descrição:
Integrar todos os módulos e realizar testes finais para garantir que o sistema funcione corretamente como um todo. Validar o desempenho e usabilidade final do projeto.

Objetivos:

Integrar todos os módulos e garantir que trabalham juntos.
Realizar testes extensivos de uso e desempenho.
Cada módulo e funcionalidade deve ser implementada, testada, e integrada conforme o projeto avança. Esse guia deve ajudar a coordenar o desenvolvimento e garantir que todas as partes do projeto sejam cobertas.
