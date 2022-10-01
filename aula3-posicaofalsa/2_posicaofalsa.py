def f(x): return x**3-9*x+3

def posicao_falsa(f, a, b, tol, iter_max = 20):
    Fa = f(a)
    Fb = f(b)
    if Fa * Fb > 0:
        print("Erro, a função não muda de sinal")
        return (False, None)

    intervX = abs(b-a)

    if intervX <= tol:
        return (True, x)
    if abs(f(a)) <= tol:
        return (True, a)
    if abs(f(b)) <= tol:
        return (True, b)

    k = 1

    print("k\t a\t\t fa\t\t b\t\t fb\t\t x\t\t fx\t\tintervX")

    while k <= iter_max:
        x = (a * f(b) - b * f(a))/(f(b) - f(a))
        Fx = f(x)

        print("%d\t%e\t%e\t%e\t%e\t%e\t%e\t%e" % (k, a, Fa, b, Fb, x, Fx, intervX))

        if abs(Fx) <= tol:
            return (True, x)

        if Fa * Fx > 0:
            a = x
            Fa = Fx
        else:
            b = x
            Fb = Fx
        
        intervX = abs(b-a)

        if intervX <= tol:
            return (True, x)
        k += 1

    print("Erro, número máximo de iterações atingido")
    return (False, x)

a = float(input("Digite o a: "))
b = float(input("Digite o b: "))
tol = float(input("Digite a tolerância: "))


(sem_erro, raiz) = posicao_falsa(f, a, b, tol)

if sem_erro == False:
    print("O método retornou um erro.")
if raiz is not None:
    print(f"Raíz: {raiz}")