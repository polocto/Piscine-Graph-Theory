#include "Arete.h"
#include "Sommet.h"


Arete::Arete(Sommet* s1, Sommet* s2)
    :m_suivant(s1),m_precedent(s2)
{

}

void Arete::ponderation(std::stringstream& iss)
{
        double tampon;
        iss>>tampon;

        if (iss.fail())
            throw("probleme dans la lecture de la ligne du fichier: fichier corompu");
        m_poids=tampon;
}
