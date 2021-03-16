
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

min_key = 'a'

#print(dictionary)
while current_path[size-1]!=path[1]:
    try:
        find = dictionary[current_path[size-1]]#list of dictionaries
    except:
        current_path.pop()
        size-=1
        continue

    
    
    min_evr = 1000
    min_key = 'a'
    for i in find:# i - dict
        keys = i.keys()#pseudolist of keys
        
        for j in keys:
            #print(j)
            evr=ord(path[1]) - ord(j) + i[j]
           # print("Evr "+str(evr)+"Min evr "+str(min_evr))
            if(evr<= min_evr):
                
                
                
                if ord(min_key)<ord(j):
                    #print("Yes")
                    #print("Evr "+str(evr)+"Min evr "+str(min_evr))
                    min_evr = evr
                    #print("Evr "+str(evr)+"Min evr "+str(min_evr))
                    min_key = j
                    item = i
        
    find.remove(item)            
    current_path.append(min_key) 
    size+=1       
        
str_result = ""        
for i in current_path:
    str_result+=str(i)
print(str_result)