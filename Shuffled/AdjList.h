#pragma once
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<string>
#include<map>
#include<iostream>
#include<stdlib.h>
#include<set>
#include<queue>
#include<stack>
#include<random>
using namespace std;

class AdjList {
private:
    //Number of vertices in the graph
    //int numV = 0;

    //Key = Song title |  Value = adjacency map of edges. adj map key = to | adj map value = weight, i.e  graph[from][to] = weight
    unordered_map<string, unordered_map<string, int>> graph;

public:
    //Use this as our insert edge function
    int numV = 0;

    void addSong(string song);

    //Returns the weight of an edge
    int getWeight(string from, string to);

    //Adjusts the weight of an edge between 2 songs. Adjust is a positive value that is going subtract from the current edge weight
    void adjustWeight(string from, string to, int adjust);

    //Returns the vector of adjacent songs sorted by weight
    vector<string> getAdjacent(string vertex);

    //Couts a recommended playlist from our database of size n from a given song source (Prim's)
    vector<string> makePlaylist(string src);

    //Couts whether or not there is a path between src and dest songs (BFS)
    bool isRelatedBFS(string src, string dest);

    //Couts whether or not there is a path between src and dest songs (DFS)
    bool isRelatedDFS(string src, string dest);

    //Returns a random song in our graph
    string shuffle();

    AdjList();

};
