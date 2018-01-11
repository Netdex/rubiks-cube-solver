rubik's cube solver (mirror repo, redacted)
===========================================
## What
Automates solving a standard 3x3x3 rubik's cube. Scans the cube with a webcam, 
then performs a generated solution.

Can also solve to a custom desired state, ie. a certain pattern.

![alt](https://i.imgur.com/vuocffM.png)

## 3rd Party
```
ckociemba   - 3x3x3 rubik's cube two-phase non-optimal solution search
bbbiolib    - beaglebone black gpio library
log.h       - c logging library
stb_image.h - image loader library
```