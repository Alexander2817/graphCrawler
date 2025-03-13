#include <string>
#include <vector>
#include <chrono>
#include <curl/curl.h>
#include "rapidjson/document.h"
#include <iostream>
#include <queue>
#include <algorithm>

/**
 * @brief Write data to a std::string
 *
 * This function is a callback for libcurl that writes the response data to a std::string.
 *
 * @param ptr The data to write
 * @param size The size of the data element
 * @param nmemb The number of elements in the data array
 * @param userdata The std::string to which the data is to be written
 *
 * @return The number of elements written
 */
size_t my_write_data(char *ptr, size_t size, size_t nmemb, void *userdata) {
    std::string *outstring = (std::string *)userdata;
    for (size_t i = 0; i < size * nmemb; i++) {
        outstring->push_back(ptr[i]);
    }
    return nmemb * size;
}

/**
 * @brief Get the neighbors of a node in the graph
 *
 * @param node The node whose neighbors are to be found
 *
 * @return A vector of strings containing the neighbors of the node
 */
std::vector<std::string> getting_neighbors(const std::string &node) {
    std::vector <std::string> neighbors;
    std::string url = "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/" + node;
    std::string myoutstring;
    
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &myoutstring);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write_data);

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    /**Testing for debugging purposes visual inspection
    std::cout << "Raw response for " << node << ": " << std::endl;
    std::cout << myoutstring << std::endl;
      */
    rapidjson::Document d;
    d.Parse(myoutstring.c_str());

    // Check if the response is valid JSON
    if (d.HasParseError() || !d.IsObject()) {
        return neighbors;
    }

    //The neighbors are stored in the "neighbors" array in the JSON
    for (rapidjson::Value::ConstValueIterator itr = d["neighbors"].Begin(); itr != d["neighbors"].End(); ++itr) {
        neighbors.push_back(itr->GetString());
    }
    return neighbors;
}

/**
 * @brief Perform a breadth first search of the graph from the given node
 *
 * @param start The node to start at
 * @param depth The maximum depth of the search
 *
 * The function performs a breadth first search of the graph from the given node
 * and prints the nodes at each level of the search. The search is limited to
 * the given depth. If the depth is zero, the function will return immediately.
 */
void bfs(const std::string &start, int depth) {
    std::queue<std::string> q;
    std::vector<std::string> visited;
    q.push(start);
    visited.push_back(start);
    for (int l = 0; l < depth && !q.empty(); l++) {
        int level = q.size();

        for (int i = 0; i < level; i++) {
            std::string current = q.front();
            q.pop();
            std::vector<std::string> neighbors = getting_neighbors(current);
            for(const std::string &neighbor : neighbors) {
                auto it = std::find(visited.begin(), visited.end(), neighbor);
                if (it == visited.end()) {
                    visited.push_back(neighbor);
                    q.push(neighbor);
                }
            }
        }
        std::cout << std::endl;
    }

}
/**
 * @brief Main function for the graph crawler
 *
 * @param argc The number of command line arguments
 * @param argv The command line arguments
 *
 * The program takes two command line arguments, the starting node and the depth of the crawl.
 * The program will then perform a breadth first search of the graph from the starting node
 * and print out all the nodes that are reachable within the specified depth. The program will
 * also print out the time taken to complete the search.
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./graph_crawler <start_node> <depth>" << std::endl;
        return 0;
    }
    
    std::string start = argv[1];
    int depth = std::stoi(argv[2]);

    auto start_time = std::chrono::high_resolution_clock::now();
    bfs(start, depth);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken: " << duration.count() << "ms" << std::endl;

    return 0;
}