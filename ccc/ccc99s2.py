import re
import datetime
input = raw_input

m = ['January', 'February', 'March', 'April',' May', 'June', 'July', 'Augest', 'September', 'October', 'November', 'December']

def cvt1(x):
    try:
        y = int(x.group(3))
        if y < 25:
            y += 2000
        else:
            y += 1900
        datetime.datetime(y, int(x.group(2)), int(x.group(1)))
        return '%s/%s/%d' % (x.group(1), x.group(2), y)
    except ValueError:
        return '%s/%s/%s' % (x.group(1), x.group(2), x.group(3))


def cvt2(x):
    try:
        y = int(x.group(1))
        if y < 25:
            y += 2000
        else:
            y += 1900
        datetime.datetime(y, int(x.group(2)), int(x.group(3)))
        return '%d.%s.%s' % (y, x.group(2), x.group(3))
    except ValueError:
        return '%s.%s.%s' % (x.group(1), x.group(2), x.group(3))


def cvt3(x):
    global m
    try:
        y = int(x.group(3))
        if y < 25:
            y += 2000
        else:
            y += 1900
        datetime.datetime(y, m.index(x.group(1)) + 1, int(x.group(2)))
        return '%s %s, %d' % (x.group(1), x.group(2), y)
    except ValueError:
        return '%s %s, %s' % (x.group(1), x.group(2), x.group(3))


for _ in xrange(int(input())):
    s = input()
    s = re.sub(r'\b(\d\d)/(\d\d)/(\d\d)\b', lambda x: cvt1(x), s)
    s = re.sub(r'\b(\d\d)\.(\d\d)\.(\d\d)\b', lambda x: cvt2(x), s)
    s = re.sub(r'\b(%s) (\d\d), (\d\d)\b' % '|'.join(m), lambda x: cvt3(x), s)
    print s
