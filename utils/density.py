bits = float(input())
from numpy import log
total = (pow(2,bits+1))/log(pow(2,bits+1)) - (pow(2,bits))/log(pow(2,bits))
density = (pow(2,bits+1) - pow(2,bits)) / total
print(density)