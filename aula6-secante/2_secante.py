from math import e as euler, cos, sin
from numpy import log as ln

def f(x):
    return -((euler**x)/2) + 2*cos(x)
    #return x**3 - 9*x + 5

def dxf(x):
    #return -((4*sin(x)+euler**x)/2)
    return x**3 - 9*x + 5;

def secante(f, tol, x0, x1, aprox = 4, iter = 50):

    Fx0 = round(f(x0), aprox)

    print("k\t x\t\t f(x)")
    print("%d\t%e\t%e" % (0, round(x0, aprox), Fx0))

    if abs(Fx0) <= tol:
        return (True, x0)

    Fx1 = round(f(x1), aprox)

    print("%d\t%e\t%e" % (1, round(x1, aprox), Fx1))

    if abs(Fx1) <= tol:
        return (True, x1)

    k = 2

    while(k<=iter):
        temp = x0
        x0 = x1
        x1 = round(x1-((f(x1)*(x1-temp))/(f(x1)-f(temp))), aprox)
        Fx = round(f(x1), 4)
        print("%d\t%e\t%e" % (k, round(x1,aprox), Fx))
        if abs(Fx) <= tol:
            return (True, x1)
        k+=1
    return (False, None)

x0 = float(input("Digite o valor x0: "))
x1 = float(input("Digite o valor x1: "))

tol = float(input("Digite a tolerancia: "))
aprox = int(input("Digite o número de casas decimais a ser trabalhada: "))

(sem_erro, raiz) = secante(f, tol, x0, x1, aprox)

if sem_erro == False:
    print("O método retornou um erro.")
if raiz is not None:
    print(f"Raíz: {raiz}")