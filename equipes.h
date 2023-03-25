#ifndef EQUIPES_H
#define EQUIPES_H

#include <QString>
#include <QVector>

struct Equipe{
    QString nom;
    QString ville;
};

void ajouterEquipe(const Equipe &equipe);
void supprimerEquipe(const QString &nom);
QVector<Equipe> listeEquipes();

#endif