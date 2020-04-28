#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "biblio.h"
#include "svgfile.h"
class Sommet;

class Arete
{
public:
    Arete(Sommet* s1, Sommet* s2);
    Arete(Sommet* s1, Sommet* s2,double poids);
    virtual  ~Arete() = default;
    void affichage(Svgfile& svgout)const;
    void ponderation(std::stringstream& ifs);
    void affichageconsole()const;
    double get_vp(Sommet*precedent)const;
    double get_poid()const;
    Sommet* getsuivant(Sommet* Som)const;
    Sommet* getext1();
    Sommet* getext2();
    void k_connexe(int& nombre_chemin,std::map<const Arete*,bool>& arete,std::map<const Sommet*,bool>&sommet,const Sommet*arrive)const;
private:
    Sommet* m_ext1,* m_ext2;//extemit� des Arete
    double m_poids;
};

#endif
