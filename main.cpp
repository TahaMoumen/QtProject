#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QDebug>
#include <QInputDialog>
#include "equipes.h"
#include "equipeswindow.h"
#include "stades.h"
#include "stadeswindow.h"


int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QWidget fenetre;

    QMenuBar *menuBar = new QMenuBar(&fenetre);

    QMenu *menuAjout = menuBar->addMenu("Ajout");
    QAction *ajoutEquipesAction = new QAction("Equipes", &fenetre);
    QAction *afficherEquipesAction = new QAction("Afficher Equipes", &fenetre);
    QAction *ajoutStadesAction = new QAction("Stades", &fenetre);
    QAction *afficherStadesAction = new QAction("Afficher Stades", &fenetre);
    menuAjout->addAction(ajoutEquipesAction);
    menuAjout->addAction(ajoutStadesAction);
    menuAjout->addAction(afficherEquipesAction);
    menuAjout->addAction(afficherStadesAction);

    QMenu *menuPlanning = menuBar->addMenu("Planning");
    QAction *planningAction = new QAction("Matchs", &fenetre);
    menuPlanning->addAction(planningAction);

    QMenu *menuScore = menuBar->addMenu("Score");
    QAction *scoreAleatoireAction = new QAction("Aleatoire", &fenetre);
    menuScore->addAction(scoreAleatoireAction);
    
    QMenu *menuClassement = menuBar->addMenu("Classement");
    QAction *classementAction = new QAction("Affichage", &fenetre);
    menuClassement->addAction(classementAction);

    QObject::connect(ajoutEquipesAction, &QAction::triggered, [&fenetre]() {
        bool ok;
        QString nom = QInputDialog::getText(&fenetre, "Ajouter une équipe", "Nom de l'équipe:", QLineEdit::Normal, "", &ok);
        if (ok && !nom.isEmpty()){
            QString ville = QInputDialog::getText(&fenetre, "Ajouter une équipe", "Ville de l'équipe:", QLineEdit::Normal, "", &ok);
            if (ok && !ville.isEmpty()){
                Equipe equipe;
                equipe.nom = nom;
                equipe.ville = ville;
                ajouterEquipe(equipe);
            }
        }
    });

    QObject::connect(afficherEquipesAction, &QAction::triggered, [&fenetre]() {
        EquipesWindow *window = new EquipesWindow(&fenetre);
        window->show();
    });

    QObject::connect(ajoutStadesAction, &QAction::triggered, [&fenetre]() {
        bool ok;
        QString nom = QInputDialog::getText(&fenetre, "Ajouter un stade", "Nom du stade:", QLineEdit::Normal, "", &ok);
        if (ok && !nom.isEmpty()){
            QString ville = QInputDialog::getText(&fenetre, "Ajouter un stade", "Ville du stade:", QLineEdit::Normal, "", &ok);
            if (ok && !ville.isEmpty()){
                Stade stade;
                stade.nom = nom;
                stade.ville = ville;
                ajouterStade(stade);
            }
        }
    });

    QObject::connect(afficherStadesAction, &QAction::triggered, [&fenetre]() {
        StadesWindow *window = new StadesWindow(&fenetre);
        window->show();
    });

    fenetre.resize(300, 200);
    fenetre.show();

    return app.exec();
}