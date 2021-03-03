#converts from the bigint format to normal decimal

x = input()
x = x.split()

result = 0
for i in range(len(x)):
    result += int(x[len(x) - 1 - i]) * pow(pow(2,16),i)

print(result)

