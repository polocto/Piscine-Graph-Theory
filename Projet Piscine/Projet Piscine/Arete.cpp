#include "Arete.h"
#include "Sommet.h"


Arete::Arete(Sommet* s1, Sommet* s2)
    :m_suivant(s1),m_precedent(s2)
{
    m_suivant->ajoutP(this);
    m_precedent->ajoutS(this);
}
