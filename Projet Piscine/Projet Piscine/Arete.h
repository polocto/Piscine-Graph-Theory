#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "biblio.h"
#include "svgfile.h"
class Sommet;

class Arete
{
public:
    Arete(Sommet* s1, Sommet* s2);
    ~Arete() = default;
    void affichage(Svgfile& svgout);
    void ponderation(std::stringstream& ifs);
    void affichageconsole()const;
private:
    Sommet* m_ext1,* m_ext2;
    double m_poids;
};

#endif
