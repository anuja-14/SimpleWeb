import os.path, time, sys
f = open('history', "r")
fileRequested = sys.argv[1]
timeFileCreated = (time.ctime(os.path.getmtime(fileRequested)))
print timeFileCreated

