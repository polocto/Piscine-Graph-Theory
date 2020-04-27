#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "biblio.h"
#include "svgfile.h"
#include "myComparator.h"
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

    /**Ajout d'une arete au sommet*/
    virtual void ajout(Arete*suivant);

    /**Affichage*/
    void affichageconsole()const;
    void affichage(Svgfile& svgout);

    /**calcule indice*/
    void calc_icd();
    void calc_icp(double distance,double total);
    //void dijkstra(std::map<char,std::pair<bool,Sommet*> marque);
   void ajoutvoisin(std::vector<Sommet*>& Som,std::map<std::string,std::pair<bool,Sommet*>>& marque,std::map<std::string,double>& poids);
   Arete* trouverArete(Sommet* ext1);
private:
    std::string m_nom;
    std::vector<Arete*> m_suivants;
    double m_i_d,m_i_vp,m_i_p;
    double m_x,m_y;
};

#endif
