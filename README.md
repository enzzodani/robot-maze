# Robot Maze Solver

Este projeto implementa um robô que navega em um labirinto, coletando pacotes em locais específicos, com um "pacote mestre" de prioridade máxima. A estrutura inclui diferentes módulos que permitem ao robô planejar e registrar seus movimentos, bem como avaliar o ambiente em busca de objetivos.

## Estrutura do Projeto

O projeto é dividido em módulos para manter o código organizado e facilitar o desenvolvimento. Cada módulo é responsável por uma funcionalidade essencial:

- **Main**: Ponto de entrada do programa, gerencia a interação com o usuário e a execução principal.
- **Maze**: Representa o labirinto e fornece acesso aos nós, rotas, obstáculos e pacotes.
- **Queue**: Implementa uma fila de prioridade para determinar a ordem de coleta dos pacotes.
- **Movements Stack**: Uma pilha para rastrear o histórico de movimentos do robô.
- **State Tree**: Armazena o histórico de estados do robô, representando suas posições e pacotes coletados.

## Instalação e Execução

### Compilação

Para compilar o projeto, execute o comando:

```bash
gcc -o robot_maze main.c maze.c queue.c stateTree.c movementsStack.c -Wall
```

### Execução

Após a compilação, execute o programa com:

```bash
./robot_maze
```

## Documentação

Para detalhes completos de implementação e design, consulte a documentação:
- **[Docmentação Geral](docs/doc_geral.md)** 
