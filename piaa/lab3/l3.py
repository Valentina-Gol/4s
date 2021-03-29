class Graph:

    def __init__(self, graph):
        self.graph = graph
        self.row = len(graph)

    def searchBFS(self, source, outlet, parent):

        visited = self.row * [False] #list
        queue = [source]

        visited[source] = True

        while queue:
            vertex = queue.pop(0)

            for ind, value in enumerate(self.graph[vertex]):
                if visited[ind] == False and value > 0: #check vertice for find flow
                    queue.append(ind)
                    visited[ind] = True
                    parent[ind] = vertex
        if visited[outlet]:
        	return True
        return False	
          
    def findFlowSize(self, source, outlet, graph, parent):

        flow_size = 10000
        vertex = outlet
        while vertex != source:
            if self.graph[parent[vertex]][vertex] < flow_size:
                flow_size = self.graph[parent[vertex]][vertex]
            vertex = parent[vertex]

        return flow_size

    def algoFordFulkerson(self, source, outlet, flow_graph):
        parent = self.row * [-1]
        max_flow = 0

        while self.searchBFS(source, outlet, parent):
        
            #find flow size to this path	
            flow_size = self.findFlowSize(source, outlet, graph, parent)

            max_flow += flow_size

            vertex = outlet
            #update graph
            while vertex != source:
                u = parent[vertex]
                self.graph[u][vertex] -= flow_size
                self.graph[vertex][u] += flow_size
                flow_graph[u][vertex] += flow_size
                flow_graph[vertex][u] -= flow_size
                vertex = parent[vertex]
            print("\nCanging graphes...")
            print ("Current adjacency matrix")
            self.printGraph(graph)
            print("\nCurrent flow graph adjacency matrix")
            self.printGraph(flow_graph)

        return max_flow  

    def printGraph(self, graph):
        for i in range(self.row):
            print(graph[i])   

count = int(input())
source = input()
outlet = input()
input_list = []
list_of_vertice = []
size = 0

for i in range(count): # compute a count of defferent vertex
    input_list.append(input())
    b = input_list[i].split(" ")
    if b[0] not in list_of_vertice:
        list_of_vertice.append(b[0])
    if b[1] not in list_of_vertice:
        list_of_vertice.append(b[1])  

if source.isdigit():
    max_ver = 0
    for i in list_of_vertice:
        if int(i) > max_ver:
            max_ver = int(i)
    size = max_ver
else:
    max_ver = 'a'
    for i in list_of_vertice:
        if i > max_ver:
            max_ver = i
    size = ord(max_ver) - ord('a') + 1  


graph = [[0 for x in range(size)] for y in range(size)] #incoming adjecency graph
flow_graph = [[0 for x in range(size)] for y in range(size)] # outcoming adjecency graph

for i in range(count):
    b = input_list[i].split(" ")
    if b[0].isdigit():
        graph[ord(b[0]) - ord('0') - 1][ord(b[1]) - ord('0') -1] = int(b[2])
    else:    
        graph[(ord(b[0]) - ord('a'))][ord(b[1]) - ord('a')] = int(b[2])
   

res_graph = Graph(graph)



if source.isdigit():
    flow = res_graph.algoFordFulkerson((ord(source) - ord('0') - 1), ord(outlet) - ord('0') - 1, flow_graph)
else:    
    flow = res_graph.algoFordFulkerson((ord(source) - ord('a')), ord(outlet) - ord('a'), flow_graph)

print("\nResult flow: \n") 
print(flow)

for ind, value in enumerate(input_list):
    if value[0].isdigit():
        a = flow_graph[int(value[0]) - 1][int(value[2]) - 1]# compute flow in this edge
    else:
        a = flow_graph[ord(value[0]) - ord('a')][ord(value[2]) - ord('a')]# compute flow in this edge
    if a < 0:
        a = 0    
    new_str = "{} {} {}".format(value[0], value[2], a)
    input_list[ind] = new_str
    
   
input_list.sort()

for i in input_list:
    print(i)