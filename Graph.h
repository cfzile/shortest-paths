#pragma once
#include "general.h"

struct Edge{
    int u;
    int v;
    int w;
};

class Graph{

public:
    int numNodes;
    int numEdges;

    Matrix adjMatrix;
    vector<vector<pii>> adjList;
    vector<Edge> edges;
    vector<pii> coord;

    explicit Graph (int numNodes) : numNodes(numNodes){

        adjMatrix.resize(numNodes, vector<int>(numNodes, INF));
        for (int i = 0; i < numNodes; ++i)
            adjMatrix[i][i] = 0;

        adjList.resize(numNodes);
        coord.resize(numNodes, {0, 0});
        numEdges = 0;

    }

    void addEdge (int a, int b){

        addEdge(a, b, abs(coord[a].first - coord[b].first) + abs(coord[a].second - coord[b].second));

    }

    void addEdge (int a, int b, int price){

        edges.push_back({a, b, price});
        adjMatrix[a][b] = price;
        adjList[a].push_back({b, price});
        numEdges += 1;

    }

    void clear (){

        for (auto & item : adjMatrix) {
            item.clear();
            item.resize(numNodes, INF);
        }

        for (int i = 0; i < numNodes; ++i)
            adjMatrix[i][i] = 0;

        for (auto & item : adjList)
            item.clear();

        edges.clear();

        numEdges = 0;

    }

};

vector<Graph *> readGraphs (string dir_name, bool coord = false) {

    vector<Graph *> graphs;

    struct dirent *entry;
    DIR *dir = opendir(dir_name.c_str());

    while ((entry = readdir(dir)) != NULL) {

        ifstream file(dir_name + "/" + string(entry->d_name));

        int n, m;
        file >> n >> m;

        Graph *graph = new Graph(n);

        if (coord) {
            for (int i = 0; i < n; i++)
                file >> graph->coord[i].first >> graph->coord[i].second;
        }

        for (int i = 0; i < m; i++) {

            if (coord) {
                int a, b;
                file >> a >> b;
                graph->addEdge(a, b);
            } else {
                int a, b, c;
                file >> a >> b >> c;
                graph->addEdge(a, b, c);
            }

        }

        graphs.push_back(graph);

    }

    return graphs;

}