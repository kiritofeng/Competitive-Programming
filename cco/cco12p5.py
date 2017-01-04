from sys import stdin
input = stdin.readline
P = {int(input()) for _ in xrange(int(input()))}
for i in xrange(1, 101):
    if P.issubset({round(x * 100.0/i) for x in xrange(i + 1)}):
        print i
        break
