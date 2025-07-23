#include "SenhaMedia.h"
#include <random>

// Gera 4 dígitos aleatórios entre 0 e 9
void SenhaMedia::gerar() {
    numeros.clear();
    std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0,9);
    for (int i = 0; i < 4; ++i)
        numeros.push_back(dist(gen));
}
