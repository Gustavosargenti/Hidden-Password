#include "Dificuldade.h"

// inicializa nível como FACIL
Dificuldade::Dificuldade() : nivel(NivelDificuldade::FACIL) {}

// Altera o nível
void Dificuldade::definirNivel(NivelDificuldade n) {
    nivel = n;
}

// Retorna o nível atual
NivelDificuldade Dificuldade::getNivel() const {
    return nivel;
}
