mkdir build
g++ -std=c++17 src\main.cpp -o build\main.exe -Isrc src\libs\Table\Table.cpp src\libs\QueryParser\QueryParser.cpp
