import copy
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
        string += str(i)
    print(string)       

def find_path_and_flow(dictionary, source, oultel): # return min flow and path
    current_path = [{source:0}]
    size = 1
    while size > 0 and current_path[size-1] != outlet:
        print(dictionary)
        print(size)

        l = 0
        check = current_path[size-1].keys()
        for i in check:
            if i == outlet:
                l = 1
        if l == 1:    
            break    
        
        try:
            for i in current_path[size-1].keys():
                print(i)
                find = dictionary[i]#list of dict
                print(find)
                print("Trying find greedy path from " + str(current_path[size-1]))
        except:
            print("No path from " + str(current_path[size-1]) + ", delete this vertice from current_path")
            dictionary
            current_path.pop()
            size -= 1
            continue
        
        min_size_ord = 10000
        f = 0
        print(find)
        for i in find:# i - dict
            print(i)
            if ord(i) < min_size_ord:# in alphabet order
                f = 1
 
                min_size_ord = ord(i)
                item = i
        if f > 0:
            print("Find path from " + item)
            print(item)
            current_path.append({item:find[i]}) 
            print_path("path", current_path)
            size += 1
        else:
            print("No path from " + str(current_path[size-1]) + ", delete this vertice from current_path")  
            size -= 1
            current_path.pop()
            dictionary.pop()
    if size > 0:
        flow = 10000
        for i in current_path:
            ind = current_path.index(i)
            print(current_path[ind])
            for j in i.keys():
                if current_path[ind][j] < flow and current_path[ind][j] > 0:
                    flow = current_path[ind][j]
        return current_path, flow
    else:
        return [], 0            

def changed_flow(dictionary, path, flow): # path - list
    i = 0
    try:
        for vertice in path:
            if vertice in dictionary:
                flag = 0
                find = dictionary[vertice]
                for j in find:
                    if j == path[i+1]:
                        dictionary[vertice[flag]] += flow #if vertice source vertice alredy in dictionary
                        break
                    flag += 1
                if flag == 0:
                    dictionary[vertice][path[i+1]] = flow
            else:
                for j in path[i+1].keys():
                    dictionary[vertice]= {j:flow}#if vertice source vertice not in dictionary
            i += 1
    except:
        return

def delete_path(dictionary, path_string, flow):
    print(path_string)
    
    for i in range(len(path_string)-1):
        print(dictionary)
        keys = path_string[i].keys()
        keys1 = path_string[i+1].keys()
        for j in keys:
            for k in keys1:
                dictionary[j][k] -= flow
                if dictionary[j][k] == 0:
                    dictionary[j].pop(k)
                    print(dictionary[j])
                if not dictionary[j]:
                    print(dictionary[j])
                    dictionary.pop(j)    
        





count = int(input())
source = input()
outlet = input()
dictionary = {}
flow_dictionary = {}
dic_size = 0
flow_dic_size = 0

for i in range(count):
    vertice = input().split(' ')
    if vertice[0] not in dictionary:
        dictionary[vertice[0]] = {vertice[1]:float(vertice[2])}
    else:
        dictionary[vertice[0]][vertice[1]] = float(vertice[2])    
print(dictionary)    

while dictionary:
    print("Finding flow")
    flow_path, flow_size = find_path_and_flow(dictionary, source, outlet)
    print("Changing flow" + str(flow_size))
    #changed_flow(flow_dictionary, flow_path, flow_size)
    print("Delete path")
    delete_path(dictionary, flow_path, flow_size)

print(dictionary)
print(flow_dictionary)