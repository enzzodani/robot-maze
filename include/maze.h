#ifdef MAZE_H
#define MAZE_H

typedef struct mazeNode {
    int x,y; //Coordenadas do labirinto
    int type; //0=vazio 1,2,3=pacotes 7=obstaculo 9=pacote mestre
    mazeNode* north,south,west,east; //Vizinhos
} mazeNode;

#endif // MAZE_H
