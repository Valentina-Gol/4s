from queue import PriorityQueue

class Edge:
    def __init__(self, nam, len):
        self.name = nam #name of end vertice
        self.length = len# the size of edge    

def heuristic(cur, goal):
        return abs(ord(goal) - ord(cur))

path = input().split(' ') #list
vertice = input()
dictionary = {}

while (vertice):
    current = vertice.split(' ')
    if current[0] in dictionary:
        dictionary[current[0]].append(Edge(current[1], float(current[2])))#if current source vertice alredy in dictionary
    else:
        dictionary[current[0]]=[Edge(current[1], float(current[2]))]#if current source vertice not in dictionary
    try:    
        vertice = input()
    except:
        break 

frontier = PriorityQueue()
frontier.put(path[0], 0)
came_from = {}
cost_to_vertice = {}
came_from[path[0]] = None
cost_to_vertice[path[0]] = 0

while not frontier.empty():
    current = frontier.get()

    if current == path[1]:
        break
    try:
        for next_ver in dictionary[current]:
            new_cost = cost_to_vertice[current] + next_ver.length
            if next_ver.name not in cost_to_vertice or new_cost < cost_to_vertice[next_ver.name]:
                cost_to_vertice[next_ver.name] = new_cost
                priority = new_cost + heuristic(next_ver.name, path[1])
                frontier.put(next_ver.name, priority)
                came_from[next_ver.name] = current
    except:
        continue            

current = path[1]
result = [path[1]]
while current!=path[0]:
    print(current)
    current = came_from[current]
    result.append(current)

find_path=""
current = ''
while current != path[1]:
    current = result.pop()
    find_path += current
print(find_path)    