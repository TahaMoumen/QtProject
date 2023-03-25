#include "equipes.h"

QVector<Equipe> equipes;

void ajouterEquipe(const Equipe &equipe){
    equipes.append(equipe);
}

void supprimerEquipe(const QString &nom){
    for (int i = 0; i < equipes.size(); ++i){
        if (equipes[i].nom == nom){
            equipes.remove(i);
            break;
        }
    }
}

QVector<Equipe> listeEquipes(){
    return equipes;
}