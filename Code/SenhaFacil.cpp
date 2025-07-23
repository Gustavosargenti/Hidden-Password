#include "SenhaFacil.h"
#include <random>

// Gera 3 dígitos aleatórios entre 0 e 9
void SenhaFacil::gerar() {
    numeros.clear();
    std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0,9);
    for (int i = 0; i < 3; ++i)
        numeros.push_back(dist(gen));
}
