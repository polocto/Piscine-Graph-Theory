#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "biblio.h"
#include "svgfile.h"
class Arete;

class Sommet
{
public:
    Sommet(const std::string&nom, const double& pos_x, const double& pos_y);//constructeur
    virtual ~Sommet() = default;//destructeur par default ne fait rien

    /**Getter*/
    std::string getnom()const;
    double getx()const;
    double getY()const;
    double get_vp()const;

    /**Ajout d'une arete au sommet*/
    virtual void ajout(Arete*suivant);

    /**Sauvegarde*/
    void sauvegarde(std::ofstream&fichier)const;

    /**Affichage*/
    void affichageconsole()const;
    void affichage(Svgfile& svgout)const;

    /**calcule indice*/
    void calc_icd(const size_t&ordre);
    void calc_vp(std::map<Sommet*,double>&somme);
    void indice_vp(std::map<Sommet*,double>&somme,const double& lambda);
private:
    std::string m_nom;
    std::vector<Arete*> m_suivants;
    double m_i_d,m_i_vp,m_i_p;
    double m_i_d_nn;
    double m_x,m_y;
};

#endif
