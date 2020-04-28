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
    void calc_ici_naif(int total,int a);
    int k_connexe(const Sommet* arrive)const;
    void k_connexe(int& nombre_chemin,std::map<const Arete*,bool>& arete,std::map<const Sommet*,bool>&sommet,const Sommet*arrive)const;

    void calc_icp(double distance,double total);
   void ajoutvoisin(std::vector<Sommet*>& Som,std::map<std::string,std::pair<bool,Sommet*>>& marque,std::map<std::string,double>& poids);
   Arete* trouverArete(Sommet* ext1);

private:
    std::string m_nom;
    std::vector<Arete*> m_suivants;
    double m_i_d,m_i_vp,m_i_p,m_i_is;
    double m_i_d_nn;
    double m_x,m_y;
};

#endif
