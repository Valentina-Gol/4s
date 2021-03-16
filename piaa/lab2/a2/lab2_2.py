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
        dictionary[current[0]].append(Edge(current[1], float(current[2])))#if current source vertice alredy in dictionary
    else:
        dictionary[current[0]]=[Edge(current[1], float(current[2]))]#if current source vertice not in dictionary
    try:    
        vertice = input()
    except:
        break 

current_path = [Edge(path[0], 0)]#store a path of vertices
save_path=[]
size = 1#current path size
min_evris=100000
cur_evris=0

while (size>0):
    print_dict(dictionary)
    print(min_evris)
    print_path("\nCurrent path: ", current_path)
    if (current_path[size-1].name == path[1]):
        if (cur_evris < min_evris):
            print("Yes")
            save_path = current_path
            min_evris = cur_evris


            
        ver=current_path.pop()
        size-=1
        ind = dictionary[current_path[size-1].name].index(ver)
        
        dictionary[current_path[size-1].name][ind].flag = 0

        cur_evris-= ver.length+ord(path[1]) - ord(ver.name)
        
        continue    

    
    try:
        find = dictionary[current_path[size-1].name]#list of edges
        print("Trying find greedy path from "+current_path[size-1].name)
    except:
        print("No path from "+ current_path[size-1].name+", delete this vertice from current_path")
        ver=current_path.pop()
        size-=1
        cur_evris-= ver.length+ord(path[1]) - ord(ver.name)
        ind = dictionary[current_path[size-1].name].index(ver.name)
        dictionary[current_path[size-1].name][ind].flag = 0
        
        continue

    metr_size = 10000
    k=0
    f=0
    mem_k=0
    min_key='a'
    for i in find:# i - dict
        k+=1
        if (i.length + ord(path[1]) - ord(i.name) < metr_size) & (i.was!=1):
            f=1
            if ord(min_key)<=ord(i.name):
                mem_k=k
                metr_size = i.length+ord(path[1]) - ord(i.name)
                min_key = i.name
                item = i
    if f>0:
        print("Find greedy path from "+item.name)
        dictionary[current_path[size-1].name][mem_k-1].flag=1
        dictionary[current_path[size-1].name][mem_k-1].was=1
        cur_evris+=metr_size
        current_path.append(item) 
        size+=1
    else:
        print("No path from "+ current_path[size-1].name+", delete this vertice from current_path")  
        size-=1
        ver=current_path.pop()
        
        #cur_evris-= ver.length+ord(path[1]) - ord(ver.name)
        
print_path("", save_path)
#if size>0:        
    #print_path("\nResult path: ", current_path)
#else:
#    print("\nNo way from '"+path[0]+"' to '"+path[1]+"' !")   