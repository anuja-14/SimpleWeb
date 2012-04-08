import sys

f = open("history","w")
f.write(sys.argv[1])
f.close()
print sys.argv[1]
print 'hello'
