#ifndef STADES_H
#define STADES_H

#include <QString>
#include <QVector>

struct Stade{
    QString nom;
    QString ville;
};

void ajouterStade(const Stade &stade);
void supprimerStade(const QString &nom);
QVector<Stade> listeStades();

#endif