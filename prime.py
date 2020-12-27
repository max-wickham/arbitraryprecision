import random
def prime(n, k = 6):
    if(n == 1):
        return False
    
    _n = n
    _n -= 1
    s = 0
    r = n
    r -= 1
    while r % 2 == 0:
        s += 1
        r = int(r / 2)
    

    for i in range(0,k):
        a = random.randint(0, n -1)
        x = pow(a,r,n)
        if  not (x == 1) and  not(x == _n):
            j = 0
            j += 1
            while (j < s) and not (x == _n):
                x = x * x
                x = x % n
                if(x == 1):
                    return False
                
                j += 1
            
            if not(x==_n):
                return False
            
        
    
    return True


count = 0
n = 200
result = "["
while count < 100:
    print(n)
    if(prime(n)):
        print(n)
        result += str(n) + ","
        count += 1
        print("Count " + str(count))
    n += 1
print(result)