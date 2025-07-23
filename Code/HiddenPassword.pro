QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Contagem.cpp \
    Dificuldade.cpp \
    Jogador.cpp \
    Jogosenha.cpp \
    Senha.cpp \
    SenhaDificil.cpp \
    SenhaFacil.cpp \
    SenhaMedia.cpp \
    main.cpp \
    mainwindow.cpp \
    widget.cpp

HEADERS += \
    Contagem.h \
    Dificuldade.h \
    Jogador.h \
    Jogosenha.h \
    Senha.h \
    SenhaDificil.h \
    SenhaFacil.h \
    SenhaMedia.h \
    mainwindow.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
