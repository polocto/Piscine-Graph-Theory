#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "biblio.h"
class Arete;

class Sommet
{
public:
    Sommet(const std::string&nom, const double& pos_x, const double& pos_y);
    ~Sommet() = default;
    void ajoutS(Arete*suivant);
    void ajoutP(Arete*prece);
private:
    std::string m_nom;
    std::vector<Arete*> m_suivants,m_precedents;
    double m_i_d,m_i_vp,m_i_p;
    double m_x,m_y;
};

#endif
