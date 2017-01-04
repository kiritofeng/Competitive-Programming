print((lambda x:'There %s %d way%s to get the sum 10.'%(['is','are'][x!=1],x,['','s'][x!=1]))(sum([i+j==8 for i,j in __import__('itertools').product(range(input()),range(input()))])))
