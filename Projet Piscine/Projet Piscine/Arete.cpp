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
        std::cout <<tampon;
        if (iss.fail())
            throw("probleme dans la lecture de la ligne du fichier: fichier corompu");
        m_poids=tampon;
}

void Arete::affichageconsole()const
{
    std::cout<<m_ext1->getnom()<<" "<<m_ext2->getnom()<<" "<<m_poids;
}

void Arete::affichage(Svgfile& svgout)
{
    svgout.addLine(m_ext1->getx(),m_ext1->getY(),m_ext2->getx(),m_ext2->getY());
}
