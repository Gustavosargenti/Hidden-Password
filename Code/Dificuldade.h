#ifndef DIFICULDADE_H
#define DIFICULDADE_H

// Níveis de dificuldade disponíveis
enum class NivelDificuldade {
    FACIL  = 1,
    MEDIO  = 2,
    DIFICIL = 3
};

// Guarda o nível selecionado
class Dificuldade {
private:
    NivelDificuldade nivel;
public:
    Dificuldade();
    void definirNivel(NivelDificuldade n);
    NivelDificuldade getNivel() const;
};

#endif // DIFICULDADE_H
