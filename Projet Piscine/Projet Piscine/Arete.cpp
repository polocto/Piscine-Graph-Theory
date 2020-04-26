#include "Arete.h"
#include "Sommet.h"


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
