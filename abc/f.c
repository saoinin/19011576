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
void PrinmJarnikMST() {
    ver* s;
    node* h;
    int find;
    int u, z, w;
    Q = (queue*)malloc(sizeof(queue) * (n + 1));//큐동적할당 정점개수+1
    for (int i = 1; i <= n; i++) {//0번째 인덱스는 사용하지 않음
        G->vertices[i].d = 100000;//큰수로 초기화하자 무한대를 뜻함
        G->vertices[i].p = -1;//이어진 선을 뜻함
        Q[i].key = G->vertices[i].d;//QreplaceKey()를 호출해도 되지만 교체가 아닌 초기화이니까 그냥 넣어준다.
        Q[i].removed = 0;//0으로 초기화 삭제 여부
    }
    s = &(G->vertices[1]);//시작점인 인덱스 1
    s->d = 0;//1의 거리는 0으로 만들어줌
    QreplaceKey(1, 0);//d를 바꿔줄때는 큐의 키도 교체해준다.
    while (QisEmpty() == 0) {//큐가 빌때까지 반복
        u = QremoveMin();//가장 작은 큐의 인덱스 u
        printf(" %d", u);//출력
        h = G->vertices[u].adjacent;//정점 u의 인접정점 포인터 h
        h = h->next;//첫번째는 헤더이니 넘기고
        while (h != NULL) {//인접정점 전부 돌리면서
            z = h->index;//인접정점의 인덱스 z
            find = findEdg(u, z);//u와 z사이의 간선을 찾자 find는 해당간선의 인덱스
            w = G->edges[find].weight;//그간선의 가중치 w
            if (Q[z].removed == 0 && (w < G->vertices[z].d)) {//큐에서 삭제되지 않았고 w가 큐에서 해당인덱스 키값보다 작다면
                G->vertices[z].d = w;//도착한 정점의 거리를 갱신하고
                G->vertices[z].p = find;//그 정점까지 간 선을 p에 저장
                QreplaceKey(z, w);//큐도 갱신
            }
            h = h->next;//인접정점 넥스트
        }
    }
    for (int i = 1; i <= n; i++) {//정점 1~ n까지
        if (G->vertices[i].p != -1) {//초기값은 전부 -1이고 사용한 간선은 p에 저장됨
            int E = G->vertices[i].p;//간선 인덱스의
            int W = G->edges[E].weight;//가중치를 찾아
            MST += W;//다 더하고
        }
    }
    printf("\n%d", MST);//MST 총무게를 출력하자.
}
node* getnode(int i) {//노드(인접정점 구조체)생성 함수
    node* new = (node*)malloc(sizeof(node));
    new->index = i;
    new->next = NULL;
    return new;
}
int findEdg(int a, int b) {//해당되는 간선의 인덱스를 찾아주는 함수
    for (int i = 1; i <= M; i++) {
        if (G->edges[i].a == a && G->edges[i].b == b || G->edges[i].a == b && G->edges[i].b == a) {
            //무방향이므로 a b는 서로 바뀔수 있기에 이런 조건
            return i;
        }
    }
    return 0;
}
void init() {//이것저것 전부 초기화해주는 함수
    G = (graph*)malloc(sizeof(graph));//G 동적할당
    G->vertices = (ver*)malloc(sizeof(ver) * (n + 1));//정점구조체배열
    G->edges = (edg*)malloc(sizeof(edg) * (m + 1));//간선구조체배열
    //간선의 구조체배열 정점의 구조체 배열 모두 0번째를 헤더대용으로 사용한다.
    for (int i = 1; i <= n; i++) {
        G->vertices[i].adjacent = getnode(-1);
    }
    //각 정점배열에 인접리스트의 헤더를 동적할당해 만들어준다.
}
void insertEdge(int a, int b, int w) {//간선추가 함수
    M++;//간선 개수 +1
    G->edges[M].a = a;
    G->edges[M].b = b;
    G->edges[M].weight = w;//구조체배열 해당인덱스에 추가
    insertVerAdj(a, b);//인접리스트 추가
    if (a != b) {//a와 b가 같다면 한번만 추가해도 되지만 다르다면 a기준 한번 b기준 한번
        insertVerAdj(b, a);
    }
}
void insertVerAdj(int a, int  b) {//인접리스트 추가
    node* p = G->vertices[a].adjacent;
    while (p->next != NULL) {//마지막노드로 이동
        p = p->next;
    }
    p->next = getnode(b);//그 다음에 노드추가
    arrangeVerAdj(a);//정렬
}
void arrangeVerAdj(int a) {//a정점의 인접리스트 정렬
    node* p = G->vertices[a].adjacent->next;//첫번째는 헤더니까 그다음 노드
    node* q;
    int tmp;
    while (p->next != NULL) {//정렬을 위한 p와 q 위치 조정
        q = p->next;//q는 p 오른쪽
        while (q != NULL) {//오른쪽 끝까지
            if (p->index > q->index) {//비교후
                tmp = p->index;//오름차순이 되게 뒤바꿈
                p->index = q->index;
                q->index = tmp;
            }
            q = q->next;
        }
        p = p->next;
    }
}


int main() {
    int u, v, w;
    scanf("%d %d", &n, &m);
    init();//초기화 동적할당 과정
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        insertEdge(u, v, w);
    }

    
    
    return 0;
}