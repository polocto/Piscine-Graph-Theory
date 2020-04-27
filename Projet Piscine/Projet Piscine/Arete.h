#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "biblio.h"
#include "svgfile.h"
class Sommet;

class Arete
{
public:
    Arete(Sommet* s1, Sommet* s2);
    virtual  ~Arete() = default;
    void affichage(Svgfile& svgout);
    void ponderation(std::stringstream& ifs);
    void affichageconsole()const;
    double get_poid()const;
    Sommet* getsuivant(Sommet* Som)const;
    Sommet* getext1();
    Sommet* getext2();
private:
    Sommet* m_ext1,* m_ext2;//extemit� des Arete
    double m_poids;
};

#endif
