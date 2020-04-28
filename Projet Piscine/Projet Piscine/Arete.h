#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "biblio.h"
#include "svgfile.h"
#include "myComparator.h"
class Sommet;

class Arete
{
public:
    Arete(Sommet* s1, Sommet* s2);
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
    void Brand(const Sommet*precednent,std::map<const Sommet*,double>&distance,const double&d_a,std::priority_queue<std::pair<const Sommet*,std::pair<const Sommet*,double>>,std::vector<std::pair<const Sommet*,std::pair<const Sommet*,double>>>,myComparator>&q,std::map<const Sommet*,double>&sigma,std::map<const Sommet*,std::list<const Sommet*>>&predecesseur)const;
private:
    Sommet* m_ext1,* m_ext2;//extemit� des Arete
    double m_poids;
};

#endif
