#!/usr/bin/python
import sys

pi = 0
for n in range(10000):
    pi += (-1)**n /  (2*n+1)
f = open(sys.argv[1], 'w')
f.write(str(pi*4))
f.close()

print("Wrote", pi*4)