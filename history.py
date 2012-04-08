import sys
from datetime import datetime
current = []
f = open("history","r+")
flag = 1
now = datetime.now()
current = str(now).split()
for line in f.readlines():
    data = line.split()
    url = data[0]
    day = data[1]
    time = data[2]
    if url == sys.argv[1]:
        flag = 0
        FMT = '%H:%M:%S'
        tdelta = datetime.strptime(current[1], FMT) - datetime.strptime(time, FMT)
        td = str(tdelta)
        if tdelta > '0:50:0':
            has_changed = 1
            print 1
        else :
            has_changed = 0
            print 0
if flag == 1:
    f.write(sys.argv[1] + " " + str(current[0]) + " " + str(current[1]))
f.close()
print 'hello'
