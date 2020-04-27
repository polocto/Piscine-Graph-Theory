#include "Sommet.h"
#include "Arete.h"

/**constructeur
initialisation de données non passé en paramètre à 0
*/
Sommet::Sommet(const std::string&nom, const double& pos_x, const double& pos_y)
    :m_nom(nom),m_i_d(0),m_i_vp(1),m_i_p(0),m_x(pos_x),m_y(pos_y)
{
}

/**ajout d'une arete suivante*/
void Sommet::ajout(Arete*suivant)
{
    m_suivants.push_back(suivant);
}

/**Affichage console*/
void Sommet::affichageconsole()const
{
    std::cout<<m_nom<<" "<<m_x<<" "<<m_y<<" icd: "<<m_i_d<<" ivp: "<<m_i_vp;
}
/**Affichage SVG*/
void Sommet::affichage(Svgfile& svgout)
{
    svgout.addDisk(m_x*100,m_y*100,10,"BLACK");//Affichage sommet
    svgout.addText(m_x*100-1,m_y*100-20,m_nom,"BLUE");//Affichage nom sommet
}

/**GETTER*/

/**retourn la position x du sommet*/
double Sommet::getx()const
{
    return m_x;
}

/**retourn la position y du sommet*/
double Sommet::getY()const
{
    return m_y;
}

double Sommet::get_vp()const
{
    return m_i_vp;
}

/**retourn le nom du sommet*/
std::string Sommet:: getnom()const
{
    return m_nom;
}

/** Calcule icd indice de centralité de degré*/
void Sommet::calc_icd()
{
    m_i_d=m_suivants.size();
}
/**Calcul somme des indice de vecteur propre des voisins*/
void Sommet::calc_vp(std::map<Sommet*,double>&somme)
{
    somme[this]=0;//initialisation à 0
    for(Arete* a : m_suivants)
        somme.at(this)+=a->get_vp(this);//somme des vecteur propre des sommet voisins

}
/**mise à jour du de l'indice de vecteur propre*/
void Sommet::indice_vp(std::map<Sommet*,double>&somme,const double& lambda)
{
    m_i_vp=somme.at(this)/lambda;//somme des vecteur propre des sommet voisins divisé par lambda
}
