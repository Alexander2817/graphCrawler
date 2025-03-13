CXX = g++
CXXFLAGS = -Wall -std=c++11
LIBS = -lcurl

RAPIDJSON_PATH = /mnt/c/Users/Alex/parallel/rapidjson

INCLUDES = -I $(RAPIDJSON_PATH)

all: graph_crawler

graph_crawler: graph_crawler.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) graph_crawler.cpp -o graph_crawler $(LIBS)
