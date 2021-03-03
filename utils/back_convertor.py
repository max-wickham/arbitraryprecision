x = input()
x = bin(int(x))[2:]
print(x)
print(len(x))
result = "}"
while len(x) >= 16:
    print(x[-16:])
    n = int(x[-16:],2)
    result = "," + str(n) + result
    x = x[:-16]
    print(len(x))
if len(x) > 0:
    n = int(x,2)
    print(n)
    result = '{' + str(n) + result
    print(result)
else:
    result = '{' + result[1:]
print(result)
