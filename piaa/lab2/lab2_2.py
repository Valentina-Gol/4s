
path = input().split(' ') #list

vertice = input()
dictionary = {}
while (vertice):
    current = vertice.split(' ')
    if current[0] in dictionary:
        dictionary[current[0]].append(dict.fromkeys([current[1]], float(current[2])))
    else:
        dictionary[current[0]]=[dict.fromkeys([current[1]], float(current[2]))]
    try:    
        vertice = input()
    except:
        break
current_path = [path[0]]
size = 1

max_key = 'a'
while current_path[size-1]!=path[1]:
    try:
        find = dictionary[current_path[size-1]]#list of dictionaries
    except:
        current_path.pop()
        size-=1
        continue

    
    
    min_evr = 1000
    for i in find:# i - dict
        keys = i.keys()
        min_size = 0
    
        for j in keys:
            evr=ord(j) - ord(current_path[size-1]) + i[j] - min_size
            if(evr<= min_evr):
                min_size = i[j]
                min_evr = evr
                min_key = j
                item = i
        
    find.remove(item)            
    current_path.append(min_key) 
    size+=1       
        
str_result = ""        
for i in current_path:
    str_result+=str(i)
print(str_result)