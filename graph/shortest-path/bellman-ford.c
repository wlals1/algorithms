#include <stdio.h>
#include <stdlib.h>
#define MAX_V 1000
#define MAX_E 10000
#define INF 987654321

typedef struct Edge {
  int u, v, w;
} Edge;
Edge edges[MAX_E];
int dist[MAX_V];

int bellman_ford(int start, int n, int E) {
  for (int i = 0; i < n; i++)
    dist[i] = INF;
  dist[start] = 0;

  for (int round = 0; round < n - 1; round++) {
    for (int i = 0; i < E; i++) {
      Edge e = edges[i];
      if (dist[e.u] == INF)
        continue;
      int new_dist = dist[e.u] + e.w;
      if (new_dist < dist[e.v]) {
        dist[e.v] = new_dist;
      }
    }
  }

  for (int i = 0; i < E; i++) {
    Edge e = edges[i];
    if (dist[e.u] == INF)
      continue;
    if (dist[e.u] + e.w < dist[e.v])
      return 1;
  }
  return 0;
}

int main(void) {
  int n = 5; // 정점 0~4
  int E = 0;

  // 음수 간선 포함, 단 음수 사이클은 없음
  edges[E++] = (Edge){0, 1, 6};
  edges[E++] = (Edge){0, 2, 7};
  edges[E++] = (Edge){1, 2, 8};
  edges[E++] = (Edge){1, 3, 5};
  edges[E++] = (Edge){1, 4, -4}; // 음수!
  edges[E++] = (Edge){2, 3, -3}; // 음수!
  edges[E++] = (Edge){2, 4, 9};
  edges[E++] = (Edge){3, 1, -2}; // 음수!
  edges[E++] = (Edge){4, 0, 2};
  edges[E++] = (Edge){4, 3, 7};

  int has_neg_cycle = bellman_ford(0, n, E);

  if (has_neg_cycle) {
    printf("Negative cycle detected!\n");
  } else {
    for (int i = 0; i < n; i++) {
      if (dist[i] == INF)
        printf("dist[%d] = INF (unreachable)\n", i);
      else
        printf("dist[%d] = %d\n", i, dist[i]);
    }
  }
  return 0;
}