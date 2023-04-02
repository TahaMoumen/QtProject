#include "match.h"

QVector<Match> genererPlanning(QVector<Equipe> equipes) {
    QVector<Match> planning;
    QDate dateDebut = QDate::currentDate();
    for (int i = 0; i < equipes.size(); i++) {
        for (int j = i + 1; j < equipes.size(); j++) {
            Match match;
            match.equipe1 = equipes[i].nom;
            match.equipe2 = equipes[j].nom;
            match.date = dateDebut;
            planning.append(match);
            dateDebut = dateDebut.addDays(1);
        }
    }
    return planning;
}