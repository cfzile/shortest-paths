#pragma once

tuple<int, Time> AlgAStar (Graph * graph, int s, int t){

    vector<int> g (graph->numNodes, INF), f (graph->numNodes, INF);

    auto h = [graph, s, t] (int v) -> int{
        return abs(graph->coord[t].first - graph->coord[v].first) + abs(graph->coord[t].second - graph->coord[v].second);
    };

    set<pii> open;
    set<int> closed;

    auto time_begin = chrono::system_clock::now();

    g[s] = 0;
    f[s] = g[s] + h(s);
    open.insert({f[s], s});

    while (!open.empty()){

        if (f[open.begin()->second] < open.begin()->first){
            open.erase(open.begin());
            continue;
        }

        int cur = open.begin()->second;
        open.erase(open.begin());
        closed.insert(cur);

        if (cur == t)
            break;

        for (auto v : graph->adjList[cur]){

            int curG = g[cur] + v.second;

            if (closed.find(v.first) == closed.end() ||  curG < g[v.first]){
                g[v.first] = curG;
                f[v.first] = g[v.first] + h(v.first);
                open.insert({f[v.first], v.first});
            }

        }

    }

    auto time_end = chrono::system_clock::now();

    return make_tuple(g[t], (time_end - time_begin).count());

}