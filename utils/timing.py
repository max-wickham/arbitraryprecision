import time

a = 1*pow(2,32) + 2*pow(2,16) + 3
b = 2*pow(2,32) + 3*pow(2,16) + 4
c = 0

start = time.time()
for i in range(100000):
    c = a + b + a + b
end = time.time()
print("Time " + str(int((end-start)*1000)) + "ms")