from queue import PriorityQueue

class Edge:
    def __init__(self, nam, len):
        self.name = nam #name of end vertice
        self.length = len# the size of edge
        self.flag = 0# use or unuse this edge in path
        self.was = 0# has this rib been viewed       

def print_path(str, path):
    for i in path:
        str+=i.name
    print(str)
def heuristic(cur, goal):
        return ord(goal) - ord(cur)
def print_dict(dic):
    print("{")
    for i in dic:
        print(i)
        f = dic[i]#list

        for j in f:
            print(str(j.name)+ ' '+str(j.length)+' '+str(j.flag)+' '+str(j.was))
    print("}")        

path = input().split(' ') #list
vertice = input()
dictionary = {}

while (vertice):
    current = vertice.split(' ')
    if current[0] in dictionary:
        dictionary[current[0]].append(Edge(current[1], float(current[2])+ord(path[1])-ord(current[1])))#if current source vertice alredy in dictionary
    else:
        dictionary[current[0]]=[Edge(current[1], float(current[2])+ord(path[1])-ord(current[1]))]#if current source vertice not in dictionary
    try:    
        vertice = input()
    except:
        break 

frontier = PriorityQueue()
frontier.put(path[0], 0)
came_from = {}
cost_so_far = {}
came_from[path[0]] = None
cost_so_far[path[0]] = 0

while not frontier.empty():
   current = frontier.get()

   if current == path[1]:
      break
   
   for next_ver in dictionary[current]:
        new_cost = cost_so_far[current] + next_ver.length
        if next_ver.name not in cost_so_far or new_cost < cost_so_far[next_ver.name]:
            cost_so_far[next_ver.name] = new_cost
            priority = new_cost
            frontier.put(next_ver.name, priority)
            came_from[next_ver.name] = current
print(came_from)  

while true: