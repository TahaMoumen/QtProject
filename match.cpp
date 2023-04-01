#include "match.h"

QVector<Match> genererPlanning(QVector<Equipe> equipes) {
    QVector<Match> planning;
    for (int i = 0; i < equipes.size(); i++) {
        for (int j = i + 1; j < equipes.size(); j++) {
            Match matchAller;
            matchAller.equipe1 = equipes[i].nom;
            matchAller.equipe2 = equipes[j].nom;
            matchAller.date = QDate::currentDate().addDays(qrand() % 30);
            planning.append(matchAller);

            Match matchRetour;
            matchRetour.equipe1 = equipes[j].nom;
            matchRetour.equipe2 = equipes[i].nom;
            matchRetour.date = QDate::currentDate().addDays(qrand() % 30);
            planning.append(matchRetour);
        }
    }
    return planning;
}