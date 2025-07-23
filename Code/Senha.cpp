#include "Senha.h"

// Conta quantos dígitos estão na posição correta
int Senha::verificarPosicao(const std::vector<int>& tentativa) const {
    int acertos = 0;
    for (size_t i = 0; i < tentativa.size() && i < numeros.size(); ++i) {
        if (tentativa[i] == numeros[i])
            ++acertos;
    }
    return acertos;
}

// Retorna quantos dígitos a senha possui
int Senha::getTamanho() const {
    return static_cast<int>(numeros.size());
}
