#ifndef SENHAMEDIA_H
#define SENHAMEDIA_H

#include "Senha.h"

// Gera senha de 4 dígitos
class SenhaMedia : public Senha {
public:
    void gerar() override;
};

#endif // SENHAMEDIA_H
