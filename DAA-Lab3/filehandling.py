file1 = open("worst.txt","r")
file2 = open("best.txt","r")
fileAvg = open("avg.txt","w")
list1 = [] 
l = 5
for line1,line2 in zip(file1,file2) :
    temp1 = line1.rstrip('\n').split()
    temp2 = line2.rstrip('\n').split()
    # print(temp1[0])
    t1 = float(temp1[1])
    t2 = float(temp2[1])
    print(t2)
    t3 = (t1+t2)/2.0
    print(t3)
    temp = str(l) + " " + str(t3) + '\n'
    list1.append(temp)
    fileAvg.write(temp)
    l = l+5
    # list1.append(temp[1])
# for line in file2:
#     list2.append()
print(list1)
