#ifdef MAZE_H
#define MAZE_H

typedef struct mazeNode {
    int x,y; //Coordenadas do labirinto
    int type; //0=vazio 1,2,3=pacotes 7=obstaculo 9=pacote mestre
    mazeNode* north,south,west,east; //Vizinhos
} mazeNode;

mazeNode* createNode(int x, int y, int type);
mazeNode* initMaze(int lines, int columns);
void linkNodes();
int isObstacle(MazeNode* node);
void freeMaze();
void insertStart(Node *newNode, List *list);
void insertEnd(Node *newNode, List *list);

#endif // MAZE_H
