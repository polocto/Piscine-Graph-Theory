#include "Arete.h"
#include "Sommet.h"


Arete::Arete(Sommet* s1, Sommet* s2)
    :m_ext1(s1),m_ext2(s2)
{
    m_ext1->ajout(this);
    m_ext2->ajout(this);
}
