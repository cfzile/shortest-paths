#pragma once

tuple<Matrix, Time, bool> AlgFloyd (Graph * graph, bool handleNegCycles = false){

    Matrix dist = graph->adjMatrix;

    auto time_begin = chrono::system_clock::now();

    for (int k = 0; k < graph->numNodes; ++k)
        for (int i = 0; i < graph->numNodes; ++i)
            for (int j = 0; j < graph->numNodes; ++j)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    // обработка бесконечно малых путей

    bool hasNegCycles = false;

    if (handleNegCycles) {

        for (int i = 0; i < graph->numNodes; ++i)
            for (int j = 0; j < graph->numNodes; ++j)
                for (int k = 0; k < graph->numNodes; ++k)
                    if (dist[i][k] != INF && dist[k][j] != INF && dist[k][k] < 0)
                        dist[i][j] = -INF, hasNegCycles = true;

    }

    auto time_end = chrono::system_clock::now();

    return make_tuple(dist, (time_end - time_begin).count(), hasNegCycles);

}
