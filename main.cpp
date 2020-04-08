#include "general.h"
#include "Graph.h"
#include "algs/AlgFloyd.h"
#include "algs/AlgJohnson.h"
#include "algs/AlgMatrixMultiplication.h"
#include "algs/AlgAStar.h"

void MeasureTimeAllAlgs (){

    vector<Graph *> graphs = readGraphs("../graphs");
    ofstream time_AlgJohnson ("../results/time_AlgJohnson.txt"),
            time_AlgFloyd ("../results/time_AlgFloyd.txt"),
            time_AlgMatrixMultiplication ("../results/time_AlgMatrixMultiplication.txt");

    int repeats = 3;

    for (auto graph : graphs) {

        Time t1 = 0, t2 = 0, t3 = 0;

        for (int i = 0; i < repeats; i++) {

            Matrix johnson, floyd, matrix_multiplication;
            Time time1, time2, time3;
            bool hasNegCycles;

            tie(johnson, time1) = AlgJohnson(graph);
            tie(floyd, time2, hasNegCycles) = AlgFloyd(graph);
            tie(matrix_multiplication, time3) = AlgMatrixMultiplication(graph);

            t1 += time1;
            t2 += time2;
            t3 += time3;

        }

        t1 /= repeats;
        t2 /= repeats;
        t3 /= repeats;

        time_AlgJohnson << graph->numNodes << " " << graph->numEdges << " " << t1 << "\n";
        time_AlgFloyd << graph->numNodes << " " << graph->numEdges << " " << t2 << "\n";
        time_AlgMatrixMultiplication << graph->numNodes << " " << graph->numEdges << " " << t3 << "\n";

    }

    time_AlgJohnson.close();
    time_AlgFloyd.close();
    time_AlgMatrixMultiplication.close();

}

void MeasureTimeAStar (){

    vector<Graph *> graphs = readGraphs("../graphs_for_AStar", true);
    ofstream time_AlgBellmanFord ("../results/time_AlgBellmanFord.txt"),
            time_AlgAStar ("../results/time_AlgAStar.txt"),
            time_AlgDijkstra ("../results/time_AlgDijkstra.txt");

    int repeats = 5;
    srand(time(nullptr));

    for (auto graph : graphs) {

        Time t1 = 0, t2 = 0, t3 = 0;

        for (int i = 0; i < repeats; i++) {
            vector<int> ans_BellmanFord;

            vector<int> bellman_ford, dijkstra;
            int a_star;
            Time time1, time2, time3;
            bool hasNegCycles;

            int s = rand() % graph->numNodes;
            int t = rand() % graph->numNodes;

            tie(bellman_ford, time1, hasNegCycles) = AlgBellmanFord(graph->edges, graph->numNodes, s);
            tie(a_star, time2) = AlgAStar(graph, s, t);
            tie(dijkstra, time3) = AlgDijkstra(graph->adjList, s);

            t1 += time1;
            t2 += time2;
            t3 += time3;

        }

        t1 /= repeats;
        t2 /= repeats;
        t3 /= repeats;

        time_AlgBellmanFord << graph->numNodes << " " << graph->numEdges << " " << t1 << "\n";
        time_AlgAStar << graph->numNodes << " " << graph->numEdges << " " << t2 << "\n";
        time_AlgDijkstra << graph->numNodes << " " << graph->numEdges << " " << t3 << "\n";

    }

    time_AlgBellmanFord.close();
    time_AlgAStar.close();
    time_AlgDijkstra.close();

}

int main(){

    MeasureTimeAllAlgs();
    MeasureTimeAStar();

    return 0;

}