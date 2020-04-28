#include "Sommet.h"
#include "Arete.h"

/**constructeur
initialisation de donn�es non pass� en param�tre � 0
*/
Sommet::Sommet(const std::string&nom, const double& pos_x, const double& pos_y)
    :m_nom(nom),m_i_d(0),m_i_vp(1),m_i_p(0),m_i_d_nn(0),m_x(pos_x),m_y(pos_y)
{
}

/**ajout d'une arete suivante*/
void Sommet::ajout(Arete*suivant)
{
    m_suivants.push_back(suivant);
}

/**Affichage console*/
void Sommet::affichageconsole()const
{
    std::cout<<m_nom<<" "<<m_x<<" "<<m_y<<" icd: "<<m_i_d<<" icp "<<m_i_p<<" ivp: "<<m_i_vp;
}
/**Affichage SVG*/
void Sommet::affichage(Svgfile& svgout)const
{
    svgout.addDisk(m_x*100,m_y*100,10,"BLACK");//Affichage sommet
    svgout.addText(m_x*100-1,m_y*100-20,m_nom,"BLUE");//Affichage nom sommet
}

/**GETTER*/

/**retourn la position x du sommet*/
double Sommet::getx()const
{
    return m_x;
}

/**retourn la position y du sommet*/
double Sommet::getY()const
{
    return m_y;
}

double Sommet::get_vp()const
{
    return m_i_vp;
}

/**retourn le nom du sommet*/
std::string Sommet:: getnom()const
{
    return m_nom;
}

/** Calcule icd indice de centralit� de degr�*/
void Sommet::calc_icd(const size_t&ordre)
{
    m_i_d_nn=m_suivants.size();
    m_i_d=m_i_d_nn/(double)ordre;
}
/**Calcul somme des indice de vecteur propre des voisins*/
void Sommet::calc_vp(std::map<Sommet*,double>&somme)
{
    somme[this]=0;//initialisation � 0
    for(Arete* a : m_suivants)
        somme.at(this)+=a->get_vp(this);//somme des vecteur propre des sommet voisins

}
/**mise � jour du de l'indice de vecteur propre*/
void Sommet::indice_vp(std::map<Sommet*,double>&somme,const double& lambda)
{
    m_i_vp=somme.at(this)/lambda;//somme des vecteur propre des sommet voisins divis� par lambda
}

///mise a jour de l'indice de centralité de proximité
void Sommet::calc_icp(double distance,double total)
{
    m_i_p=total/distance;
}

///mise a jour de l'indice de centralité d'intermediarité simplifier
void Sommet::calc_ici_naif(int total,int a)
{
    m_i_is=total/a;
}
///Sauvegarde
void Sommet::sauvegarde(std::ofstream&fichier)const
{
    fichier<<" indice de centrailite de degre : ("<<m_i_d_nn<<", "<<m_i_d<<"); ";
    fichier<<"indice de vecteur propre : "<<m_i_vp<<"; ";
    fichier<<"indice de proximite : "<<m_i_p<<";";
}

///Ajout les voisin d'un sommet a un veteur passer en parametre
void Sommet::ajoutvoisin(std::vector<Sommet*>& Som,std::map<std::string,std::pair<bool,Sommet*>>& marque,std::map<std::string,double>& poids)
{
    Sommet* tampon;
    for (auto s: m_suivants)
    {
        tampon=s->getsuivant(this);
        if (marque[tampon->getnom()].first==0)//si le sommet n'est pas marquer
           {
            Som.push_back(tampon);
            marque[tampon->getnom()].second=this;
            poids[tampon->getnom()]=poids[this->getnom()]+s->get_poid();
           }
    }
}

int Sommet::k_connexe(const Sommet* arrive)const
{
    int nombre_chemin=0;
    std::map<const Arete*,bool> arete;
    std::map<const Sommet*,bool>sommet;

    k_connexe(nombre_chemin,arete,sommet,arrive);
    return nombre_chemin;
}


void Sommet::k_connexe(int& nombre_chemin,std::map<const Arete*,bool>& arete,std::map<const Sommet*,bool>&sommet,const Sommet*arrive)const
{
    if(sommet.count(this))
        return;
    if(arrive==this)
    {
        nombre_chemin++;
        return;
    }
    sommet[this]=true;
    for(Arete* a : m_suivants)
        a->k_connexe(nombre_chemin,arete,sommet,arrive);
}

///retourne une arete avec les deux sommet aux extremiter
Arete* Sommet::trouverArete(Sommet* ext1)
{
    Arete* Art=nullptr;
    for(auto s:m_suivants)
    {
        if (s->getext1()==this || s->getext1()==ext1)
            if (s->getext2()==this || s->getext2()==ext1)
                Art=s;
    }
    return Art;
}

