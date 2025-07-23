#include "JogoSenha.h"
#include "SenhaFacil.h"
#include "SenhaMedia.h"
#include "SenhaDificil.h"
#include <iostream>
#include <chrono>                 // Inclui utilitários de tempo (std::chrono)


// Construtor: inicia limiteTempo com zero (sem limite)
JogoSenha::JogoSenha()
    : limiteTempo(0)                // Inicializa o membro limiteTempo com 0
{}


// Método que lê as opções do usuário e gera a senha apropriada
void JogoSenha::configurarJogo() {
    int escolha;                            // Variável para armazenar escolha de dificuldade
    std::cout << "1) Fácil (3 dígitos)\n"   // Exibe menu de dificuldade
              << "2) Médio (4 dígitos)\n"
              << "3) Difícil (4 dígitos + embaralha a cada 15 tentativas)\n"
              << "Escolha: ";
    std::cin >> escolha;                    // Lê a escolha do usuário

    // Converte inteiro em NivelDificuldade e configura
    dificuldade.definirNivel(static_cast<NivelDificuldade>(escolha));

    std::cout << "Tempo limite (s, 0=∞): ";  // Pede tempo limite
    std::cin >> limiteTempo;            // Lê tempo em segundos (0 = sem limite)

    // Cria o objeto de senha conforme o nível escolhido
    switch (dificuldade.getNivel()) {
    case NivelDificuldade::FACIL:
        senha = std::make_unique<SenhaFacil>();   // 3 dígitos
        break;
    case NivelDificuldade::MEDIO:
        senha = std::make_unique<SenhaMedia>();   // 4 dígitos
        break;
    case NivelDificuldade::DIFICIL:
        senha = std::make_unique<SenhaDificil>(); // 4 dígitos + shuffle
        break;
    }

    senha->gerar();                // Gera os dígitos da senha
    tentativas.iniciarContagem();  // Reseta o contador de tentativas
}


// Loop principal do jogo em modo console
void JogoSenha::iniciarJogo() {
    configurarJogo();                                // Executa configuração inicial
    std::cout << "\n=== Iniciando Jogo ===\n";
    auto inicio = std::chrono::steady_clock::now();  // Marca o tempo de início

    while (true) {                                   // Loop infinito até vitória ou tempo esgotado
        // Verifica se ultrapassou o tempo limite (quando > 0)
        if (limiteTempo > 0) {
            auto agora = std::chrono::steady_clock::now();                                          // Tempo atual
            auto segs = std::chrono::duration_cast<std::chrono::seconds>( agora - inicio).count();  // Diferença entre agora e início
            if (segs >= limiteTempo) {                                                              // Se o tempo excedeu o limite
                std::cout << "\nTempo esgotado! Tentativas: "
                          << tentativas.getContador() << "\n";
                break;                   // Sai do loop (fim de jogo)
            }
        }

        // Solicita palpite ao jogador e incrementa contador
        auto chute = jogador.fazerPalpite(senha->getTamanho());
        tentativas.incrementar();

        // Verifica quantos dígitos acertou na posição correta
        int certos = senha->verificarPosicao(chute);
        if (certos == senha->getTamanho()) {  // Se acertou todos
            std::cout << "\nVocê acertou em " << tentativas.getContador() << " tentativas!\n";
            break;                            // Sai do loop (vitória)
        } else {
            // Caso contrário, mostra quantos estão corretos
            std::cout << "→ " << certos << " número(s) no lugar certo.\n";

            // Se modo difícil e a cada 15 tentativas, embaralha a senha
            if (dificuldade.getNivel() == NivelDificuldade::DIFICIL && tentativas.getContador() % 15 == 0)
            {
                auto sd = static_cast<SenhaDificil*>(senha.get()); // Cast para acessar embaralharSenha()
                sd->embaralharSenha();    // Embaralha os dígitos
                std::cout << "Senha foi embaralhada!\n";
            }
        }
    }

    finalizarJogo();
}


// Exibe mensagem de fim de jogo no console
void JogoSenha::finalizarJogo() {
    std::cout << "\n=== Fim de Jogo ===\n";  // Imprime cabeçalho de fim
}
