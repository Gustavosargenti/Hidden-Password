#include "Jogador.h"
#include <iostream>
#include <string>

// Pede até o usuário digitar exatamente a quantidade de caracteres da senha
std::vector<int> Jogador::fazerPalpite(int tamanhoSenha) {
    std::string entrada;
    do {
        std::cout << "Informe seu palpite (" << tamanhoSenha << " dígitos): ";
        std::cin >> entrada;
    } while ((int)entrada.size() != tamanhoSenha);

    // Converte cada caractere em número
    std::vector<int> resultado;
    for (char c : entrada) {
        resultado.push_back(c - '0');
    }
    return resultado;
}
