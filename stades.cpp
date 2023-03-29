#include "stades.h"

QVector<Stade> stades;

void ajouterStade(const Stade &stade){
    stades.append(stade);
}

void supprimerStade(const QString &nom){
    for (int i = 0; i < stades.size(); ++i){
        if (stades[i].nom == nom){
            stades.remove(i);
            break;
        }
    }
}

QVector<Stade> listeStades(){
    return stades;
}