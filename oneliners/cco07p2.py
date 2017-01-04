print((lambda N: 'No two snowflakes are alike.' if len({tuple(sorted(raw_input().split())) for _ in xrange(N)}) == N else 'Twin snowflakes found.')(int(raw_input())))
