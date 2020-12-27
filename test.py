import random 

def prime(n, k = 4):
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

# def rand(n):
#     a = random.randint(pow(2,n-1),pow(2,n))
#     if(a % 2 == 0): 
#         a += 1
#     return a
def rand(n):
    nums = [211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839]
    result = 1
    for i in range(0,int(n/7)):
        a = random.randint(0,99)
        result *= nums[a]
    result *= 2
    result += 1
    return result
        

n = 64
a = rand(n)
count = 0
while(not prime(a)):
    if( count % 1 == 0):
        print(count)
        print(a)
    count += 1
    a = rand(n)
print ("Prime: " + str(a))