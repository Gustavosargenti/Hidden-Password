#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);       // Cria o objeto QApplication
    MainWindow janela;
    janela.show();                      // Exibe a janela principal na tela
    return app.exec();                  // Inicia o loop de eventos Qt
}
