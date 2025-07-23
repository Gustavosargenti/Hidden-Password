#ifndef JOGADOR_H
#define JOGADOR_H

#include <vector>

// Responsável por ler um palpite do usuário
class Jogador {
public:
    // Lê um palpite de tamanho exato e retorna um vetor
    std::vector<int> fazerPalpite(int tamanhoSenha);
};

#endif // JOGADOR_H
