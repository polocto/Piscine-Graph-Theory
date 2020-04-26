#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "biblio.h"
class Sommet;

class Arete
{
public:
    Arete(Sommet* s1, Sommet* s2);
    virtual ~Arete() = default;
private:
    Sommet* m_ext1,* m_ext2;
    double m_poids;
};

#endif
