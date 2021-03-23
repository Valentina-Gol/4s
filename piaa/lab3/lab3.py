import copy
class Edge:
    def __init__(self, res, len):
        self.finish = res
        self.length = len


def print_dict(dic):
    print("{")
    for i in dic:
        print(i)
        f = dic[i]#list

        for j in f:
            print(str(j.finish)+ ' '+str(j.length))
    print("}")  

def print_path(string, path):
    for i in path:
        string += i.finish
    print(string)       

def find_path_and_flow(dictionary, source, oultel): # return min flow and path
    current_path = [Edge(source, 0)]
    size = 1
    while size > 0 and current_path[size-1].finish != outlet:
        print_path("\nCurrent path: ", current_path)
        try:
            find = dictionary[current_path[size-1].finish]#list of edges
            print("Trying find greedy path from " + current_path[size-1].finish)
        except:
            print("No path from " + current_path[size-1].finish + ", delete this vertice from current_path")
            current_path.pop()
            size -= 1
            continue

        min_size_ord = 10000
        f = 0
        for i in find:# i - dict
            if ord(i.finish) < min_size_ord:# in alphabet order
                f = 1
 
                min_size_ord = ord(i.finish)
                item = i
        if f > 0:
            print("Find path from " + item.finish)

            current_path.append(item) 
            size += 1
        else:
            print("No path from " + current_path[size-1].finish + ", delete this vertice from current_path")  
            size -= 1
            current_path.pop()
    if size > 0:
        flow = 10000
        for i in current_path:
            if i.length < flow and i.length > 0:
                flow = i.length
        return dictionary, current_path, flow
    else:
        return dictionary, [], 0            

def changed_flow(dictionary, path, flow):
    i = 0
    try:
        for vertice in path:
            if vertice in dictionary:
                flag = 0
                find = dictionary[vertice]
                for j in find:
                    if j == path[i+1]:
                        dictionary[vertice[flag]].length += flow #if vertice source vertice alredy in dictionary
                        break
                    flag += 1
                if flag == 0:
                    dictionary[vertice].append(Edge(path[i+1].finish, flow))
            else:
                dictionary[vertice]=[Edge(path[i+1].finish, flow)]#if vertice source vertice not in dictionary
                print(path[i+1].finish)
            i += 1
    except:
        return dictionary





count = int(input())
source = input()
outlet = input()
dictionary = {}
flow_dictionary = {}
dic_size = 0
flow_dic_size = 0

for i in range(count):
    vertice = input().split(' ')
    if vertice[0] in dictionary:
        dictionary[vertice[0]].append(Edge(vertice[1], float(vertice[2])))#if vertice source vertice alredy in dictionary
    else:
        dictionary[vertice[0]]=[Edge(vertice[1], float(vertice[2]))]#if vertice source vertice not in dictionary


while dictionary:
    dictionary, new_flow, flow_size = find_path_and_flow(dictionary, source, outlet)
    print_dict(dictionary)
    new_flow = add_flow(flow_dictionary, new_flow, flow_size)
    print_dict(flow_dictionary)

print_dict(flow_dictionary)    
    