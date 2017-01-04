from sys import stdin
S = set()
N = int(stdin.readline())
for i in xrange(N):
 tmp = sorted(map(int, stdin.readline().split()))
 sum = 0
 for j in xrange(6):
  sum += tmp[j]*10**(7*j)
 S.add(sum)
print 'No two snowflakes are alike.' if len(S) == N else 'Twin snowflakes found.'
