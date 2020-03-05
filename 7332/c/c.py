for _ in range(int(input())) :
    k, *a = map(int, input().split())
    print('Prime Factorization #%d:' % (_ + 1))
    t = []
    b = []
    for i in range(k) :
        t.append((a[i * 2], a[i * 2 + 1]))
        b.append(a[i * 2])
    tt = {}
    t.sort()
    b = list(set(b))
    b.sort()
    k = len(b)
    for i in t :
        if i[0] not in tt :
            tt[i[0]] = i[1]
        else :
            tt[i[0]] += i[1]
    
#print(*[tt[b[x // 2]] if x % 2 else ' ' + str(b[x // 2]) for x in range(2 * k)])
    print(*[tt[b[x // 2]] if x % 2 else ' ' * len(str(b[x // 2])) for x in range(2 * k)], sep='')
    print(*[b[x // 2] if x % 2 == 0 else ' ' * len(str(tt[b[x // 2]])) for x in range(2 * k - 1)], sep='')
    print()

