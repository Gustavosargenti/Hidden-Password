#include "mainwindow.h"
#include "SenhaFacil.h"
#include "SenhaMedia.h"
#include "SenhaDificil.h"

#include <QMessageBox>                            // Para caixas de diálogo informativas
#include <QApplication>                           // Para encerrar a aplicação (quit)
#include <QVBoxLayout>                            // Layout vertical
#include <QHBoxLayout>                            // Layout horizontal
#include <QGridLayout>                            // Layout em grade
#include <QGroupBox>                              // Caixa com título para agrupar widgets
#include <QRadioButton>                           // Botões de opção (dificuldade)
#include <QSpinBox>                               // SpinBox para definir tempo
#include <QPushButton>                            // Botões clicáveis
#include <QLabel>                                 // Para exibir texto
#include <QFont>                                  // Para configurar fontes
#include <QGraphicsDropShadowEffect>              // Para aplicar sombra a widgets

// Restaura a interface de volta ao menu de configuração
void MainWindow::resetJogoUI() {
    temporizador->stop();                        // Para o cronômetro

    labelMensagem->hide();                       // Esconde a mensagem de feedback
    labelTentativas->hide();                     // Esconde o contador de tentativas
    labelTempo->hide();                          // Esconde o contador de tempo
    botaoLimpar->hide();                         // Esconde o botão “C” (limpar)
    botaoEnviar->hide();                         // Esconde o botão ENTER
    for (auto *b : botoesNumericos)              // Para cada botão numérico
        b->hide();                               // esconde

    qDeleteAll(labelsPalpites);                  // Deleta todos os labels “_”
    labelsPalpites.clear();                      // Limpa o vetor de labels
    layoutPalpites->setEnabled(false);           // Desativa o layout de palpites

    rbFacil->setEnabled(true);                   // Reativa o rádio Fácil
    rbMedio->setEnabled(true);                   // Reativa o rádio Médio
    rbDificil->setEnabled(true);                 // Reativa o rádio Difícil
    spinTempo->setEnabled(true);                 // Reativa o SpinBox de tempo
    botaoIniciar->setEnabled(true);              // Reativa o botão INICIAR JOGO
}

//Cria N labels “_” para representar espaços de palpite
static QVector<QLabel*> criarEspacos(int n) {
    QVector<QLabel*> v;                          // Vetor para armazenar os labels
    QFont f;                                     // Objeto de fonte
    f.setPointSize(48);                          // Define tamanho da fonte
    f.setBold(true);                             // Define fonte negrito
    for (int i = 0; i < n; ++i) {                // Loop de 0 até n-1
        auto *lbl = new QLabel("_");             // Cria um QLabel com texto “_”
        lbl->setFont(f);                         // Aplica a fonte configurada
        lbl->setStyleSheet("color:#555;");       // Define cor cinza
        lbl->setFixedSize(80,80);                // Define tamanho fixo
        lbl->setAlignment(Qt::AlignCenter);      // Centraliza o texto no label
        v.append(lbl);                           // Adiciona ao vetor
    }
    return v;                                    // Retorna o vetor de labels
}

