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
#include <QStackedWidget>
#include <QComboBox>
#include <QDebug>
#include <QMap>
#include "equipes.h"
#include "match.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget fenetre;

    //liste deroulante en haut a droite pour les matchs
    QComboBox *listeJours = new QComboBox(&fenetre);

    QVector<Match> planning;

    //table en bas a gauche pour les equipes 
    QTableWidget *tablEquipes = new QTableWidget(0, 4, &fenetre);
    tablEquipes->setHorizontalHeaderLabels({"Nom", "Ville","Stade","Points"}); 
    tablEquipes->setParent(&fenetre);

    ///Menu 
    QMenuBar *menuBar = new QMenuBar(&fenetre);
    QMenu *menuAjout = menuBar->addMenu("Ajout");

    QAction *ajoutEquipesAction = new QAction("Equipes", &fenetre);
    menuAjout->addAction(ajoutEquipesAction);

    QAction *ajout4EquipesAction = new QAction("Ajout 4 équipes", &fenetre);
    menuAjout->addAction(ajout4EquipesAction);

    QMenu *menuPlanning = menuBar->addMenu("Planning");
    QAction *planningAction = new QAction("Matchs", &fenetre);
    menuPlanning->addAction(planningAction);

    QMenu *menuClassement = menuBar->addMenu("Classement");
    QAction *classementAction = new QAction("Affichage", &fenetre);
    menuClassement->addAction(classementAction);

    //bouton pour ajouter 4 matchs comme ça c'est plus rapide pour faire le planning 
    QObject::connect(ajout4EquipesAction, &QAction::triggered, [&fenetre, tablEquipes]() {
        bool ok;
        for (int i = 0; i < 4; i++) {
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
            
        }
    });

    QObject::connect(ajoutEquipesAction, &QAction::triggered, [&fenetre, tablEquipes]() {
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

    QObject::connect(planningAction, &QAction::triggered, [&fenetre, &planning, &listeJours]() {
        QVector<Equipe> equipes = listeEquipes();
        if (equipes.size() < 4) {
            QMessageBox::warning(&fenetre, "Erreur", "Il faut au moins 4 équipes pour générer un planning.");
        } else {
            planning = genererPlanning(equipes);
            qDebug() << "Taille de planning:" << planning.size();
            for (const Match &match : planning) {
                qDebug() << "Date du match:" << match.date;
            }
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

            for (const Match &match : planning) {
                qDebug() << "Index de" << match.date.toString("dd/MM/yyyy") << "dans listeJours:" << listeJours->findText(match.date.toString("dd/MM/yyyy"));
                if (listeJours->findText(match.date.toString("dd/MM/yyyy")) == -1) {
                    listeJours->addItem(match.date.toString("dd/MM/yyyy"));
                }
                else{

                }
            }
        }
    });

    // pour avoir les detail du match du jour choisi
    QLabel *matchInfoLabel = new QLabel("Match du jour", &fenetre);
    QPushButton *randomScoreButton = new QPushButton("Score aléatoire", &fenetre);
    

    QObject::connect(listeJours, QOverload<int>::of(&QComboBox::currentIndexChanged), [listeJours, &planning, matchInfoLabel, &fenetre](int index) {
        QString selectedDate = listeJours->itemText(index);
        qDebug() << "Selected date:" << selectedDate;
        for (const Match &match : planning) {
            qDebug() << "Match date:" << match.date.toString("dd/MM/yyyy");
            if (match.date.toString("dd/MM/yyyy") == selectedDate) {
                matchInfoLabel->setText("Match du jour: " + match.equipe1 + " vs " + match.equipe2);
                break;
            }
        }
        fenetre.repaint(); 
    });


    // pour avoir le score aleatoire au match du jour
    QObject::connect(randomScoreButton, &QPushButton::clicked, [listeJours, &planning, matchInfoLabel, &fenetre]() {
        QString selectedDate = listeJours->currentText();
        qDebug() << "Selected date:" << selectedDate;
        for (Match &match : planning) {
            qDebug() << "Match date:" << match.date.toString("dd/MM/yyyy");
            if (match.date.toString("dd/MM/yyyy") == selectedDate) {
                match.score1 = rand() % 6;
                match.score2 = rand() % 6;
                qDebug() << "equipes:" << match.equipe1 << match.equipe2 << match.date << match.score1 << match.score2 ;
                matchInfoLabel->setText("Match du jour: " + match.equipe1 + " vs " + match.equipe2 + " (" + QString::number(match.score1) + " - " + QString::number(match.score2) + ")");
                break;
            }
        }
        //affiches les points avec qDebug
        QVector<Equipe> equipes = listeEquipes();
        for (Equipe &equipe : equipes) {
            qDebug() << "Nom d'équipe dans la liste 'equipes':" << equipe.nom;
            equipe.points = 0;
        }
        for (Match &match : planning) {
            qDebug() << "Noms d'équipes dans la liste 'planning':" << match.equipe1 << match.equipe2;
            if (match.score1 > match.score2) {
                for (Equipe &equipe : equipes) {
                    if (equipe.nom == match.equipe1) {
                        equipe.points += 3;
                    }
                }
            } else if (match.score1 < match.score2) {
                for (Equipe &equipe : equipes) {
                    if (equipe.nom == match.equipe2) {
                        equipe.points += 3;
                    }
                }
            } else {
                for (Equipe &equipe : equipes) {
                    if (equipe.nom == match.equipe1 || equipe.nom == match.equipe2) {
                        equipe.points += 1;
                    }
                }
            }
        }

        // afficher les points avec qDebug
        for (Equipe &equipe : equipes) {
            qDebug() << "equipe:" << equipe.nom << equipe.points;
        }
        fenetre.repaint(); 
    });



    


    // Positions
    matchInfoLabel->move(600, 300);
    randomScoreButton->move(600, 350);
    listeJours->move(1200,0);
    fenetre.resize(1800, 1000);
    tablEquipes->resize(600, 250);
    tablEquipes->move(0, fenetre.height() - 250);

    fenetre.show();
    return app.exec();
}

