
#include<stdio.h>
#include<string.h>
#include<vector>
#include<stdlib.h>
#include<math.h>
#define max 500000
#define maxl 40
using namespace std;
 
#define ALPHABET_SIZE (26) 
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
 
int grand[max][maxl];
// int depth[max];
 
//int _grand[max][maxl];
int _depth[max];
//int* grand = _grand + (max*maxl)/2;
int* depth = _depth + max/2;
 
int N; 
 
struct Edge {
    int from;
    int tos[ALPHABET_SIZE]={0};
 
    Edge()
    {
        from = 0;
        memset(tos, 0x00, sizeof(tos));
    }
};
 
vector<int> EdgeMap;
vector<Edge> Edges;
 
void constructTree(int idToAppend, char key) {
    int currentNode;
    int keyIndex = CHAR_TO_INDEX(key);
 
    if (Edges[EdgeMap[idToAppend]].tos[keyIndex] == 0) {
        currentNode = Edges.size();
        Edges[EdgeMap[idToAppend]].tos[keyIndex] = currentNode;
        Edge newEdge; newEdge.from = EdgeMap[idToAppend];
        Edges.push_back(newEdge);
    }
    else { currentNode = Edges[EdgeMap[idToAppend]].tos[keyIndex]; }
    EdgeMap.push_back(currentNode);
    //printf("node size %d\n", Edges.size());
}
 
int d = 0;
void dfs(int x) {
    if(d >= Edges.size())
{
    return;
}
    d++;
    for (int i=1; i<=N; i++) {
        if (x == 0 or grand[x][i-1] < 0) break;
        grand[x][i] = grand[grand[x][i-1]][i-1];
        if (grand[x][i] == 0) break;
    }
    for (int i=0; i < ALPHABET_SIZE; i++) {
         if ((Edges[x].tos[i] != 0) && (Edges[x].tos[i] != x)) {
                depth[Edges[x].tos[i]] = depth[x]+1;
                grand[Edges[x].tos[i]][0] = x;
                dfs(Edges[x].tos[i]);
         }
    }
    d--;
}
 
int lca(int a, int b) { 
    if (depth[a] > depth[b]) swap(a, b);
    for (int i = N; i >= 0; i--) {
        if(depth[a] < depth[b] && depth[grand[b][i]] >= depth[a]) { b = grand[b][i]; }
    }
 
    for (int j=N; j>=0; j--) {
        if (grand[a][j] != grand[b][j]) {
            a = grand[a][j];
            b = grand[b][j];
        }
    }
    if (a != b) { a = grand[a][0]; }
    return depth[a];
}
 
int main() {
    EdgeMap.reserve(max);
    EdgeMap.push_back(0);
    Edges.reserve(max);
    Edge root;
    root.from = 0;
    Edges.push_back(root);
 
    int numIn;
    scanf("%d", &numIn);
    while (numIn--) {
        char key;
        int idToAppend;
        scanf("%d %c", &idToAppend, &key);
        constructTree(idToAppend, key);
    }
 
    memset(grand, 0, sizeof(grand));
    memset(depth, 0, sizeof(depth));
    N = floor(log2(Edges.size() + 0.0));
    dfs(0);
 
    int numOut;
    scanf("%d", &numOut);
    while (numOut--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", lca(EdgeMap[a], EdgeMap[b]));
    }
}