// Construtor de MainWindow — monta toda a interface
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),                       // Chama o construtor da classe base
    temporizador(new QTimer(this)),            // Cria o timer para o cronômetro
    tentativas(0),                             // Inicializa contador de tentativas
    segundosRestantes(0)                       // Inicializa segundos restantes
{
    // Tema escuro
    auto *central = new QWidget;                            // Widget central
    setCentralWidget(central);                              // Define widget central
    central->setStyleSheet("background-color:#2e2e2e;");    // Aplica cor de fundo escura
    auto *vMain = new QVBoxLayout(central);                 // Layout vertical principal

    // Caixa de Configuração
    auto *cfgBox = new QGroupBox("Configuração");                  // GroupBox com título
    cfgBox->setStyleSheet("QGroupBox{color:#eee;font:bold 20px; margin-top:16px;}"); // Estilo
    auto *cfgLayout = new QVBoxLayout(cfgBox);                     // Layout vertical interno
    cfgLayout->setSpacing(20);                                      // Espaçamento entre itens
    cfgLayout->setContentsMargins(20,40,20,20);                     // Margens internas

    // Rádios de dificuldade
    rbFacil   = new QRadioButton("FÁCIL (3 dígitos)");                  // Opção Fácil
    rbMedio   = new QRadioButton("MÉDIO (4 dígitos)");                  // Opção Médio
    rbDificil = new QRadioButton("DIFÍCIL (4 dígitos + embaralha)");    // Opção Difícil

    QFont fonteRadio; fonteRadio.setPointSize(18); fonteRadio.setBold(true);    // Fonte para rádios
    for (auto *rb : {rbFacil, rbMedio, rbDificil}) {                            // Para cada rádio
        rb->setFont(fonteRadio);                                                // aplica fonte
        rb->setMinimumSize(150,40);                                             // tamanho mínimo
        rb->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);   // política de expansão
        rb->setStyleSheet(R"(
            QRadioButton { spacing:12px; color:#ddd; }
            QRadioButton::indicator { width:24px; height:24px; }
            QRadioButton::indicator:checked {
               background:#ffb86c; border:2px solid #ffb86c; border-radius:12px;
            }
            QRadioButton::indicator:unchecked {
               border:2px solid #888; background:none; border-radius:12px;
            }
        )");                                                       // Estilo do indicador
    }
    rbFacil->setChecked(true);                                      // Seleciona Fácil por padrão

    // Agrupa rádios para seleção única
    grupoDificuldade = new QButtonGroup(this);                      // Cria QButtonGroup
    grupoDificuldade->addButton(rbFacil,1);                         // ID 1 = Fácil
    grupoDificuldade->addButton(rbMedio,2);                         // ID 2 = Médio
    grupoDificuldade->addButton(rbDificil,3);                       // ID 3 = Difícil

    // Layout horizontal dos controles de dificuldade
    auto *hcfg = new QHBoxLayout;                                   // Layout horizontal
    hcfg->setSpacing(16);                                           // Espaçamento
    hcfg->addWidget(rbFacil);                                       // Adiciona rádio Fácil
    hcfg->addWidget(rbMedio);                                       // Adiciona rádio Médio
    hcfg->addWidget(rbDificil);                                     // Adiciona rádio Difícil

    // SpinBox de tempo
    spinTempo = new QSpinBox;                                       // Cria SpinBox
    spinTempo->setRange(0,300);                                     // Define de 0 a 300
    spinTempo->setSuffix(" s");                                     // Sufixo s
    spinTempo->setStyleSheet(R"(QSpinBox{ background:#1e1e2e;color:#eee;border:1px solid #444;border-radius:4px;padding:2px 6px;})");                                                            // Estilo SpinBox
    auto *lblTempo = new QLabel("TEMPO:");                          // Label “TEMPO:”
    lblTempo->setStyleSheet("color:#ddd;font-size:16px;");          // Estilo do label
    hcfg->addWidget(lblTempo);                                      // Adiciona ao layout
    hcfg->addWidget(spinTempo);                                     // Adiciona SpinBox

    // Botão “INICIAR JOGO”
    botaoIniciar = new QPushButton("INICIAR JOGO");                  // Cria botão
    botaoIniciar->setFixedHeight(50);                                // Altura fixa
    botaoIniciar->setStyleSheet(R"(
      QPushButton { background:#444;color:#fff;border-radius:8px;padding:8px 16px;font-size:18px; }
      QPushButton:pressed { background:#555; }
    )");                                                            // Estilo botão
    hcfg->addWidget(botaoIniciar);                                  // Adiciona ao layout horizontal

    cfgLayout->addLayout(hcfg);                                     // Insere hcfg no cfgBox
    vMain->addWidget(cfgBox);                                       // Adiciona cfgBox ao layout principal

    // Área de Palpites (“_”)
    layoutPalpites = new QHBoxLayout;                               // Layout horizontal
    layoutPalpites->setSpacing(16);                                 // Espaçamento
    vMain->addLayout(layoutPalpites);                               // Adiciona ao layout principal

    // Label de Mensagens
    labelMensagem = new QLabel;                                     // Cria label vazia
    labelMensagem->setStyleSheet("color:#ccc;font-size:20px;");     // Estilo texto
    labelMensagem->setAlignment(Qt::AlignCenter);                   // Centraliza
    vMain->addWidget(labelMensagem);                                // Adiciona

    // Label de Tentativas
    labelTentativas = new QLabel("TENTATIVAS: 0");                  // Inicializa com zero
    labelTentativas->setStyleSheet("color:#bbb;font-size:18px;");   // Estilo
    labelTentativas->setAlignment(Qt::AlignCenter);                 // Centraliza
    vMain->addWidget(labelTentativas);                              // Adiciona

    // Label de Tempo
    labelTempo = new QLabel("TEMPO: --");                           // Inicializa sem limite
    labelTempo->setStyleSheet("color:#bbb;font-size:18px;");        // Estilo
    labelTempo->setAlignment(Qt::AlignCenter);                      // Centraliza
    vMain->addWidget(labelTempo);                                   // Adiciona

    // Teclado Numérico
    auto *grid = new QGridLayout;                                       // Layout em grade
    QFont fonteBtn; fonteBtn.setPointSize(36); fonteBtn.setBold(true);  // Fonte botões
    const QString estBtn = R"(
      QPushButton { background:#333;color:#fff;border:3px solid #888;border-radius:16px; }
      QPushButton:hover { background:#444; }
      QPushButton:pressed { background:#555; }
      QPushButton:disabled { background:#222;color:#555; }
    )";                                                             // Estilo botões
    for (int i=1; i<=9; ++i) {                                      // Botões 1 a 9
        auto *b = new QPushButton(QString::number(i));              // Cria botão com número
        b->setFixedSize(200,100);                                   // Tamanho fixo
        b->setFont(fonteBtn);                                       // Aplica fonte
        b->setStyleSheet(estBtn);                                   // Aplica estilo
        auto *s = new QGraphicsDropShadowEffect(b);                 // Sombra
        s->setBlurRadius(20); s->setOffset(0,0); s->setColor(QColor(0,0,0,160));
        b->setGraphicsEffect(s);                                    // Adiciona sombra
        botoesNumericos.append(b);                                  // Guarda no vetor
        grid->addWidget(b,(i-1)/3,(i-1)%3);                         // Posiciona na grade
        connect(b,&QPushButton::clicked,this,&MainWindow::digitoPressionado); // Conecta slot
    }

    // Botão C (Limpar)
    botaoLimpar = new QPushButton("C");
    botaoLimpar->setFixedSize(200,100);
    botaoLimpar->setFont(fonteBtn);
    botaoLimpar->setStyleSheet(estBtn);
    {
        auto *s = new QGraphicsDropShadowEffect(botaoLimpar);
        s->setBlurRadius(20); s->setOffset(0,0); s->setColor(QColor(0,0,0,160));
        botaoLimpar->setGraphicsEffect(s);
    }
    grid->addWidget(botaoLimpar,3,0);                             // Posição (3,0)
    connect(botaoLimpar,&QPushButton::clicked,this,&MainWindow::limparPressionado);

    // Botão 0
    auto *b0 = new QPushButton("0");
    b0->setFixedSize(200,100);
    b0->setFont(fonteBtn);
    b0->setStyleSheet(estBtn);
    {
        auto *s = new QGraphicsDropShadowEffect(b0);
        s->setBlurRadius(20); s->setOffset(0,0); s->setColor(QColor(0,0,0,160));
        b0->setGraphicsEffect(s);
    }
    botoesNumericos.append(b0);
    grid->addWidget(b0,3,1);                                      // Posição (3,1)
    connect(b0,&QPushButton::clicked,this,&MainWindow::digitoPressionado);

    // Botão ENTER
    botaoEnviar = new QPushButton("ENTER");
    botaoEnviar->setFixedSize(200,100);
    botaoEnviar->setFont(fonteBtn);
    botaoEnviar->setStyleSheet(estBtn);
    {
        auto *s = new QGraphicsDropShadowEffect(botaoEnviar);
        s->setBlurRadius(20); s->setOffset(0,0); s->setColor(QColor(0,0,0,160));
        botaoEnviar->setGraphicsEffect(s);
    }
    grid->addWidget(botaoEnviar,3,2);                             // Posição (3,2)
    connect(botaoEnviar,&QPushButton::clicked,this,&MainWindow::enviarPressionado);

    vMain->addLayout(grid);                                       // Adiciona grade ao layout

    // Esconde tudo até iniciar
    {
        QWidget* es[] = { labelMensagem,labelTentativas,labelTempo,botaoLimpar,botaoEnviar };
        for (auto *w : es) w->hide();                              // Esconde labels e botões
        for (auto *b : botoesNumericos) b->hide();                 // Esconde botões 0–9
        layoutPalpites->setEnabled(false);                         // Desativa layout de palpites
    }

    // Conexões finais
    connect(botaoIniciar,&QPushButton::clicked,this,&MainWindow::iniciarJogo);    // Inicia jogo
    connect(temporizador,&QTimer::timeout,this,&MainWindow::atualizarTempo);      // Tick do timer

    setWindowTitle("Jogo da Senha (Dark Mode)");                           // Título da janela
    resize(700,900);                                                       // Tamanho inicial
}

// Destrutor padrão
MainWindow::~MainWindow() = default;

// inicia o jogo após clicar em “INICIAR JOGO”
void MainWindow::iniciarJogo() {
    if (rbFacil->isChecked())                                                    // Se Fácil marcado
        senha = std::make_unique<SenhaFacil>();                                  // Cria SenhaFacil
    else if (rbMedio->isChecked())                                               // Se Médio marcado
        senha = std::make_unique<SenhaMedia>();                                  // Cria SenhaMedia
    else                                                                         // Caso contrário (Difícil)
        senha = std::make_unique<SenhaDificil>();                                // Cria SenhaDificil
    senha->gerar();                                                              // Gera os dígitos

    qDeleteAll(labelsPalpites);                                                  // Deleta espaços antigos
    labelsPalpites = criarEspacos(senha->getTamanho());                          // Cria novos espaços
    for (auto *lbl : labelsPalpites) {                                           // Para cada label
        layoutPalpites->addWidget(lbl);                                          //   adiciona ao layout
        lbl->show();                                                             //   exibe-o
    }
    layoutPalpites->setEnabled(true);                                            // Ativa layout

    tentativas = 0;                                                              // Zera contador
    labelTentativas->setText("TENTATIVAS: 0");                                   // Atualiza label
    labelMensagem->clear();                                                      // Limpa mensagem

    segundosRestantes = spinTempo->value();                                      // Lê tempo do SpinBox
    if (segundosRestantes > 0) {
        temporizador->start(1000);                                               // Inicia timer 1s
        labelTempo->setText(QString("TEMPO: %1").arg(segundosRestantes));        // Exibe tempo
    } else {
        labelTempo->setText("TEMPO: ∞");                                         // Sem limite
    }

    QWidget* ms[] = { labelMensagem,labelTentativas,labelTempo,botaoLimpar,botaoEnviar };
    for (auto *w : ms) w->show();                                                // Exibe controles
    for (auto *b : botoesNumericos) b->show();                                   // Exibe botões 0–9
}

// Insere o dígito do botão no primeiro “_” vazio
void MainWindow::digitoPressionado() {
    auto *b = qobject_cast<QPushButton*>(sender()); // Identifica o botão clicado
    if (!b) return;                                 // Se nulo, sai
    for (auto *lbl : labelsPalpites) {              // Para cada label de palpite
        if (lbl->text() == "_") {                   // No primeiro vazio
            lbl->setText(b->text());                // Coloca o texto do botão
            lbl->setStyleSheet("color:#e0e0e0;");   // Ajusta cor do texto
            break;                                  // Sai do loop
        }
    }
}

// Apaga o último dígito preenchido
void MainWindow::limparPressionado() {
    for (int i = labelsPalpites.size() - 1; i >= 0; --i) {      // De trás para frente
        if (labelsPalpites[i]->text() != "_") {                 // No primeiro não vazio
            labelsPalpites[i]->setText("_");                    // Volta a “_”
            labelsPalpites[i]->setStyleSheet("color:#555;");    // Cor cinza
            break;                                              // Sai do loop
        }
    }
}

// Verifica o palpite, trata acerto ou shuffle no difícil
void MainWindow::enviarPressionado() {
    std::vector<int> pal;                                   // Vetor para armazenar palpite
    for (auto *lbl : labelsPalpites) {                      // Para cada label de palpite
        QString t = lbl->text();                            // Lê o texto
        if (t == "_") {                                     // Se incompleto
            labelMensagem->setText("COMPLETE O PALPITE!");  // Exibe aviso
            return;                                         // Sai
        }
        pal.push_back(t.toInt());                           // Converte em int e adiciona
    }

    tentativas++;                                           // Incrementa contador
    labelTentativas->setText(QString("TENTATIVAS: %1").arg(tentativas)); // Atualiza label

    int corretos = senha->verificarPosicao(pal);        // Conta acertos na posição
    if (corretos == senha->getTamanho()) {              // Se acertou todos
        temporizador->stop();                           // Para timer

        QMessageBox msg(this);                          // Cria caixa de diálogo
        msg.setWindowTitle("Você Ganhou!");             // Título
        msg.setText(QString("Acertou em %1 tentativas!").arg(tentativas)); // Texto
        QPushButton *btnMenu = msg.addButton("Voltar ao Menu", QMessageBox::AcceptRole);
        QPushButton *btnSair = msg.addButton("Sair do Jogo",   QMessageBox::RejectRole);
        msg.exec();                                      // Exibe diálogo
        if (msg.clickedButton() == btnMenu)              // Se “Voltar ao Menu”
            resetJogoUI();                               // reseta UI
        else                                             // Senão
            QApplication::quit();                        // fecha app
        return;                                          // Sai
    }

    // Se não acertou tudo, exibe feedback parcial
    labelMensagem->setText(QString("%1 NÚMERO(S) CORRETOS").arg(corretos));

    // No modo difícil, a cada 15 tentativas embaralha a senha
    if (grupoDificuldade->checkedId() == 3 && tentativas % 15 == 0) {
        auto *sd = static_cast<SenhaDificil*>(senha.get());                     // Cast seguro
        sd->embaralharSenha();                                                  // Embaralha dígitos
        labelMensagem->setText(labelMensagem->text() + "\nSENHA EMBARALHADA!"); // Aviso
    }

    // Limpa todos os espaços para próxima tentativa
    for (auto *lbl : labelsPalpites) {
        lbl->setText("_");                                 // Volta a “_”
        lbl->setStyleSheet("color:#555;");                 // Cor cinza
    }
}

// Chamado a cada segundo para atualizar o cronômetro
void MainWindow::atualizarTempo() {
    if (--segundosRestantes <= 0) {                        // Decrementa e checa fim
        temporizador->stop();                              // Para timer

        QMessageBox msg(this);                             // Caixa de fim por tempo
        msg.setWindowTitle("Tempo Esgotado");
        msg.setText(QString("Tempo esgotado! Tentativas: %1").arg(tentativas));
        QPushButton *btnMenu = msg.addButton("Voltar ao Menu", QMessageBox::AcceptRole);
        msg.exec();                                        // Exibe
        if (msg.clickedButton() == btnMenu)                // Se voltar ao menu
            resetJogoUI();                                 // reseta UI
        else                                               // Senão
            QApplication::quit();                          // fecha app
    } else {
        labelTempo->setText(QString("TEMPO: %1").arg(segundosRestantes)); // Atualiza label
    }
}
