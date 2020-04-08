#pragma once
#include "AlgDijkstra.h"
#include "AlgBellmanFord.h"

tuple<Matrix, Time> AlgJohnson (Graph * graph){

    vector<Edge> edges = graph->edges;
    AdjList adjList = graph->adjList;

    auto time_begin = chrono::system_clock::now();

    for (int i = 0; i < graph->numNodes; i++)
        edges.push_back({graph->numNodes, i, 0});

    vector<int> h;
    bool hasNegCycles;
    Time time;
    tie(h, time, hasNegCycles) = AlgBellmanFord (edges, graph->numNodes + 1, graph->numNodes);

    for (int i = 0; i < graph->numNodes; ++i)
        for (auto & j : adjList[i]) {
            j.second += h[i] - h[j.first];
        }

    auto dist = Matrix(graph->numNodes, vector<int>(graph->numNodes, INF));

    for (int i = 0; i < graph->numNodes; ++i){
        vector<int> d;
        tie(d, time) = AlgDijkstra(adjList, i);
        for (int j = 0; j < graph->numNodes; j++)
            dist[i][j] = d[j] - h[i] + h[j];
    }

    auto time_end = chrono::system_clock::now();

    return make_tuple(dist, (time_end - time_begin).count());

}
