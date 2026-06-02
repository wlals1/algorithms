# Shortest Path

Three algorithms for shortest paths in a weighted graph, differing in what
they handle (negative edges, all-pairs) and how fast they are.

## Dijkstra — single source, non-negative weights

Grows shortest distances outward from a start vertex, always finalizing the
closest unfinalized vertex next. Uses a **min-heap** keyed by distance, and
**relaxation**: when a shorter route to `v` is found through `u`, update
`dist[v] = dist[u] + w`.

```
dist[start] = 0, rest = INF
push (start, 0)
while heap not empty:
    pop the vertex u with smallest distance
    skip if a shorter dist[u] is already known   # stale heap entry
    for each edge u → v (weight w):
        if dist[u] + w < dist[v]:
            dist[v] = dist[u] + w; push (v, dist[v])
```

The heap entry carries the **vertex and its accumulated distance** `{v, dist}`
— the distance alone wouldn't say which vertex it belongs to.

**Why non-negative only.** Dijkstra finalizes a vertex once popped, trusting
that distances only grow as more edges are added. A negative edge breaks that:
a longer-looking path could become shorter later, so a finalized distance
might be wrong. Dijkstra assumes monotonic growth; negative edges violate it.

## Bellman-Ford — single source, negative edges allowed

Gives up the greedy "finalize the closest" idea. Instead it **relaxes every
edge, V-1 times**.

```
dist[start] = 0, rest = INF
repeat V-1 times:
    for each edge (u, v, w):
        if dist[u] != INF and dist[u] + w < dist[v]:
            dist[v] = dist[u] + w
# one more pass: if anything still relaxes, there is a negative cycle
```

**Why V-1 passes.** A shortest path is simple (no repeated vertices), so it
uses at most V-1 edges. Each full pass propagates shortest distances one more
edge outward, so V-1 passes settle every shortest path. If a V-th pass still
relaxes something, a path keeps shrinking past V-1 edges — a **negative
cycle** — which Bellman-Ford reports.

The `dist[u] != INF` guard matters: relaxing from an unreached vertex would
compute `INF + w`, corrupting distances (and risking overflow). Slower than
Dijkstra (O(VE)) but handles negatives and detects negative cycles.

## Floyd-Warshall — all pairs

Computes the shortest distance between *every* pair `dist[i][j]` at once, by
dynamic programming over which vertices may be used as intermediates.

```
dist[i][j] = weight of edge i→j, 0 if i==j, INF otherwise
for k in 0..V-1:            # allow vertex k as an intermediate
    for i in 0..V-1:
        for j in 0..V-1:
            if dist[i][k] + dist[k][j] < dist[i][j]:
                dist[i][j] = dist[i][k] + dist[k][j]
```

**Why k is the outermost loop.** After the `k` iteration finishes, `dist[i][j]`
is the shortest path using intermediates from `{0..k}`. Computing that
requires the `{0..k-1}` answers to be complete first — so the intermediate
`k` must be advanced one full pass at a time, outside `i` and `j`. The order
of the `k` values themselves doesn't change the result (the final set of
allowed intermediates is the same, and `min` is order-independent), but `k`
must stay outermost.

This rests on **optimal substructure**: a sub-path of a shortest path is
itself a shortest path, so a long route `i→k→j` can be built from the shorter
`i→k` and `k→j` answers. As with Bellman-Ford, guard against `INF + INF`
overflow — use a sentinel like `987654321`, never `INT_MAX`.

## When to use which

| | Source | Negative edges | Complexity | Structure |
|---|---|---|---|---|
| Dijkstra       | single | no (+ detects nothing) | O(E log V) | min-heap |
| Bellman-Ford   | single | yes (+ detects neg. cycle) | O(VE) | edge list |
| Floyd-Warshall | all pairs | yes | O(V³) | adjacency matrix |

- Non-negative, one source → **Dijkstra** (fastest).
- Negative edges, one source → **Bellman-Ford**.
- Every pair of distances → **Floyd-Warshall** (simple, good when V is small).

## Files

| File                | Contents                                  |
|---------------------|-------------------------------------------|
| `dijkstra.c`        | Dijkstra with a hand-written min-heap     |
| `bellman-ford.c`    | Bellman-Ford + negative-cycle detection   |
| `floyd-warshall.c`  | Floyd-Warshall, all-pairs DP              |

## References

- Cormen et al., *Introduction to Algorithms*, Chapter 22 (single-source),
  Chapter 23 (all-pairs)
