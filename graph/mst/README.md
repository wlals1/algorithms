# Minimum Spanning Tree

A **spanning tree** connects all vertices of a graph with no cycles, using
exactly `n-1` edges for `n` vertices. The **minimum** spanning tree is the
one whose total edge weight is smallest. Note this is a *tree* (an edge set
spanning all vertices), not a *path* — the route between two vertices inside
an MST is not necessarily their shortest path.

Two algorithms here find the same MST by opposite strategies.

## Kruskal — edge-centric

Sort all edges by weight, then take them cheapest-first, skipping any edge
that would form a cycle.

```
sort edges by weight ascending
for each edge (u, v, w) in order:
    if find(u) == find(v):   # already in the same component → cycle
        skip
    else:
        unite(u, v); accept edge
    stop once n-1 edges are accepted
```

The cycle test is the job of **union-find** (disjoint-set union): "are these
two endpoints already in the same group?" If yes, adding the edge closes a
cycle. Kruskal naturally takes an **edge list** (`{u, v, w}` array), since it
processes all edges in sorted order — vertex-centric adjacency lists don't
fit.

### Union-find

Union-find answers "same group?" and merges groups, both in near-constant
amortized time. Two optimizations together give **O(α(n))** amortized per
operation (α = inverse Ackermann, ≤ 5 for any realistic n):

- **Path compression** — `find` reattaches every node on the path directly to
  the root, flattening the tree so future lookups are fast.
- **Union by rank** — the shorter tree is attached under the taller one, so
  height stays O(log n).

A single operation can still be O(n) in the worst case (a deep first `find`);
the α(n) bound is *amortized* — the expensive operation flattens the tree and
pays for the cheap ones that follow. (This is a guarantee over a sequence of
operations, unlike the *average-case* O(1) of a hash table.)

## Prim — vertex-centric

Start from one vertex and grow a single tree, repeatedly absorbing the
cheapest edge that crosses from the tree to a vertex outside it.

```
put the start vertex in the tree
repeat until all vertices are in:
    among edges from the tree to outside, pick the minimum
    absorb that vertex into the tree
```

No cycle check is needed: only vertices *outside* the tree are absorbed, so a
just-added vertex connects to the tree for the first time — a cycle can never
form. The "minimum crossing edge" is found with a **min-heap**, and the graph
is stored as an **adjacency list** (vertex-centric). When an edge is popped
whose endpoint is already in the tree, it is discarded.

## Kruskal vs Prim

| | Kruskal | Prim |
|---|---|---|
| Strategy | sort all edges, take cheapest | grow one tree from a seed |
| "Minimum" of | all edges | edges crossing the tree boundary |
| Cycle prevention | union-find test | absorb only outside vertices (automatic) |
| Data structures | edge list + union-find | adjacency list + min-heap |
| Intermediate state | a forest (several pieces) | always one connected tree |

Both produce the same total weight (the MST is unique when edge weights are
distinct). The choice is about graph shape: Kruskal suits sparse graphs given
as an edge list; Prim suits denser graphs given as adjacency lists.

## Complexity

| | Time |
|---|---|
| Kruskal | O(E log E) — dominated by the sort |
| Prim (binary heap) | O(E log V) |

## Files

| File            | Contents                                   |
|-----------------|--------------------------------------------|
| `kruskal.c`     | Kruskal + union-find (path compression, rank) |
| `prim.c`        | Prim with a hand-written binary min-heap   |

## References

- Cormen et al., *Introduction to Algorithms*, Chapter 21 (MST), Chapter 19
  (disjoint sets)
