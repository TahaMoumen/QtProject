#include "stadeswindow.h"
#include "stades.h"

StadesWindow::StadesWindow(QWidget *parent) : QMainWindow(parent){
    listWidget = new QListWidget(this);
    setCentralWidget(listWidget);

    QVector<Stade> stades = listeStades();
    for (const Stade &stade : stades){
        listWidget->addItem(stade.nom + " - " + stade.ville);
    }
}