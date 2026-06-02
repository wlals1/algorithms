#include <stdio.h>
#include <stdlib.h>
#define MAX_V 1000
#define INF 987654321

typedef struct Node {
  int v, w;
  struct Node *next;
} Node;

typedef struct HNode {
  int v, w;
} HNode;

int dist[MAX_V];
Node *graph[MAX_V];
HNode heap[MAX_V * MAX_V];
int idx = 0;

void insert_edge(int u, int v, int w) {
  Node *new = calloc(1, sizeof(Node));
  new->v = v;
  new->w = w;
  new->next = graph[u];
  graph[u] = new;

  new = calloc(1, sizeof(Node));
  new->v = u;
  new->w = w;
  new->next = graph[v];
  graph[v] = new;
}

void push(int v, int w) {
  heap[++idx] = (HNode){v, w};
  int t = idx;
  while (t / 2 > 0 && heap[t].w < heap[t / 2].w) {
    HNode tmp = heap[t];
    heap[t] = heap[t / 2];
    heap[t / 2] = tmp;

    t /= 2;
  }
}

HNode pop(void) {
  HNode ret = heap[1];
  heap[1] = heap[idx--];
  int t = 1;
  while (t * 2 <= idx) {
    int child = t * 2;
    if (child + 1 <= idx && heap[child + 1].w < heap[child].w)
      child++;
    if (heap[t].w <= heap[child].w)
      break;
    HNode tmp = heap[t];
    heap[t] = heap[child];
    heap[child] = tmp;

    t = child;
  }
  return ret;
}

void dijkstra(int start, int v) {
  for (int i = 0; i < v; i++)
    dist[i] = INF;

  push(start, 0);
  dist[start] = 0;

  while (idx != 0) {
    HNode cur = pop();
    if (dist[cur.v] < cur.w)
      continue;

    for (Node *nxt = graph[cur.v]; nxt; nxt = nxt->next) {
      int new_dist = dist[cur.v] + nxt->w;
      if (new_dist < dist[nxt->v]) {
        dist[nxt->v] = new_dist;
        push(nxt->v, new_dist);
      }
    }
  }
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
  int n = 5;
  insert_edge(0, 1, 4);
  insert_edge(0, 2, 1);
  insert_edge(2, 1, 2);
  insert_edge(1, 3, 1);
  insert_edge(2, 3, 5);
  insert_edge(3, 4, 3);

  dijkstra(0, n);

  for (int i = 0; i < n; i++)
    printf("dist[%d] = %d\n", i, dist[i]);
  // 기대: 0, 3, 1, 4, 7
  return 0;
}
