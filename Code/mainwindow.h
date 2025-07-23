#ifndef MAINWINDOW_H                       // Início do include guard para evitar múltiplas inclusões deste cabeçalho
#define MAINWINDOW_H                       // Declaração de que MAINWINDOW_H está definido

#include <QMainWindow>                     // Inclui a classe base QMainWindow do Qt
#include <QTimer>                          // Inclui a classe QTimer para temporização
#include <QVector>                         // Inclui o container QVector para armazenar listas
#include <QButtonGroup>                    // Inclui QButtonGroup para agrupar botões exclusivos
#include <memory>                          // Inclui utilitários de gerenciamento de memória (std::unique_ptr)
#include "Senha.h"                         // Inclui a interface abstrata de Senha do nosso projeto

class QRadioButton;                        // Declaração antecipada de QRadioButton
class QSpinBox;                            // Declaração antecipada de QSpinBox
class QPushButton;                         // Declaração antecipada de QPushButton
class QHBoxLayout;                         // Declaração antecipada de QHBoxLayout
class QLabel;                              // Declaração antecipada de QLabel

// Declaração da classe MainWindow que herda de QMainWindow
class MainWindow : public QMainWindow {
    Q_OBJECT                              // Macro necessária para usar sinais e slots no Qt

public:
    explicit MainWindow(QWidget *parent = nullptr);  // Construtor: opcionalmente recebe widget pai
    ~MainWindow() override;                          // Destrutor: substitui o destrutor virtual da classe base

private slots:
    void iniciarJogo();                   // Slot para iniciar o jogo ao clicar no botão
    void digitoPressionado();             // Slot chamado ao pressionar um botão numérico
    void limparPressionado();             // Slot chamado ao pressionar o botão “C” (limpar)
    void enviarPressionado();             // Slot chamado ao pressionar o botão “ENTER”
    void atualizarTempo();                // Slot acionado a cada tick do QTimer
    void resetJogoUI();                   // Slot para resetar a interface e voltar ao menu

private:
    // Widgets de configuração
    QButtonGroup* grupoDificuldade;    // Agrupa os radio buttons de dificuldade para seleção única
    QRadioButton* rbFacil;             // Radio button Fácil
    QRadioButton* rbMedio;             // Radio button Médio
    QRadioButton* rbDificil;           // Radio button Difícil
    QSpinBox* spinTempo;               // SpinBox para definir o tempo limite em segundos
    QPushButton* botaoIniciar;         // Botão INICIAR JOGO

    // Área de palpites (“_”)
    QHBoxLayout* layoutPalpites;        // Layout horizontal para exibir os labels de palpite
    QVector<QLabel*> labelsPalpites;    // Vetor de QLabel usados para mostrar cada posição do palpite
    QLabel* labelMensagem;              // Label para exibir mensagens e feedback de acertos
    QLabel* labelTentativas;            // Label que mostra o número de tentativas feitas
    QLabel* labelTempo;                 // Label que exibe o tempo restante

    // Teclado numérico
    QVector<QPushButton*> botoesNumericos;  // Vetor que armazena os botões 1–9 e 0
    QPushButton* botaoLimpar;               // Botão “C” para apagar o último dígito
    QPushButton* botaoEnviar;               // Botão “ENTER” para submeter o palpite

    // Lógica de jogo
    std::unique_ptr<Senha> senha;           // Ponteiro polimórfico para a senha gerada
    QTimer* temporizador;                   // Timer para controlar o cronômetro de jogo
    int tentativas;                         // Contador de tentativas realizadas
    int segundosRestantes;                  // Segundos restantes no cronômetro
};

#endif // MAINWINDOW_H
