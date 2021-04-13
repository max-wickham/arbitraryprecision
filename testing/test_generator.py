import re
from jinja2 import Template
import math
import random

max_pow = 32

def convert(num):
    x = bin(int(num))[2:]
    result = "}"
    while len(x) >= max_pow:
        n = int(x[-max_pow:],2)
        result = "," + str(n) + result
        x = x[:-max_pow]
    if len(x) > 0:
        n = int(x,2)
        result = '{' + str(n) + result
    else:
        result = '{' + result[1:]
    return result

test_cases = {}
test_cases = {}
operands = {}
#generate multiplications
max_int = (2<< (max_pow*5)) - 1

# test_cases["MaxBit"] = {}
# operands["MaxBit"] = ["",""]
# operands["MaxBit"][0] = "int x = a.max_bit()"
# operands["MaxBit"][1] = "d.equal(x)"
# for i in range(100):
#     random1 = random.randrange(0,max_int)
#     random2 = 0
#     result = len(bin(random1)[2:])
#     test_cases["MaxBit"]["test"+str(i)] = [convert(random1),convert(random2),convert(result)]

# test_cases["SubtractionSelf"] = {}
# operands["SubtractionSelf"] = ["",""]
# operands["SubtractionSelf"][0] = "a.subtraction_self(b)"
# operands["SubtractionSelf"][1] = "d.equal(a)"
# for i in range(100):
#     random1 = random.randrange(0,max_int)
#     random2 = random.randrange(0,random1)
#     result = random1-random2
#     test_cases["SubtractionSelf"]["test"+str(i)] = [convert(random1),convert(random2),convert(result)]

# test_cases["AdditionSelf"] = {}
# operands["AdditionSelf"] = ["",""]
# operands["AdditionSelf"][0] = "a.addition_self_unsigned(b)"
# operands["AdditionSelf"][1] = "d.equal(a)"
# for i in range(100):
#     random1 = random.randrange(0,max_int)
#     random2 = random.randrange(0,max_int)
#     result = random1+random2
#     test_cases["AdditionSelf"]["test"+str(i)] = [convert(random1),convert(random2),convert(result)]

# test_cases["Multiplication"] = {}
# operands["Multiplication"] = ["",""]
# operands["Multiplication"][0] = "a.multiplication(b,c)"
# operands["Multiplication"][1] = "d.equal(c)"
# for i in range(100):
#     random1 = random.randrange(0,max_int)
#     random2 = random.randrange(0,max_int)
#     result = random1*random2
#     test_cases["Multiplication"]["test"+str(i)] = [convert(random1),convert(random2),convert(result)]

# test_cases["MultiplicationSelf"] = {}
# operands["MultiplicationSelf"] = ["",""]
# operands["MultiplicationSelf"][0] = "a.multiplication_self(b)"
# operands["MultiplicationSelf"][1] = "d.equal(a)"
# for i in range(100):
#     random1 = random.randrange(0,max_int)
#     random2 = random.randrange(0,max_int)
#     result = random1*random2
#     test_cases["MultiplicationSelf"]["test"+str(i)] = [convert(random1),convert(random2),convert(result)]

# test_cases["DivisionSelf"] = {}
# operands["DivisionSelf"] = ["",""]
# operands["DivisionSelf"][0] = "a.division_self(b)"
# operands["DivisionSelf"][1] = "d.equal(a)"
# for i in range(100):
#     random1 = random.randrange(0,max_int)
#     random2 = random.randrange(0,max_int)
#     result = int(random1/random2)
#     test_cases["DivisionSelf"]["test"+str(i)] = [convert(random1),convert(random2),convert(result)]

# test_cases["Modulus"] = {}
# operands["Modulus"] = ["",""]
# operands["Modulus"][0] = "c = a.modulus(b)"
# operands["Modulus"][1] = "d.equal(c)"
# for i in range(100):
#     random1 = random.randrange(0,max_int)
#     random2 = random.randrange(0,max_int)
#     result = random1%random2
#     test_cases["Modulus"]["test"+str(i)] = [convert(random1),convert(random2),convert(result)]


test_cases["ModuloPow"] = {}
operands["ModuloPow"] = ["",""]
operands["ModuloPow"][0] = "c = a.modulo_pow(b,d)"
operands["ModuloPow"][1] = "e.equal(c)"
for i in range(10):
    random1 = random.randrange(0,max_int)
    random2 = random.randrange(0,max_int)
    random3 = random.randrange(0,max_int)
    result = pow(random1,random2,random3)
    test_cases["ModuloPow"]["test"+str(i)] = [convert(random1),convert(random2),convert(random3),convert(result)]

test_cases["ShiftRight"] = {}
operands["ShiftRight"] = ["",""]
operands["ShiftRight"][0] = "a.shift_right_self(f)"
operands["ShiftRight"][1] = "e.equal(a)"
for i in range(10):
    random1 = random.randrange(0,max_int)
    random4 = random.randrange(0,len(bin(random1)[2:]))
    result = random1 >> random4
    test_cases["ShiftRight"]["test"+str(i)] = [convert(random1),convert(0),convert(0),convert(result),random4]

test_cases["ShiftLeft"] = {}
operands["ShiftLeft"] = ["",""]
operands["ShiftLeft"][0] = "a.shift_left_self(f)"
operands["ShiftLeft"][1] = "e.equal(a)"
for i in range(10):
    random1 = random.randrange(0,max_int)
    random4 = random.randrange(0,len(bin(random1)[2:]))
    result = random1 << random4
    test_cases["ShiftLeft"]["test"+str(i)] = [convert(random1),convert(0),convert(0),convert(result),random4]

test_cases["DivisionInt"] = {}
operands["DivisionInt"] = ["",""]
operands["DivisionInt"][0] = "a.division_self(f)"
operands["DivisionInt"][1] = "e.equal(a)"
for i in range(10):
    random1 = random.randrange(0,max_int)
    random4 = random.randrange(0,pow(2,max_pow-10)-1)
    result = int(random1 // random4)
    test_cases["DivisionInt"]["test"+str(i)] = [convert(random1),convert(0),convert(0),convert(result),random4]

output = open("./tests1.cpp", "w")
inputFile = open("tests_template.cpp", "r")
tm = Template(inputFile.read())
output.write(tm.render(test_cases = test_cases, operands = operands))
output.close()
inputFile.close()
