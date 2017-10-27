print(lambda x:sum(x[i]*x[len(x)-i-1]%10007 for i in xrange(len(x))))(sorted([int(__import__('sys').stdin.readline().strip())for _ in xrange(int(__import__('sys').stdin.readline().strip()))]))%10007
