import os.path, time, sys
HAS_CHANGED = 0
fileName = sys.argv[1]
timeByClient = sys.argv[2]
timeFileLastModified = time.strptime(time.ctime(os.path.getmtime(fileName)))
timeByClientInFormat = time.strptime(timeByClient)

if timeFileLastModified > timeByClientInFormat:
    HAS_CHANGED  = 1
    print 1
else:
    print 0
