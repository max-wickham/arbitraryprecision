from encryption import generatePrime

class keys:

    @staticmethod
    def generate(bits):
        primeP = generatePrime(bits)
        primeQ = generatePrime(bits)
        #create the keys and save them
        #shoudl return two keys, one private and one public

    def __init__(self,key,n):
        self.key = key
        self.n = n
    
def encrypt(message,key):
    return
    #encrypt the message

def decrypt(message,key):
    return
    #decrypt the message 

def prime(n):
    n = generatePrime(2000)
    return n

