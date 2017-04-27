print((lambda x: sum(sorted([max(int(raw_input()), 0) for i in xrange(x[0])], reverse=1)[:x[1]]))(map(int, raw_input().split())))
