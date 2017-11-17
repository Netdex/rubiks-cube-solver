# Solver Pseudocode
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