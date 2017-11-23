# Considerations for Programming
## Motor Motion Strategies
### State Machine
Keep a detailed state of all positions of all components:

```
F, B, L, R Grabbers:    Vertical or Horizontal
FB, LR Belts:           Extended, Retracted, Partially Extended
```

Use this state to plan certain motions (ie. face rotate, cube rotate), without entering an invalid state.

This method is difficult to get working correctly, as there are 2^4*3^2 possible states, and it is hard to consider them all.

### Search/Expand Operaetions
Do a search on all possible moves (there's actually not that many), that leads to our desired state.

In such a search, only expand nodes that lead to a valid state, and only expand nodes that lead to our desired state. With these conditions, very few moves actually need to be explored.
Don't expand nodes that change the cube state. We know we are done we are allowed to perform the elementary operation that leads us directly to our desired state.

An advantage of this strategy is that we can weight operations by their cost (extending arms is much slower than rotating an arm). 
Using a shortest path algorithm, we easily find a time optimized solution to perform a move.

This strategy may be computationally expensive.

```
Node Expansion Rules by Elementary Operation:

Rotate Face
- perpendicular grabbers must be vertical
- parallel grabbers must be retracted
- perpendicular grabbers must be retracted

Double Rotate Face
...

Extend/Retract Arm to State
- Extend case:

- Retract case:

- Partial case: we should probably just scrap partial

Double Extend/Retract Arm to State
```
### Dependency Graph
Each operation (ie. rotating a face, rotating the cube) has a list of dependencies (ie. perpendicular grabbers must be vertical).

Enumerate all dependencies for each operation. In turn, also enumerate dependencies of dependencies. The result will be a dependency graph with no cycles, with the leaf nodes being simple operations (rotate a face, extend an arm etc.).

In order to perform the operation, recursively satisfy all dependencies first.

An advantage of this strategy is that it is less likely to accidentally enter an invalid state.

A disadvantage of this strategy is that it is difficult to enumerate all dependencies for an operation, and a mistake would be difficult to find.

## Solver Pseudocode
```
take image of top face (U)
create rgb matrix of face
perform L->D rotation

take image of top face (R)
create rgb matrix of face
rotate mat CW
perform L->D rotation

take image of top face (B)
create rgb matrix of face
rotate mat 2CW
perform L->D rotation

take image of top face (L)
create rgb matrix of face
rotate mat CCW
perform F->D rotation

take image of top face (F)
create rgb matrix of face
rotate mat CCW
perform F->D rotation x2

take image of top face (B)
create rgb matrix of face
rotate mat CCW

build rgb matrix
cluster and label rgb matrix
create cube from clustered matrix
create cube solution from matrix

transform sequence minimizing up and down

execute moveset
```
