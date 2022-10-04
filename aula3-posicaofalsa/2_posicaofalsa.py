from math import e as euler, sin, cos

def f(x): return -((euler**x)/2) + 2*cos(x)

def posicao_falsa(f, a, b, tol, aprox = 4, iter_max = 20):
    Fa = round(f(a), aprox)
    Fb = round(f(b), aprox)
    if Fa * Fb > 0:
        print("Erro, a função não muda de sinal")
        return (False, None)

    intervX = round(abs(b-a), aprox)

    if intervX <= tol:
        return (True, x)
    if round(abs(f(a)), aprox) <= tol:
        return (True, a)
    if round(abs(f(b)), aprox) <= tol:
        return (True, b)

    k = 1

    print("k\t a\t\t b\t\t x\t\t fx")

    while k <= iter_max:
        x = round((a * f(b) - b * f(a))/(f(b) - f(a)), aprox)
        Fx = round(f(x), 4)

        print("%d\t%e\t%e\t%e\t%e" % (k, a, b, x, Fx))

        if abs(Fx) <= tol:
            return (True, x)

        if Fa * Fx > 0:
            a = x
            Fa = Fx
        else:
            b = x
            Fb = Fx
        
        intervX = round(abs(b-a), aprox)

        if intervX <= tol:
            return (True, x)
        k += 1

    print("Erro, número máximo de iterações atingido")
    return (False, x)

a = float(input("Digite o a: "))
b = float(input("Digite o b: "))
tol = float(input("Digite a tolerância: "))
aprox = int(input("Digite o número de casas decimais a ser trabalhada: "))


(sem_erro, raiz) = posicao_falsa(f, a, b, tol, aprox)

if sem_erro == False:
    print("O método retornou um erro.")
if raiz is not None:
    print(f"Raíz: {raiz}")