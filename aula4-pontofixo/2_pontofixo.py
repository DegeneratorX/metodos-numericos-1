from numpy import log as ln

def f(x):
    return x - x*ln(x)
    #return x**3-9*x+3

def q(x):
    return x*ln(x)
    #return (x**3+3)/9

def ponto_fixo(f, q, tol, x, aprox = 4, iter = 50):

    Fx = round(f(x), aprox)

    print("k\t x\t\t f(x)\t\t q(x)")
    print("%d\t%e\t%e\t%e" % (0, round(x,aprox), Fx, round(q(x),aprox)))

    if abs(Fx) <= tol:
        return (True, x)

    k = 1

    while(k<=iter):
        x = round(q(x), aprox)
        Fx = round(f(x), aprox)
        print("%d\t%e\t%e\t%e" % (k, round(x,aprox), Fx, round(q(x),aprox)))

        if abs(Fx) <= tol:
            return (True, x)
        k+=1
    return (False, None)

x = float(input("Digite o valor inicial x inicial: "))

tol = float(input("Digite a tolerancia: "))

aprox = int(input("Digite o número de casas decimais a ser trabalhada: "))

(sem_erro, raiz) = ponto_fixo(f, q, tol, x, aprox)

if sem_erro == False:
    print("O método retornou um erro.")
if raiz is not None:
    print(f"Raíz: {raiz}")
