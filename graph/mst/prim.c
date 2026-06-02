#include <stdio.h>
#include <stdlib.h>
#define MAX_V 1000

typedef struct Node {
  int v, w;
  struct Node *next;
} Node;

typedef struct HNode {
  int u, v, w;
} HNode;

Node *graph[MAX_V];
HNode heap[MAX_V];
HNode mst[MAX_V];
int idx = 0;

void insert_edge(int u, int v, int w) {
  Node *n = calloc(1, sizeof(Node));
  n->v = v;
  n->w = w;
  n->next = graph[u];
  graph[u] = n;

  n = calloc(1, sizeof(Node));
  n->v = u;
  n->w = w;
  n->next = graph[v];
  graph[v] = n;
}

void push(int u, int v, int w) {
  heap[++idx] = (HNode){u, v, w};
  int i = idx;
  while (i / 2 > 0 && heap[i].w < heap[i / 2].w) {
    HNode tmp = heap[i];
    heap[i] = heap[i / 2];
    heap[i / 2] = tmp;
    i /= 2;
  }
}

HNode pop(void) {
  HNode ret = heap[1];
  heap[1] = heap[idx--];
  int i = 1;
  while (i * 2 <= idx) {
    int child = i * 2;
    if (child + 1 <= idx && heap[child + 1].w < heap[child].w)
      child++;
    if (heap[i].w <= heap[child].w)
      break;
    HNode tmp = heap[i];
    heap[i] = heap[child];
    heap[child] = tmp;

    i = child;
  }
  return ret;
}

int prim(int start, int n) {
  int *visit = calloc(n, sizeof(int));
  int total = 0, count = 0;
  push(-1, start, 0);

  while (idx != 0) {
    HNode min = pop();
    if (visit[min.v] == 1)
      continue;
    visit[min.v] = 1;
    total += min.w;
    count++;
    if (count == n)
      break;
    for (Node *nxt = graph[min.v]; nxt; nxt = nxt->next) {
      if (!visit[nxt->v]) {
        push(min.v, nxt->v, nxt->w);
      }
    }
  }
  free(visit);
  return total;
}

void free_graph(int n) {
  for (int i = 0; i <= n; i++) {
    Node *curr = graph[i];
    while (curr) {
      Node *del = curr;
      curr = curr->next;
      free(del);
    }
    graph[i] = NULL;
  }
}

int main(void) {
  int n = 4; // 정점 0~3

  insert_edge(0, 1, 10);
  insert_edge(1, 2, 5);
  insert_edge(0, 2, 8);
  insert_edge(2, 3, 3);
  insert_edge(1, 3, 7);

  int total = prim(0, n);                  // 시작점 0
  printf("MST total weight: %d\n", total); // 16 기대
  free_graph(n);
  return 0;
}