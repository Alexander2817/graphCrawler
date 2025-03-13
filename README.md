# Graph Crawler

This program is a graph crawler that performs a breadth-first search (BFS) from a starting node. It uses libcurl to request data from an API and RapidJSON to parse JSON data. The program prints the nodes reachable from the start node within a given depth.

## Requirements

1. **libcurl**: A library for making HTTP requests.
   - On Ubuntu/Debian:
     ```bash
     sudo apt install libcurl4-openssl-dev
     ```
   - On macOS:
     ```bash
     brew install curl
     ```

2. **RapidJSON**: A fast JSON parser for C++.
   - On Mac or Windows install using:
     ```bash
     git clone https://github.com/Tencent/rapidjson.git
     cd rapidjson
     mkdir build && cd build
     cmake ..
     sudo make install
     ```

     If this does not work, you can directly include the RapidJSON headers by specifying the path in your
compilation command. Assuming the cloned folder is in your home directory:

## Compilation

1. Clone the repository or download the `graph_crawler.cpp`, `Makefile`, and `README.md` files.
   
2. Update the Makefile RAPIDJSON_PATH to where you cloned rapidjson into.

3. To compile the program, run the following command in the terminal:
   ```bash
   make
   ```
   If the Makefile does not work, use the following command in the terminal:
   ```bash
   g++ -Wall -std=c++11 -I ./rapidjson/include graph_crawler.cpp -o graph_crawler -lcurl
   ```

   
