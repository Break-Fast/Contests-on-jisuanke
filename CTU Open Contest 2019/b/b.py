I = input
R = lambda : map(int, input().split())
ans = 0
while True :
    try :
        s = I()
        indx = s.find(',')
        if indx == -1 :
            ans += s.count('|') * 42
        else :
            ans += int(s[:indx]) * max(s.count('|'), 1)
            #if(s.count('|') > 1) : ans += s.count('|')
    except EOFError:
        break
print((ans + 9) // 10 * 10, ',-', sep='')

