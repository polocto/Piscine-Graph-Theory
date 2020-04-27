#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"

///Constructeur de la class Arete
///Prend en parametre les adresses des deux extremitée pour initialiser arrete et pour ajouter l'arrete a leur liste de suivant
///initialisation du poids a 1 cas d'un graph non ponderé
Arete::Arete(Sommet* s1, Sommet* s2)
    :m_ext1(s1),m_ext2(s2),m_poids(1)
{
    m_ext1->ajout(this);
    m_ext2->ajout(this);
}

///initialisation des ponderation apartir d'un flot de fichier
void Arete::ponderation(std::stringstream& iss)
{
    iss>>m_poids;

    if (iss.fail())
        throw("probleme dans la lecture de la ligne du fichier: fichier corompu");
}

///Affichage des informations lier a Arete dans la console
void Arete::affichageconsole()const
{
    std::cout<<m_ext1->getnom()<<" "<<m_ext2->getnom()<<" "<<m_poids;//utilisation de getteur pour acceder au nom des sommets
}

/// Affichage au format svg d'une Arete du graph
void Arete::affichage(Svgfile& svgout)
{
    svgout.addLine(m_ext1->getx()*100,m_ext1->getY()*100,m_ext2->getx()*100,m_ext2->getY()*100,"BLACK");
}

/**recupere l'indice de vecteur propre du voisin*/
double Arete::get_vp(Sommet*precedent)const
{
    if(precedent==m_ext1)
        return m_ext2->get_vp();
    return m_ext1->get_vp();
}
