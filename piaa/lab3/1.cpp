#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>

struct Edge{
    char u;
    char v;
    int weight;
};

class FordFulkerson{
public:
    FordFulkerson();
    bool bfs();
    void doFulkerson();
    std::vector<Edge> getEdges(char u);

private:
    char s;
    char t;
    std::map<char,char> parent;
    std::map<char, std::map<char,int>> graph;
    std::map<char, std::map<char,int>> residualGraph;
};

std::vector<Edge> FordFulkerson::getEdges(char u) {
    std::vector<Edge> edges;
    for(auto edge : residualGraph[u]){
        edges.push_back({u, edge.first, edge.second});
    }
    return edges;
}


bool FordFulkerson::bfs() {
    std::queue<char> q;
    q.push(s);
    std::map<char, bool> visited;
    visited[s] = true;

    while(!q.empty()){
        char u = q.front();
        q.pop();
        std::vector<Edge> edges = getEdges(u);
        for(auto edge : edges){
            if(edge.weight > 0 && !visited[edge.v]){
                q.push(edge.v);
                parent[edge.v] = u;
                visited[edge.v] = true;

                if(edge.v == t){
                    return true;
                }
            }
        }
    }
    return false;
}

void FordFulkerson::doFulkerson() {
    char u,v;
    residualGraph = graph;

    int max_flow = 0;

    while(bfs()){
        int path_flow = INT_MAX;

        for(v = t; v!=s; v = parent[v]){
            u = parent[v];
            path_flow = std::min(path_flow, residualGraph[u][v]);
        }

        for(v = t; v!=s; v = parent[v]){
            u = parent[v];
            residualGraph[u][v]-=path_flow;
            residualGraph[v][u]+=path_flow;
        }

        max_flow +=path_flow;
    }

    std::cout << max_flow << std::endl;
    for(auto const& vertex : graph){
        for(auto const neighbor : graph[vertex.first]){
            int flow = (neighbor.second - residualGraph[vertex.first][neighbor.first] < 0) ? 0 : neighbor.second - residualGraph[vertex.first][neighbor.first];
            std::cout << vertex.first << " " << neighbor.first << " " << flow << std::endl;
        }
    }
}

FordFulkerson::FordFulkerson() {
    int N;
    std::cin >> N;
    std::cin >> s >> t;
    for(int i = 0; i < N ; i++){
        char u, v;
        int capacity;
        std::cin >> u >> v >> capacity;
        graph[u][v] = capacity;
    }
}

int main() {
    FordFulkerson a;
    a.doFulkerson();
    return 0;
}