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
        iss>>m_poids;

        if (iss.fail())
            throw("probleme dans la lecture de la ligne du fichier: fichier corompu");
}

void Arete::affichageconsole()const
{
    std::cout<<m_ext1->getnom()<<" "<<m_ext2->getnom()<<" "<<m_poids;
}

void Arete::affichage(Svgfile& svgout)
{
    svgout.addLine(m_ext1->getx()*100,m_ext1->getY()*100,m_ext2->getx()*100,m_ext2->getY()*100,"BLACK");
}
