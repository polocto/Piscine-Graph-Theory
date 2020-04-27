#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"

Arete::Arete(Sommet* s1, Sommet* s2)
    :m_suivant(s1),m_precedent(s2)
{

}

void Arete::affichage(Svgfile& svgout)
{
    svgout.addLine(m_precedent->getx(),m_precedent->getY(),m_suivant->getx(),m_suivant->getY());
}
