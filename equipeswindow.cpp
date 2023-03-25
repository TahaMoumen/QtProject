#include "equipeswindow.h"
#include "equipes.h"

EquipesWindow::EquipesWindow(QWidget *parent) : QMainWindow(parent)
{
    listWidget = new QListWidget(this);
    setCentralWidget(listWidget);

    QVector<Equipe> equipes = listeEquipes();
    for (const Equipe &equipe : equipes)
    {
        listWidget->addItem(equipe.nom + " - " + equipe.ville);
    }
}