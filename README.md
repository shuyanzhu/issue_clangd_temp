# Project to [issue](https://github.com/clangd/vscode-clangd/issues/258)
## build
```bash
# note: I use clang13.0.1 as compiler which supports c++20
# You may need edit coroutine.cmake for your environment，I advice you comment CMakeLists.txt:6. Anyway, you can figure out easily.
mkdir build
cd build
cmake ..
make
```
## where is the problem
- example/asio_others/throttling_proxy.cpp:71, try "Go to definition" in transfer. I think it would be failed.
- main.cpp:62, I think "Go to definition" would work normal.