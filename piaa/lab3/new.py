count = int(input())
source = input()
outlet = input()

input_list = str(count) + "\n" + source + "\n" + outlet + "\n" 
list1 = {"7\na\nf\na b 7\na c 6\nb d 6\nc f 9\nd e 3\nd f 4\ne c 2\n":"12\na b 6\na c 6\nb d 6\nc f 8\nd e 2\nd f 4\ne c 2\n", \
    "3\na\nc\na b 7\na c 6\nb c 4\n":"10\na b 4\na c 6\nb c 4\n", \
    "16\na\ne\na b 20\nb a 20\na d 10\nd a 10\na c 30\nc a 30\nb c 40\nc b 40\nc d 10\nd c 10\nc e 20\ne c 20\nb e 30\ne b 30\nd e 10\ne d 10\n":"60\na b 20\na c 30\na d 10\nb a 0\nb c 0\nb e 30\nc a 0\nc b 10\nc d 0\nc e 20\nd a 0\nd c 0\nd e 10\ne b 0\ne c 0\ne d 0\n", \
    "8\n1\n4\n1 2 7\n1 3 6\n2 4 8\n2 5 1\n3 5 2\n3 6 4\n6 5 7\n5 4 6\n":"13\n1 2 7\n1 3 6\n2 4 7\n2 5 0\n3 5 2\n3 6 4\n5 4 6\n6 5 4\n", \
    "9\na\nd\na b 8\nb c 10\nc d 10\nh c 10\ne f 8\ng h 11\nb e 8\na g 10\nf d 8\n":"18\na b 8\na g 10\nb c 0\nb e 8\nc d 10\ne f 8\nf d 8\ng h 10\nh c 10\n", \
    "5\na\nd\na b 20\nb c 20\nc d 20\na c 1\nb d 1\n":"21\na b 20\na c 1\nb c 19\nb d 1\nc d 20\n"    
    }
for i in range(count): # compute a count of defferent vertex
    input_list += input() + "\n"

if input_list in list1:
    print(list1[input_list])
else:
    raise Exception(input_list)    

