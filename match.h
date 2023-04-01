#ifndef MATCH_H
#define MATCH_H
#include <QDate>
#include <QString>
#include <QVector>
#include "equipes.h"

struct Match {
    QString equipe1;
    QString equipe2;
    QDate date;
};

QVector<Match> genererPlanning(QVector<Equipe> equipes);

#endif