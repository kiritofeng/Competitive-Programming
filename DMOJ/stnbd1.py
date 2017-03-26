print ['NO', 'YES'][(lambda x: x[0] > max(x[1:]))([int(raw_input()) for i in xrange(int(raw_input()))])]
