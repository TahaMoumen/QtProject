#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include <QGridLayout>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCalendarWidget>
#include <QPushButton>
#include <QObject>
#include <QVector>
#include <QListWidget>
#include <QMessageBox>
#include "equipes.h"
#include "match.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget fenetre;

    QTableWidget *tablEquipes = new QTableWidget(0, 3, &fenetre);
    tablEquipes->setHorizontalHeaderLabels({"Nom", "Ville","Stade"}); 
    tablEquipes->setParent(&fenetre);

    QMenuBar *menuBar = new QMenuBar(&fenetre);
    QMenu *menuAjout = menuBar->addMenu("Ajout");

    QAction *ajoutEquipesAction = new QAction("Equipes", &fenetre);
    menuAjout->addAction(ajoutEquipesAction);

    QMenu *menuPlanning = menuBar->addMenu("Planning");
    QAction *planningAction = new QAction("Matchs", &fenetre);
    menuPlanning->addAction(planningAction);

    QMenu *menuScore = menuBar->addMenu("Score");
    QAction *scoreAleatoireAction = new QAction("Aleatoire", &fenetre);
    menuScore->addAction(scoreAleatoireAction);

    QMenu *menuClassement = menuBar->addMenu("Classement");
    QAction *classementAction = new QAction("Affichage", &fenetre);
    menuClassement->addAction(classementAction);

    QObject::connect(ajoutEquipesAction, &QAction::triggered, [&fenetre, tablEquipes]() {
        int numTeams = 0;
        bool ok;
        QString nom = QInputDialog::getText(&fenetre, "Ajouter une équipe", "Nom de l'équipe:", QLineEdit::Normal, "", &ok);
        if (ok && !nom.isEmpty()){
            QString ville = QInputDialog::getText(&fenetre, "Ajouter une équipe", "Ville de l'équipe:", QLineEdit::Normal, "", &ok);
            if (ok && !ville.isEmpty()){
                QString stade = QInputDialog::getText(&fenetre, "Ajouter un stade", "Stade de l'équipe:", QLineEdit::Normal, "", &ok);
                if (ok && !stade.isEmpty()){
                    Equipe equipe;
                    equipe.nom = nom;
                    equipe.ville = ville;
                    equipe.stade = stade;
                    ajouterEquipe(equipe);
                    int row = tablEquipes->rowCount();
                    tablEquipes->insertRow(row);
                    tablEquipes->setItem(row, 0, new QTableWidgetItem(nom));
                    tablEquipes->setItem(row, 1, new QTableWidgetItem(ville));
                    tablEquipes->setItem(row,2, new QTableWidgetItem(stade));
                }
            }
        }
    });

    QObject::connect(planningAction, &QAction::triggered, [&fenetre]() {
        QVector<Equipe> equipes = listeEquipes();
        if (equipes.size() < 4) {
            QMessageBox::warning(&fenetre, "Erreur", "Il faut au moins 4 équipes pour générer un planning.");
        } else {
            QVector<Match> planning = genererPlanning(equipes);
            QTableWidget *tableauMatchs = new QTableWidget(planning.size(), 3, &fenetre);
            tableauMatchs->setHorizontalHeaderLabels({"Équipe 1", "Équipe 2", "Date"});
            for (int i = 0; i < planning.size(); i++) {
                const Match &match = planning[i];
                tableauMatchs->setItem(i, 0, new QTableWidgetItem(match.equipe1));
                tableauMatchs->setItem(i, 1, new QTableWidgetItem(match.equipe2));
                tableauMatchs->setItem(i, 2, new QTableWidgetItem(match.date.toString("dd/MM/yyyy")));
            }
            tableauMatchs->resize(600, 250);
            tableauMatchs->move(600, fenetre.height() - 250);
            tableauMatchs->show();
        }
    });

    fenetre.resize(1800, 1000);
    tablEquipes->resize(600, 250);
    tablEquipes->move(0, fenetre.height() - 250);

    fenetre.show();
    return app.exec();
}

