import random
import sympy

p1 = 5 * 10 ** 10
q1 = 7 * 10 ** 10
def primemodulo4equal3(num):
    while(num % 4 != 3):
        num = sympy.nextprime(num)
    return num

p = primemodulo4equal3(p1)
q = primemodulo4equal3(q1)

n = p*q

i = input("Enter the seed val :-")
random.seed(i)
x0 = random.randint(1, 1e10)
print(x0)
nbits = int(input("Enter number of bits :-"))

bits = []
intnum =0
for j in range(0,nbits):
    x0 = (x0*x0) % n
    y = x0 % 2
    bits.append(y)
    intnum += y*(2**(nbits-j-1))

print("Random number is :-",intnum)

