# Algorithms in C

Self-paced implementation of classical algorithms in C, organized by the
problem each one solves. Companion to the `data-structures` repository;
focus is on systems/server track preparation — clean code, memory safety,
and understanding *why* each algorithm is correct, not just how to write it.

## Contents

| Area  | Problem            | Implementations                          |
|-------|--------------------|------------------------------------------|
| Graph | Minimum spanning tree | Kruskal, Prim                         |
| Graph | Shortest path      | Dijkstra, Bellman-Ford, Floyd-Warshall   |

See each subdirectory's README for the comparison of approaches — when to
reach for which, and the trade-offs between them.

## Build conventions

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 -g -O0 <file>.c -o <name>
```

Each file is self-contained (algorithm + a small `main` that tests it
against a hand-checked graph). Every implementation is checked for warnings
under these flags and for leaks under valgrind.

## Layout

```
algorithms/
└── graph/
    ├── mst/              # Kruskal, Prim (+ union-find)
    └── shortest-path/    # Dijkstra, Bellman-Ford, Floyd-Warshall
```

## Environment

- WSL2 Ubuntu 24.04
- gcc 13.2
- valgrind 3.22
