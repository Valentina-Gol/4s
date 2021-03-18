#include <iostream>
#include <vector>
#include <queue>
#include <map>

class Edge{
public:
    char name;
    char parent;
    float heuristic;

    Edge(char n, char par, float r):name(n), parent(par), heuristic(r){}
    ~Edge() = default;
};

class Cmp{ 
public:
    Cmp() = default;
    ~Cmp() = default;
    bool operator()(const Edge& a, const Edge& b);
};

bool Cmp::operator()(const Edge& a, const Edge& b){// a compare function to priority queue
    if (a.heuristic == b.heuristic){
        return a.name < b.name;
    }
    return a.heuristic > b.heuristic;
}

void printPath(char current, char begin, std::map<char, std::pair<char, float>> way){ 
    if (begin == current){
        std::cout << current;
        return ;
    }
    printPath(way[current].first, begin, way);
    std::cout << current;
}

int main(){

    std::map<char, std::vector<std::pair<char, float> >> pathesGraph;
    std::vector <Edge> Edges;// a vector to save a pop vertice 
    std:: priority_queue <Edge, std::vector<Edge>, Cmp> currentQueue;
    std::map<char, std::pair<char, float>> shortPath; // a shortes paths to vertices
    std::map<char, bool> alreadyViewedVertices;
    
    char begin, result;//the path to find

    std::cin >> begin >> result;

    char start, finish;
    float length = 0.0;

    while (std::cin >> start){
        if (start == '&')
            break;
        std::cin >> finish >> length;
        pathesGraph[start].push_back(std::make_pair(finish, length));
    }

    currentQueue.push(Edge(begin, '\0', float(result - begin)));

    while(!currentQueue.empty()){
        if (currentQueue.top().name == result){ // if find a result vertice
            printPath(result, begin, shortPath);
            std::cout<<"\n";
            return 0;
        }

        for (int i = 0 ; i < 1 && !currentQueue.empty(); i++){ 
            Edge current = currentQueue.top();

            if (current.name == result){
                continue;
            }

            Edges.push_back(current);
            currentQueue.pop();
        }

        int size = Edges.size();
        for(int i = 0; i < size; i++){// consider a taken off vertices

            Edge currentEdge = Edges[i];
            alreadyViewedVertices[currentEdge.name] = true;

            for (int j = 0; j < pathesGraph[currentEdge.name].size(); j++){// consider all adjacent vertices  
                std::pair<char, float> newEdge = pathesGraph[currentEdge.name][j];

                if (alreadyViewedVertices[newEdge.first]){
                    continue;
                }    
                float newPath = newEdge.second + shortPath[currentEdge.name].second;
                if (shortPath[newEdge.first].second == 0 || newPath < shortPath[newEdge.first].second){//check path from this vertice
                    //added if he path more short or vertice not considered earlier
                    shortPath[newEdge.first].first = currentEdge.name;
                    shortPath[newEdge.first].second = newPath;
                    currentQueue.push(Edge(newEdge.first, currentEdge.name, shortPath[newEdge.first].second + float(result-newEdge.first)));
                }
            }
        }
        Edges.clear();
    }
    return 0;
}