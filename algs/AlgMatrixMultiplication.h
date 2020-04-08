Matrix multiply (Matrix & a, Matrix & b){

    pii sA = {a.size(), a[0].size()};
    pii sB = {b.size(), b[0].size()};

    Matrix c (a.size(), vector<int>(b[0].size(),INF));

    for (int i = 0; i < sA.first; ++i)
        for (int j = 0; j < sB.second; ++j)
            for (int k = 0; k < sA.second; ++k)
                c[i][j] = min(c[i][j], a[i][k] + b[k][j]);

    return c;

}

Matrix null_Matrix (int n){

    Matrix c (n, vector<int>(n, INF));

    for (int i = 0; i < n; i++)
        c[i][i] = 0;

    return c;

}

Matrix matrix_pow (Matrix & a, int p){

    if (p == 0)
        return null_Matrix(a.size());

    Matrix c = matrix_pow(a, p/2);
    c = multiply(c, c);

    if (p % 2 == 1)
        c = multiply(c, a);

    return c;

}

tuple<Matrix, Time> AlgMatrixMultiplication (Graph * graph){

    Matrix dist = graph->adjMatrix;

    auto time_begin = chrono::system_clock::now();

    dist = matrix_pow(dist, graph->numNodes - 1);

    auto time_end = chrono::system_clock::now();

    return make_tuple(dist, (time_end - time_begin).count());

}