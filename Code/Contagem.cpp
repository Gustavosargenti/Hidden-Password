#include "Contagem.h"

//Contador começa em zero
Contagem::Contagem() : contador(0) {}

// Reinicia o contador para zero
void Contagem::iniciarContagem() {
    contador = 0;
}

// Incrementa o contador em 1
void Contagem::incrementar() {
    ++contador;
}

// Retorna o valor atual do contador
int Contagem::getContador() const {
    return contador;
}
