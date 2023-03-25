#include <QApplication>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget fenetre;

    QMenuBar *menuBar = new QMenuBar(&fenetre);

    QMenu *menuAjout = menuBar->addMenu("Ajout");
    QAction *ajoutEquipesAction = new QAction("Equipes", &fenetre);
    QAction *ajoutStadesAction = new QAction("Stades", &fenetre);
    menuAjout->addAction(ajoutEquipesAction);
    menuAjout->addAction(ajoutStadesAction);

    QMenu *menuPlanning = menuBar->addMenu("Planning");
    QAction *planningAction = new QAction("Matchs", &fenetre);
    menuPlanning->addAction(planningAction);

    QMenu *menuScore = menuBar->addMenu("Score");
    QAction *scoreAleatoireAction = new QAction("Aleatoire", &fenetre);
    menuScore->addAction(scoreAleatoireAction);

    QMenu *menuClassement = menuBar->addMenu("Classement");
    QAction *classementAction = new QAction("Affichage", &fenetre);
    menuClassement->addAction(classementAction);

    fenetre.show();

    return app.exec();
}
