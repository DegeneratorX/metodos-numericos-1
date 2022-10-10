#include<iostream>
#include<cmath>

using namespace std;

double modulo(double x){
    if (x < 0){
        return -(x);
    }
    return x;
}

int ipow(int base, int exp)
{
    int result = 1;
    while (true)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (exp == 0)
            break;
        base *= base;
    }

    return result;
}

double round_prec(double n, int prec)
{
    return std::round(n * ipow(10, prec)) / ipow(10, prec);
}

double* f(double x){
    double* res = new double;
    //*res = pow(x, 3) - 9*x + 5;
    *res = exp(x)-4*pow(x,2);
    return res;
}

double* dxf(double x){
    double* res = new double;
    //*res =  3*pow(x, 2) - 9;
    *res = exp(x) - 8*x;
    return res;
}

double newton(double *f(double), double *dxf(double), double tol, double x, int aprox = 4, int iter = 50){

    if (dxf == 0){
        cout << "Erro: a derivada de f eh zero.\n";
        return NULL;
    }

    float Fx = round_prec(*f(x), aprox);

    cout << "k\t x \t\t f(x)\t\t f'(x)\n";
    cout << 0 << "\t" << round_prec(x, aprox) << "\t\t" << Fx << "\t" << round_prec(*dxf(x), aprox) << "\n";

    if (modulo(Fx) <= tol){
        return x;
    }

    int k = 1;

    while(k<=iter){
        x = round_prec(x+(-(*f(x))/(*dxf(x))), aprox);
        Fx = round_prec(*f(x), aprox);

        cout << k << "\t" << round_prec(x, aprox) << "\t" << Fx << "\t" << round_prec(*dxf(x), aprox) << "\n";
        if (modulo(Fx) <= tol){
            return x;
        }
        k = k + 1;
    }
    return NULL;
}

int main(){
    double x, tol, res;
    int aprox;
    cout << "\nDigite o valor inicial x: ";
    cin >> x;
    cout << "\nDigite a tolerancia: ";
    cin >> tol;
    cout << "\nDigite o numero de casas decimais a ser trabalhada: ";
    cin >> aprox;
    cout << "\n";

    res = newton(&f, &dxf, tol, x, aprox);

    if (res == NULL){
        cout << "O metodo retornou um erro.";
    } else {cout << "Raiz: " << res;}
}