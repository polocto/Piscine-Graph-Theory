#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"

Arete::Arete(Sommet* s1, Sommet* s2)
    :m_ext1(s1),m_ext2(s2)
{
    m_ext1->ajout(this);
    m_ext2->ajout(this);
}

void Arete::ponderation(std::stringstream& iss)
{
        double tampon;
        iss>>tampon;

        if (iss.fail())
            throw("probleme dans la lecture de la ligne du fichier: fichier corompu");
        m_poids=tampon;
}

void Arete::affichageconsole()const
{
    std::cout<<m_ext1<<" "<<m_ext2<<" "<<m_poids;
}

void Arete::affichage(Svgfile& svgout)
{
    svgout.addLine(m_precedent->getx(),m_precedent->getY(),m_suivant->getx(),m_suivant->getY());
}
