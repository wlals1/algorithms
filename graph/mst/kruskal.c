#include <stdio.h>
#include <stdlib.h>
#define MAX_E 10000
#define MAX_V 1000

typedef struct Edge {
  int u, v, w;
} Edge;

Edge edges[MAX_E];
Edge mst[MAX_V];

int parent[MAX_V];
int rank_[MAX_V];

void uf_init(int n) {
  for (int i = 0; i < n; i++) {
    parent[i] = i;
    rank_[i] = 0;
  }
}

int find(int x) {
  if (parent[x] != x)
    parent[x] = find(parent[x]);
  return parent[x];
}

void unite(int a, int b) {
  int ra = find(a), rb = find(b);
  if (ra == rb)
    return;
  if (rank_[ra] > rank_[rb]) {
    parent[rb] = ra;
  } else if (rank_[ra] < rank_[rb]) {
    parent[ra] = rb;
  } else {
    parent[ra] = rb;
    rank_[rb]++;
  }
}

int cmp(const void *a, const void *b) {
  Edge *ea = (Edge *)a, *eb = (Edge *)b;
  return (ea->w > eb->w) - (ea->w < eb->w);
}

int kruskal(Edge edges[], int E, int n, Edge mst[]) {
  qsort(edges, E, sizeof(Edge), cmp);
  uf_init(n);
  int mst_count = 0, total = 0;
  for (int i = 0; i < E; i++) {
    Edge min = edges[i];
    if (find(min.u) != find(min.v)) {
      unite(min.u, min.v);
      total += min.w;
      mst[mst_count] = min;
      mst_count++;
      if (mst_count == n - 1)
        break;
    }
  }
  return total;
}

int main(void) {
  int n = 4;
  int E = 5;

  edges[0] = (Edge){0, 1, 10};
  edges[1] = (Edge){1, 2, 5};
  edges[2] = (Edge){0, 2, 8};
  edges[3] = (Edge){2, 3, 3};
  edges[4] = (Edge){1, 3, 7};

  int total = kruskal(edges, E, n, mst);

  printf("MST total weight: %d\n", total); // 16 기대
  printf("MST edges:\n");
  for (int i = 0; i < n - 1; i++)
    printf("  %d - %d (w=%d)\n", mst[i].u, mst[i].v, mst[i].w);

  return 0;
}