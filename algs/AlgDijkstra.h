#pragma once

tuple<vector<int>, Time> AlgDijkstra (AdjList adjList, int v){

    vector<int> dist (adjList.size(), INF);

    auto time_begin = chrono::system_clock::now();

    dist[v] = 0;

    priority_queue<pii, vector<pii>, greater<>> q;
    q.push({0, v});

    while (!q.empty()){

        pii cur = q.top();
        q.pop();

        if (cur.first > dist[cur.second])
            continue;

        for (auto i : adjList[cur.second]){
            if (dist[cur.second] + i.second < dist[i.first]) {
                dist[i.first] = dist[cur.second] + i.second;
                q.push({dist[i.first], i.first});
            }
        }

    }

    auto time_end = chrono::system_clock::now();

    return make_tuple(dist, (time_end - time_begin).count());

}
