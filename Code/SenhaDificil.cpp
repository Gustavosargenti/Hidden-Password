#include "SenhaDificil.h"
#include <random>           //geração de números aleatórios
#include <algorithm>

// Gera 4 dígitos aleatórios
void SenhaDificil::gerar() {
    numeros.clear();
    std::mt19937 gen{ std::random_device{}() };  //(mt19937) gerador de números aleatórios
    std::uniform_int_distribution<> dist(0,9);   //distribuição uniforme de inteiros de 0 a 9 (frequência de aparecimento)
    for (int i = 0; i < 4; ++i)
        numeros.push_back(dist(gen));           //produz um número aleatório entre 0–9,
}

// Embaralha os dígitos existentes
void SenhaDificil::embaralharSenha() {
    std::shuffle(                               //função que rearranja aleatoriamente os numeros
        numeros.begin(), numeros.end(),         //delimita todo o vetor
        std::mt19937{ std::random_device{}() }  //semente vinda de random_device, usado por shuffle
    );
}
