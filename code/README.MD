# Solver Pseudocode
```
take image of top face (U)
create rgb matrix of face
perform L->D rotation

take image of top face (R)
create rgb matrix of face
rotate mat CCW
perform B->D rotation

take image of top face (F)
create rgb matrix of face
rotate mat CCW
perform L->D rotation

take image of top face (D)
create rgb matrix of face
rotate mat CCW
perform B->D rotation

take image of top face (L)
create rgb matrix of face
rotate mat 2CW
perform L->D rotation

take image of top face (B)
rotate mat 2CW
create rgb matrix of face

build rgb matrix
cluster and label rgb matrix
create cube from clustered matrix
create cube solution from matrix

transform sequence minimizing up and down

execute moveset
```