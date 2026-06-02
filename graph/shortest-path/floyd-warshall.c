#include <stdio.h>
#define INF 987654321
#define MAX_V 1000
#define MAX_E 10000

int dist[MAX_V][MAX_V];

void floyd(int n) {
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dist[i][k] != INF && dist[k][j] != INF &&
            dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }
}

int main() {
  int n = 4;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      dist[i][j] = (i == j) ? 0 : INF;

  dist[0][1] = dist[1][0] = 5;
  dist[0][3] = dist[3][0] = 10;
  dist[1][2] = dist[2][1] = 3;
  dist[2][3] = dist[3][2] = 1;

  floyd(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (dist[i][j] == INF)
        printf("INF ");
      else
        printf("%3d ", dist[i][j]);
    }
    printf("\n");
  }
}