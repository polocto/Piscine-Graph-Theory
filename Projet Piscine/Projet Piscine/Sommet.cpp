#include "Sommet.h"
#include "Arete.h"


Sommet::Sommet(const std::string&nom, const double& pos_x, const double& pos_y)
    :m_nom(nom),m_i_d(0),m_i_vp(0),m_i_p(0),m_x(pos_x),m_y(pos_y)
{
}


void Sommet::ajout(Arete*suivant)
{
    m_suivants.push_back(suivant);
}


void Sommet::affichageconsole()const
{
    std::cout<<m_nom<<" "<<m_x<<" "<<m_y<<std::endl;
}
