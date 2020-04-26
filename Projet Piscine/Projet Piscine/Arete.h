#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "biblio.h"
class Sommet;

class Arete
{
public:
    Arete(Sommet* s1, Sommet* s2);
    ~Arete() = default;
private:
    Sommet* m_suivant,* m_precedent;
    double m_poids;
};

#endif
