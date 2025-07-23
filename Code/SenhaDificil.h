#ifndef SENHADIFICIL_H
#define SENHADIFICIL_H

#include "Senha.h"

// Gera 4 dígitos + possibilidade de embaralhar
class SenhaDificil : public Senha {  //Classe SenhaDficil é subclasse de Senha
public:
    void gerar() override;
    void embaralharSenha();
};

#endif // SENHADIFICIL_H
