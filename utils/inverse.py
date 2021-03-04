def modInverse(a, m):
    m0 = m
    y = 0
    x = 1
 
    if (m == 1):
        return 0
 
    while (a > 1):
 
        # q is quotient
        q = a // m
 
        t = m
 
        # m is remainder now, process
        # same as Euclid's algo
        m = a % m
        a = t
        t = y
 
        # Update x and y
        y = x - q * y
        x = t

    # Make x positive
    if (x < 0):
        x = x + m0
 
    return x

a = 284405200190476652636583234372541649370526224895762840695503
m = 546959750665044389637270698327253523428879552773476640320488
cx = pow(a,-1,m)
print(cx)
print(modInverse(a,m))
one = (a*modInverse(a,m)) % 532598620183
print(one)
531782086599