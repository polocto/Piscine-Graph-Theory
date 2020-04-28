#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"

///Constructeur de la class Arete
///Prend en parametre les adresses des deux extremit�e pour initialiser arrete et pour ajouter l'arrete a leur liste de suivant
///initialisation du poids a 1 cas d'un graph non ponder�
Arete::Arete(Sommet* s1, Sommet* s2)
    :m_ext1(s1),m_ext2(s2),m_poids(1)
{
    m_ext1->ajout(this);
    m_ext2->ajout(this);
}

Arete::Arete(Sommet* s1, Sommet* s2,double poids)
    :m_ext1(s1),m_ext2(s2),m_poids(poids)
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
void Arete::affichage(Svgfile& svgout)const
{
    svgout.addLine(m_ext1->getX()*100,m_ext1->getY()*100,m_ext2->getX()*100,m_ext2->getY()*100,"BLACK");
}

/**recupere l'indice de vecteur propre du voisin*/
double Arete::get_vp(Sommet*precedent)const
{
    if(precedent==m_ext1)
        return m_ext2->get_vp();
    return m_ext1->get_vp();
}

///getteur qui retourn le poids
double Arete::get_poid()const
{
    return m_poids;
}

///getteur qui renvoie l'adresse d'un sommet avec 1 arete et l'autre sommet
Sommet* Arete::getsuivant(Sommet* Som)const
{
    if (Som==m_ext1)
        return m_ext2;
    return m_ext1;
}
///Getteur d'une extremiter de l'arete
Sommet* Arete::getext1()
{
    return m_ext1;
}
Sommet*Arete::getext2()
{
    return m_ext2;

}

void Arete::k_connexe(int& nombre_chemin,std::map<const Arete*,bool>& arete,std::map<const Sommet*,bool>&sommet,const Sommet*arrive)const
{
    if(arete.count(this))
        return;
    arete[this]=true;
    if(!sommet.count(m_ext1))
        m_ext1->k_connexe(nombre_chemin,arete,sommet,arrive);
    else if(!sommet.count(m_ext2))
        m_ext2->k_connexe(nombre_chemin,arete,sommet,arrive);
}
