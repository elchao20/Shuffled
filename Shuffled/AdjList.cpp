#include "AdjList.h"
#include <fstream>
#include <chrono>

AdjList::AdjList(){
    //Start of Data Parsing, will transfer to a class once working
    ifstream dataFile;
    dataFile.open("/Users/ericchao/Desktop/QTProjects/Shuffled/SpotifyData.csv");
    string name;
    string album;
    string artist;
    string danceability;
    string accoustics;
    string skipLine;

    getline(dataFile, skipLine, '\n');
    unordered_map<string, vector<string>> relations;
    if (dataFile.is_open())
    {
        for (int i = 0; i < 130000; i++)
        {
            getline(dataFile, name, ',');
            if (name.at(0) == '\"') {
                string tempName;
                getline(dataFile, tempName, '\"');
                name += tempName;
                name = name.substr(1);
                getline(dataFile, tempName, ',');
            }
            addSong(name);

            getline(dataFile, album, ',');
            if (album.at(0) == '\"') {
                string tempAlb;
                getline(dataFile, tempAlb, '\"');
                album += tempAlb;
                getline(dataFile, tempAlb, ',');
                album = album.substr(1);
            }
            for (string song : relations[album]) {
                adjustWeight(song, name, 25);
            }
            relations[album].push_back(name);


            getline(dataFile, artist, ']');
            string tempArtist;
            vector<string> currArtists;
            for (int i = 0; i < artist.length(); i++) {
                char c = artist.at(i);
                if (c == ' ' || c == '[') {
                    continue;
                }
                if (c == ',' || i == artist.length() - 1) {
                    for (string song : relations[tempArtist]) {
                        adjustWeight(song, name, 25);
                    }
                    relations[tempArtist].push_back(name);
                    tempArtist = "";
                    currArtists.push_back(tempArtist);
                    continue;
                }
                tempArtist += c;
            }
            string temp;
            getline(dataFile, temp, ',');


            getline(dataFile, danceability, ',');
            for (string song : relations[danceability]) {
                adjustWeight(song, name, 25);
            }
            relations[danceability].push_back(name);

            getline(dataFile, accoustics, '\n');
            for (string song : relations[accoustics]) {
                adjustWeight(song, name, 25);
            }
            relations[accoustics].push_back(name);
        }
    }
    else
    {
        cout << "Could Not Open File" << endl;
    }
    relations.clear();
}
//Adds a song to the graph
void AdjList::addSong(string song) {
    //If graph already contains the song, return without changing anything
    if (graph.find(song) != graph.end()) {
        return;
    }

    graph[song] = unordered_map<string, int>();
    //increment the number of verticies
    numV++;
}

//Returns weight of edge between 2 vertices
int AdjList::getWeight(string from, string to) {
    return graph[from][to];
}

//Adjusts the weight of a given edge
void AdjList::adjustWeight(string from, string to, int adjust) {
    //Using these variables to initialize values at graph[to][from] and graph[from][to] to 0 if they haven't already
    int currWeight1 = graph[from][to];
    int currWeight2 = graph[to][from];
    if (currWeight1 < 0) {
        currWeight1 = 0;
    }
    if (currWeight2 < 0) {
        currWeight2 = 0;
    }
    currWeight1 += adjust;
    currWeight2 += adjust;

    graph[from][to] = currWeight1;
    graph[to][from] = currWeight2;
}

//Returns adjacent songs to a given vertex sorted by weight
vector<string> AdjList::getAdjacent(string vertex) {
    //If vertex isn't found, then return an empty vector
    if (graph.find(vertex) == graph.end()) {
        cout << vertex << " is not in our database\n";
        return vector<string>();
    }

    //Initialize adjList and define adjacency map to be graph[vertex]
    vector<string> adjList;
    unordered_map<string, int> adjMap = graph[vertex];

    for (auto it : adjMap) {
        adjList.push_back(it.first);
    }
    return adjList;
}

//Outputs a list of songs that relate closest to the source song using Prim's algorithm
vector<string> AdjList::makePlaylist(string src) {

    //If the song a user is searching for isn't in our database, return nothing
    if (graph.find(src) == graph.end()) {
        return vector<string>();
    }
    vector<string> playlist;
    //Initializing a set of all songs our algorithm has processed so far
    set<string> visited;
    visited.insert(src);
    int n = 10;

    //Goes through each vertex in visited and gets all edge weights adjacent to them
    while (n > 0) {
        //Initializing a pair where p.first is the destination to the new vertex and p.second is the weight (want to find the minumum weight)
        pair<string, int> p = pair<string, int>("", 0);
        for (string from : visited) {
            vector<string> adjList = getAdjacent(from);
            for (string to : adjList) {
                if (visited.count(to) != 0) {
                    continue;
                }
                int currWeight = getWeight(from, to);
                if (currWeight > p.second) {
                    p.second = currWeight;
                    p.first = to;
                }
            }
        }
        //p.first.first is already in visited (the 'from' variable) p.first.second is the new vertex we visit (the 'to' variable)
        string newSong = p.first;
        if (p.first.compare("") == 0) {
            break;
        }
        //the new song is now processed so it will be added to the set of visited songs
        visited.insert(newSong);

        //put song in playlist
        playlist.push_back(newSong);
        n--;
    }

    return playlist;
}

//Checks if there's a path between 2 songs using BFS traversal
bool AdjList::isRelatedBFS(string src, string dest) {
    if (graph.find(src) == graph.end()) {
        return false;
    }
    if (graph.find(dest) == graph.end()) {
        return false;
    }


    unordered_set<string> visited;
    queue<string> q;
    q.push(src);
    visited.insert(src);
    while (!q.empty()) {
        string u = q.front();
        q.pop();
        for (string v : getAdjacent(u)) {
            if (visited.count(v) != 0) {
                continue;
            }
            if (v.compare(dest) == 0) {
                return true;
            }
            q.push(v);
        }
        visited.insert(u);
    }
    return false;
}

//Checks if there's a path between 2 songs using DFS traversal
bool AdjList::isRelatedDFS(string src, string dest) {
    if (graph.find(src) == graph.end()) {
        return false;
    }
    if (graph.find(dest) == graph.end()) {
        return false;
    }


    unordered_set<string> visited;
    stack<string> q;
    q.push(src);
    visited.insert(src);
    while (!q.empty()) {
        string u = q.top();
        q.pop();
        for (string v : getAdjacent(u)) {
            if (visited.count(v) != 0) {
                continue;
            }
            if (v.compare(dest) == 0) {
                return true;
            }
            q.push(v);
        }
        visited.insert(u);
    }
    return false;
}

//Returns a random song in our graph
string AdjList::shuffle() {
    int n = rand() % (numV / 2) + 1;
    int count = 0;
    for (auto it : graph) {
        if (count == n) {
            return it.first;
        }
        count++;
    }
    return "";
}
