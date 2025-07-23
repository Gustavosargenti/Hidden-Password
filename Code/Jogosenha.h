#ifndef JOGOSENHA_H
#define JOGOSENHA_H

#include "Jogador.h"
#include "Dificuldade.h"
#include "Senha.h"
#include "Contagem.h"
#include <memory>

// Classe que controla o fluxo principal do jogo

class JogoSenha {
private:
    Dificuldade dificuldade;        // Armazena o nível de dificuldade escolhido (Fácil, Médio, Difícil)
    Contagem tentativas;            // Conta quantas tentativas o jogador já fez
    std::unique_ptr<Senha> senha;   // Ponteiro que aponta para SenhaFacil,SenhaMedia ou SenhaDificil
    Jogador jogador;                // Objeto que solicita e lê palpites do usuário
    int limiteTempo;                // Tempo máximo permitido em segundos (0 significa sem limite)
    void configurarJogo();          // lê configurações do usuário (dificuldade e tempo) e gera a senha correspondente

public:
    JogoSenha();               // Construtor: inicializa limiteTempo com valor padrão (0)
    void iniciarJogo();        // Inicia o loop principal: solicita palpites até vitória ou fim de tempo
    void finalizarJogo();      // Exibe mensagem de término de jogo
};

#endif // JOGOSENHA_H
