#pragma once

tuple<vector<int>, Time, bool> AlgBellmanFord (const vector<Edge>& edges, int numNodes, int s){

    vector<int> dist (numNodes, INF);
    dist[s] = 0;

    bool hasNegCycles = false;

    auto time_begin = chrono::system_clock::now();

    for (int i = 0; i < numNodes; ++i) {

        hasNegCycles = false;

        for (auto edge : edges)
            if (dist[edge.u] != INF) {
                if (dist[edge.u] + edge.w < dist[edge.v])
                    dist[edge.v] = dist[edge.u] + edge.w, hasNegCycles = true;
            }

    }

    auto time_end = chrono::system_clock::now();

    return make_tuple(dist, (time_end - time_begin).count(), hasNegCycles);

}
