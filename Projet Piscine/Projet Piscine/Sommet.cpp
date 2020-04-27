#include "Sommet.h"
#include "Arete.h"

Sommet::Sommet(const std::string&nom, const double& pos_x, const double& pos_y)
    :m_nom(nom),m_i_d(0),m_i_vp(0),m_i_p(0),m_x(pos_x),m_y(pos_y)
{

}

void Sommet::affichage(Svgfile* svgout)
{
    svgout->addDisk(m_x*100,m_y*100,10,"BLACK");
    svgout->addText(m_x*100-1,m_y*100-20,m_nom,"BLUE");
}


double Sommet::getx()
{
    return m_x;
}

double Sommet::getY()
{
    return m_y;
}
