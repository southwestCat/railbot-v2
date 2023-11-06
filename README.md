# RailBot
> version 2.0. Parsing LoLA protocol using nlohmann/json library.

## Requires
- [nlohmann/json](https://github.com/nlohmann/json)

Install [eigen-quadprog](https://github.com/jrl-umi3218/eigen-quadprog) and copy /usr/local/lib/libeigen-quadprog.so.1.1.2 to nao as the same path.


## Build
+ Create a build directory, named `_build`.

  ```bash
  cd _build
  ```
+ Run `cmake`.

  ```bash
  cmake ..
  ```

+ `make`

  ```bash
  make -j
  ```