from math import e as euler, cos, sin, log10
from numpy import log as ln

def f(x):
    #return x - x*ln(x)
    #return -((euler**x)/2) + 2*cos(x)
    return x**3-9*x+5

def dxf(x):
    #return -log10(x)
    #return -((4*sin(x)+euler**x)/2)
    return 3*x**2-9

def g(x): return (1/8)*x**4 - 2*x**3 + 9*x**2 - 12*x + 3

def dxg(x): return (x**3/2)-6*x**2+18*x-12

def newton(f, dxf, tol, x, aprox = 4, iter = 500):

    if dxf == 0:
        print("Erro: a derivada de f é zero.")
        return (False, None)

    Fx = round(f(x), aprox)

    print("k\t x\t\t f(x)\t\t f'(x)")
    print("%d\t%e\t%e\t%e" % (0, round(x,aprox), Fx, round(dxf(x),aprox)))

    if abs(Fx) <= tol:
        return (True, x)

    k = 1

    while(k<=iter):
        x = round(x+(-f(x)/dxf(x)), aprox)
        Fx = round(f(x), aprox)
        print("%d\t%e\t%e\t%e" % (k, round(x, aprox), Fx, round(dxf(x), aprox)))
        if abs(Fx) <= tol:
            return (True, x)
        k+=1
    return (False, None)

x = float(input("Digite o valor inicial x inicial: "))

tol = float(input("Digite a tolerancia: "))

aprox = int(input("Digite o número de casas decimais a ser trabalhada: "))

(sem_erro, raiz) = newton(g, dxg, tol, x, aprox)

if sem_erro == False:
    print("O método retornou um erro.")
if raiz is not None:
    print(f"Raíz: {raiz}")