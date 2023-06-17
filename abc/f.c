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
int QisEmpty() {//큐가 비어있는지 확인
    int count = 0;
    for (int i = 1; i <= n; i++) {
        count += Q[i].removed;//비어있다면 1이기때문에 카운트
    }
    if (count == n) {//정점의 개수만큼 카운트 됐다면
        return 1;//1 반환
    }
    else {
        return 0;//아니라면 0반환
    }
}
int QremoveMin() {//가장 작은 큐 인덱스 반환
    int a;
    int Min = 100000;
    //큰 수 Q의 초기값이기도 하지만 프로그램이 정상 작동한다면 이 숫자가 Min이 될 일은 없음
    for (int i = 1; i <= n; i++) {
        if (Q[i].removed == 1) {//삭제된 큐는 넘기자
            continue;
        }
        a = Q[i].key;//큐의 키를 구하고
        if (a < Min) {//Min보다 작냐
            Min = a;//Min 갱신
        }
    }
    for (int i = 1; i <= n; i++) {//Min에 해당되는 인덱스를 찾자
        //만약 같은 거리가 있다면 더 작은 인덱스를 고를것임
        if (Q[i].key == Min && Q[i].removed == 0) {//삭제되지 않았고 키가 Min이라면
            Q[i].removed = 1;//삭제해주고
            return i;//인덱스 반환
        }
    }
}


int main() {
    int u, v, w;
    
    return 0;
}