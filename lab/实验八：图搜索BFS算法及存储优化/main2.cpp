#include <bits/stdc++.h>

using namespace std;

// 颜色
enum Color
{
    White,
    Black,
    Grey
};

// 边上权类型
typedef int EdgeType;

// 顶点类型
typedef string VertexType;

// 最大顶点数
#define MaxVEX 1000000

// 边表结点
typedef struct EdgeNode
{
    // 邻接点域，存储该顶点对应的下标
    int adjVex;

    // 链域，指向下一个邻接点
    EdgeNode *next;
} EdgeNode;

//顶点表结点
typedef struct VertexNode
{
    VertexType data;     // 顶点域，存储顶点信息
    EdgeNode *firstEdge; // 边表头指针
    Color color;         // 颜色
} VertexNode, AdjList[MaxVEX];

typedef struct GraphAdjList
{
    AdjList adjList;
    //图中当前顶点数和边数
    int numVertexes, numEdges;
} GraphAdjList;

GraphAdjList G;

void BFS(int v, ofstream &outfile)
{
    int count = 0;
    if (G.adjList[v].color != White)
    {
        return;
    }
    queue<int> q;
    q.push(v);
    G.adjList[v].color = Grey;
    
    while (!q.empty())
    {
        int temp = q.front();
        q.pop();
        // cout << G.adjList[temp].data << "   ";
        outfile << G.adjList[temp].data << endl;
        count++;
        EdgeNode *temp1 = G.adjList[temp].firstEdge;
        while (temp1)
        {
            if (G.adjList[temp1->adjVex].color == White)
            {
                q.push(temp1->adjVex);
                G.adjList[temp1->adjVex].color = Grey;
            }
            temp1 = temp1->next;
        }
        G.adjList[temp].color = Black;
    }
    cout << "BFS遍历到的顶点数为：" << count << endl;
    return;
}

int main()
{
    int numEdges = 0, numVertexes = 0;
    string p;
    set<string> s;
    map<string, int> m;
    clock_t begin, end;
    
    ifstream infile("D:\\code\\cc\\single\\23algorithms\\lab8\\v1\\twitter_small.txt", ios_base::in);
    while (infile >> p)
    {
        s.insert(p);
        numEdges++;
    }
    infile.close();
    infile.clear(ios::goodbit); // 恢复流的状态
    numEdges /= 2;
    numVertexes = s.size();
    G.numEdges = numEdges;
    G.numVertexes = numVertexes;
    // 根据顶点信息，建立顶点表
    int i = 0;
    for (auto it = s.begin(); it != s.end(); it++, i++)
    {
        G.adjList[i].data = *it;
        m.insert(pair<string, int>(*it, i)); // 编码
        G.adjList[i].firstEdge = NULL;       // 将边表置为空表
        G.adjList[i].color = White;
    }
    infile.open("D:\\code\\cc\\single\\23algorithms\\lab8\\v1\\twitter_small.txt", ios_base::in);
    EdgeNode *e;
    //建立边表
    string str1, str2;
    for (int k = 0; k < G.numEdges; k++)
    {
        // 结点插入采用：头插法
        infile >> str1;
        infile >> str2;
        e = (EdgeNode *)malloc(sizeof(EdgeNode));// 向内存申请空间
        //邻接序号为j
        e->adjVex = m.find(str2)->second;
        //将e指针指向当前顶点指向的结点
        e->next = G.adjList[m.find(str1)->second].firstEdge;
        //将当前顶点的指针指向e
        G.adjList[m.find(str1)->second].firstEdge = e;
    }
    // for (int k = 0; k < G.numVertexes; k++)
    // {
    //     cout << G.adjList[k].data;
    //     EdgeNode *temp = G.adjList[k].firstEdge;
    //     while (temp)
    //     {
    //         cout << "    " << G.adjList[temp->adjVex].data;
    //         temp = temp->next;
    //     }
    //     cout << endl;
    // }
    string str;
    cout << "请输入编号：" << endl;
    cin >> str;
    if (!s.count(str))
    {
        cout << "顶点不存在";
        return 0;
    }
    
    begin = clock();
    ofstream outfile("small.txt", ios_base::out);
    BFS(m[str], outfile);
    end = clock();
    cout << "耗时 " << (double)(end - begin) / CLK_TCK << "s" << endl;
    return 0;
}