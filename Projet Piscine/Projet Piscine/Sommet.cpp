#include "Sommet.h"
#include "Arete.h"

/**constructeur
initialisation de données non passé en paramètre à 0
*/
Sommet::Sommet(const std::string&nom, const double& pos_x, const double& pos_y)
    :m_nom(nom),m_i_d(0),m_i_vp(0),m_i_p(0),m_x(pos_x),m_y(pos_y)
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
    std::cout<<m_nom<<" "<<m_x<<" "<<m_y<<" icd: "<<m_i_d<< " icp "<<m_i_p;
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

void Sommet::calc_icp(double distance,double total)
{
    m_i_p=distance/total;
}

void Sommet::ajoutvoisin(std::vector<Sommet*>& Som,std::map<std::string,std::pair<bool,Sommet*>>& marque,std::map<std::string,double>& poids)
{
    Sommet* tampon;
    for (auto s: m_suivants)
    {
        tampon=s->getsuivant(this);
        if (marque[tampon->getnom()].first==0)//si le sommet n'est pas marquer
           {
            Som.push_back(tampon);
            marque[tampon->getnom()].second=this;
            poids[tampon->getnom()]=poids[this->getnom()]+s->get_poid();
           }
    }
}

Arete* Sommet::trouverArete(Sommet* ext1)
{
    Arete* Art=nullptr;
    for(auto s:m_suivants)
    {
        if (s->getext1()==this || s->getext1()==ext1)
            if (s->getext2()==this || s->getext2()==ext1)
                Art=s;
    }
    return Art;
}

