#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// Função para verificar se o número está de acordo com a base fornecida
bool numeroValidoParaBase(const string& numero, int base) { //verifica o numero e a bas

    //Percorre cada caractere de numero
    for (char c : numero) { 
        int valor = (c >= '0' && c <= '9') ? c - '0' :  //Se for um número, subtrai o valor dele pelo valor de '0' de acordo com a tabela ascii
                    (c >= 'A' && c <= 'Z') ? c - 'A' + 10 : //Se for alfabético, faz o mesmo mas com o valor de 'A' e adiciona 10, código ASCII do caractere c - código ASCII do caractere 'A'.
                    (c >= 'a' && c <= 'z') ? c - 'a' + 10 : -1; //Se não for um dígito, atribui -1 para o retorno ser falso
        if (valor < 0 || valor >= base) return false;  // Retorna falso se for inválido para a base
    }
    return true;  //
}

// Função para multiplicar uma string numérica por um inteiro
string multiplicaStringPorInt(const string& numero, int multiplicador) { //constante para uma string que representa o número a ser multiplicado.
    string resultado;
    int ultra = 0; 

    //Percorre a string numero de trás para frente
    for (int i = numero.size() - 1; i >= 0; i--) { //percorre a string numero da direita para a esquerda, de trás para frente
        int produto = (numero[i] - '0') * multiplicador + ultra; //Converte o caractere para o seu valor inteiro e soma o valor da iteração anterior
        ultra = produto / 10; //calcula o ultra para a proxima iteração
        resultado.push_back((produto % 10) + '0');
    }

    while (ultra) {
        resultado.push_back((ultra % 10) + '0'); // verifica se restaram valores e adiciona no resultado
        ultra /= 10; 
    }

    reverse(resultado.begin(), resultado.end()); //Inverte a string antes de retorna-la
    return resultado;
}

// Função para adicionar duas strings numéricas para evitar estouro 
string adicionaStrings(const string& num1, const string& num2) { //recebe duas strings que representam numeros
    string resultado; 
    int ultra = 0; 
    int tamanho1 = num1.size(), tamanho2 = num2.size();
    int i = tamanho1 - 1, j = tamanho2 - 1; 

    while (i >= 0 || j >= 0 || ultra) { //continua enquanto houver dígitos ou ultra para somar
        int soma = ultra; //inicia com a soma da iteração anterior
        if (i >= 0) soma += num1[i--] - '0'; 
        if (j >= 0) soma += num2[j--] - '0';
        ultra = soma / 10;
        resultado.push_back((soma % 10) + '0'); 
    }

    reverse(resultado.begin(), resultado.end()); //Inverte o resultado
    return resultado;
}

// Função para converter de qualquer base para decimal
string converterParaDecimal(const string& numero, int baseInicial) {
    string valor_decimal = "0";
    string potenciaBase = "1";

    for (int i = numero.size() - 1; i >= 0; i--) {
        char digito = numero[i]; 
        int valor = (digito >= '0' && digito <= '9') ? digito - '0' : 
                    (digito >= 'A' && digito <= 'Z') ? digito - 'A' + 10 : 
                    digito - 'a' + 10;

        valor_decimal = adicionaStrings(valor_decimal, multiplicaStringPorInt(potenciaBase, valor));
        potenciaBase = multiplicaStringPorInt(potenciaBase, baseInicial);
    }
    return valor_decimal;
}

// Função para converter de decimal para qualquer base
string converterDeDecimal(const string& valor_decimal, int baseFinal) {
    if (valor_decimal == "0") return "0";

    string resultado;
    string valor = valor_decimal;

    while (valor != "0") {
        int resto = 0;
        string novoValor;

        for (char c : valor) {
            int num = resto * 10 + (c - '0');
            novoValor.push_back((num / baseFinal) + '0');
            resto = num % baseFinal;
        }

        novoValor.erase(0, min(novoValor.find_first_not_of('0'), novoValor.size() - 1));
        resultado.push_back((resto < 10) ? (resto + '0') : (resto - 10 + 'A'));
        valor = novoValor;
    }

    reverse(resultado.begin(), resultado.end());
    return resultado;
}


int main() {
    string numero;
    int baseInicial;
    int baseFinal;

    cout << "Digite o numero a ser convertido: ";
    cin >> numero;
    cout << "Digite o numero da base inicial: ";
    cin >> baseInicial;
    cout << "Digite o numero da base final: ";
    cin >> baseFinal;

    if (baseInicial < 2 || baseInicial > 36 || baseFinal < 2 || baseFinal > 36) {
        cout << "As bases devem estar entre 2 e 36." << endl;
        return 1;
    }

    if (!numeroValidoParaBase(numero, baseInicial)) {
        cout << "O numero fornecido nao eh valido para a base " << baseInicial << "." << endl;
        return 1;
    }

    string valor_decimal = converterParaDecimal(numero, baseInicial);
    string numero_convertido = converterDeDecimal(valor_decimal, baseFinal);

    cout << "\n\n   CONVERSAO\n----------------\n" 
         << numero << " em base " << baseInicial
         << "\nEquivale a \n" 
         << numero_convertido << " em base " << baseFinal << endl;

    return 0;
}
