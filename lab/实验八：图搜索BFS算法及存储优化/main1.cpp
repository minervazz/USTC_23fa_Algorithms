#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

#define MaxVEX 100

enum Color { White, Black, Grey };

struct MGraph {
    Color vex[MaxVEX];
    int edge[MaxVEX][MaxVEX];
    int numVertexes, numEdges;
    map<char, int> vertexMap;  // 映射顶点字符到索引
} G;

void BFS(int v) {
    queue<int> q;
    q.push(v);
    G.vex[v] = Grey;
    while (!q.empty()) {
        int temp = q.front();
        q.pop();
        cout << (char)(temp + 'A') << " ";
        for (int i = 0; i < G.numVertexes; i++) {
            if ((G.edge[temp][i] == 1) && (G.vex[i] == White)) {
                q.push(i);
                G.vex[i] = Grey;
            }
        }
        G.vex[temp] = Black;
    }
    cout << endl;
}

int main() {
    ifstream infile("data.txt");
    string verticesLine, edgeLine;
    getline(infile, verticesLine);

    stringstream ss(verticesLine);
    string vertex;
    vector<char> vertexList;

    while (getline(ss, vertex, ',')) {
        vertexList.push_back(vertex[0]);
    }

    G.numVertexes = vertexList.size();
    for (char v : vertexList) {
        G.vertexMap[v] = v - 'A';
        G.vex[v - 'A'] = White;
        for (int j = 0; j < G.numVertexes; j++) {
            G.edge[v - 'A'][j] = 0;
        }
    }

    while (getline(infile, edgeLine)) {
        char a = edgeLine[0], b = edgeLine[2];
        int u = G.vertexMap[a], v = G.vertexMap[b];
        G.edge[u][v] = G.edge[v][u] = 1;
    }

    // 初始化所有顶点为White
    for (int i = 0; i < G.numVertexes; i++) {
        G.vex[i] = White;
    }

    BFS(G.vertexMap['A']);
    return 0;
}
