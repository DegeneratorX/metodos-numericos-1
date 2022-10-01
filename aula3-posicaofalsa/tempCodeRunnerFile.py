(sem_erro, raiz) = posicao_falsa(f, a, b, tol)

if sem_erro == False:
    print("O método retornou um erro.")
if raiz is not None:
    print(f"Raíz: {raiz}")