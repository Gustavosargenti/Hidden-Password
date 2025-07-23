#ifndef SENHAFACIL_H
#define SENHAFACIL_H

#include "Senha.h"

// Gera senha de 3 dígitos
class SenhaFacil : public Senha {
public:
    void gerar() override;
};

#endif // SENHAFACIL_H
