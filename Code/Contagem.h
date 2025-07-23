#ifndef CONTAGEM_H
#define CONTAGEM_H

// Classe que conta o número de tentativas
class Contagem {
private:
    int contador;
public:
    Contagem();
    void iniciarContagem();
    void incrementar();
    int getContador() const;
};

#endif // CONTAGEM_H
