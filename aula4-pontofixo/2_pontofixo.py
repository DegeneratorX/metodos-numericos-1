from math import e as euler, cos, sin

def f(x):
    #return -((euler**x)/2) + 2*cos(x)]
    return x**3-9*x+5

def dxf(x):
    #return -((4*sin(x)+euler**x)/2)
    return 3*x**2-9

def q(x):
    return (x**3+5)/9

def ponto_fixo(f, q, tol, x, iter = 50):
    
    if abs(f(x)) <= tol:
        return (True, x)

    Fx = round(f(x), 4)
    if abs(Fx) < tol:
        return (True, x)

    print("k\t x\t\t f(x)\t\t f'(x)")
    print("%d\t%e\t%e\t%e" % (0, round(x,4), Fx, round(dxf(x),4)))


    k = 1

    while(k<=iter):
        x = round(x+(-f(x)/dxf(x)), 4)
        Fx = round(f(x), 4)
        print("%d\t%e\t%e\t%e" % (k, round(x,4), Fx, round(dxf(x),4)))

        if abs(Fx) < tol:
            return (True, x)
        k+=1
    return (False, None)

x = float(input("Digite o valor inicial x inicial: "))

tol = float(input("Digite a tolerancia: "))

(sem_erro, raiz) = newton(f, dxf, tol, x)

if sem_erro == False:
    print("O método retornou um erro.")
if raiz is not None:
    print(f"Raíz: {raiz}")
