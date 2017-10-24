Add/remove notes as you see fit

## Project Structure
```
bin/        - compiled binaries
obj/        - storage for object files to reduce recompilation
src/        - .c        implementation
include/    - .h        headers
lib/        - .so .a    external lib
```
note: headers files outside of `include/` will not be included compile-time<br>
note: source files outside of `src/` will not be compiled

## Building
```
cd code
make
```
`make run` to execute immediately.<br>
`make clean` to remove binaries.

**Make sure the program is executed from the `bin/` directory**, since many cache files are generated.

## Code Style
- avoid polluting global namespace with short global variables
- attach meaningful prefixes to global functions/variables
- avoid defining short or generic macros
- fix all compile warnings immediately
- split implementation into simple parts
- validate input, use `LOG()` in `util/log.h` for error messages rather than printf

## 3rd Party
ckociemba - 3x3x3 rubik's cube solution search