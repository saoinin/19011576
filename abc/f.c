#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE {//인접 정점 구조체
    int index;
    struct NODE* next;
}node;
typedef struct VER {//정점 구조체
    node* adjacent;
    int d;
    int p;
}ver;
typedef struct EDG {//간선 구조체
    int weight;
    int a;
    int b;
}edg;
typedef struct GRAPH {//정점과 간선이 있는 그래프 구조체
    ver* vertices;
    edg* edges;
}graph;
typedef struct QUEUE {//큐 구조체
    int key;
    int removed;//제거되었다면 1 아니라면 0
}queue;
int n;
int m;
int M = 0;//간선 생성과정에서 하나씩 카운트 하면서
int MST = 0;//최소신장트리
graph* G;
queue* Q;

void PrinmJarnikMST();
void init();
void insertVerAdj(int a, int b);
void arrangeVerAdj(int a);
node* getnode(int i);
void insertEdge(int a, int b, int w);
int findEdg(int a, int b);
void QreplaceKey(int e, int k);
int QisEmpty();
int QremoveMin();
void freeAll();
void QreplaceKey(int e, int k) {//키교체
    Q[e].key = k;//e번째 큐의 키를 k로 바꿈
    return;
}


int main() {
    int u, v, w;
    
    return 0;
}