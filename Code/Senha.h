#ifndef SENHA_H
#define SENHA_H

#include <vector>

// Classe abstrata para geração e verificação de senha
class Senha {
protected:
    std::vector<int> numeros;      // dígitos da senha
public:
    virtual ~Senha() {}            // destrutor virtual
    virtual void gerar() = 0;
    int verificarPosicao(const std::vector<int>& tentativa) const;
    int getTamanho() const;
};

#endif // SENHA_H
