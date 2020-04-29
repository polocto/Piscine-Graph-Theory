#include "Sommet.h"
#include "Arete.h"
#include <iomanip>

/**DEBUT CONSTRUCTION SOMMET*/
///constructeur
///initialisation de donn�es non pass� en param�tre � 0
Sommet::Sommet(const std::string&nom, const double& pos_x, const double& pos_y)
    :m_nom(nom),m_i_d(0),m_i_vp(1),m_i_p(0),m_i_i(0),m_i_is(0),m_i_i_nn(0),m_i_d_nn(0),m_x(pos_x),m_y(pos_y)
{
}


///Nouvelle Proposition
Sommet::Sommet(const Sommet* copie)
    :m_nom(copie->m_nom),m_i_d(0),m_i_vp(1),m_i_p(0),m_i_i(0),m_i_is(0),m_i_i_nn(0),m_i_d_nn(0),m_x(copie->m_x),m_y(copie->m_y)
{

}
///fin


/**ajout d'une arete suivante*/
void Sommet::ajout(Arete*suivant)
{
    m_suivants.push_back(suivant);
}
/**FIN CONSTRUCTION SOMMET*/

/**DEBUT AFFICHAGE*/
///Affichage console
void Sommet::affichageconsole()const
{
    std::cout<<std::setprecision(3);
    std::cout<<m_nom<<" icd: ("<<std::fixed<<m_i_d<<","<<m_i_d_nn<<")";
    std::cout<<" icp: "<<std::fixed<<m_i_p;
    std::cout<<" ivp: "<<std::fixed<<m_i_vp;
    std::cout<< " icis: "<<std::fixed<<m_i_is;
    std::cout<<" inter: ("<<std::fixed<<m_i_i<<", "<<std::fixed<<m_i_i_nn<<")";
}
///Affichage SVG
void Sommet::affichage(Svgfile& svgout)const
{
    svgout.addDisk(m_x*100,m_y*100,10,"BLACK");//Affichage sommet
    svgout.addText(m_x*100-1,m_y*100-20,m_nom,"BLUE");//Affichage nom sommet
}
/**FIN AFFICHAGE*/

/**DEBUT GETTER*/
///retourn le nom du sommet
std::string Sommet:: getnom()const
{
    return m_nom;
}

///retourn la position x du sommet
double Sommet::getX()const
{
    return m_x;
}

///retourn la position y du sommet
double Sommet::getY()const
{
    return m_y;
}
///retourne l'indice de vecteur propre
double Sommet::get_vp()const
{
    return m_i_vp;
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
/**FIN GETTER*/

/**DEBUT CALCULE INDICES*/
///Calcule icd indice de centralit� de degr�
void Sommet::calc_icd(const size_t&ordre)
{
    m_i_d_nn=m_suivants.size();
    m_i_d=m_i_d_nn/(double)(ordre-1);
}
///Calcul somme des indice de vecteur propre des voisins
void Sommet::calc_vp(std::map<Sommet*,double>&somme)
{
    somme[this]=0;//initialisation � 0
    for(Arete* a : m_suivants)
        somme.at(this)+=a->get_vp(this);//somme des vecteur propre des sommet voisins

}
///mise a jour du de l'indice de vecteur propre
///normalise l'indice
void Sommet::indice_vp(std::map<Sommet*,double>&somme,const double& lambda)
{
    m_i_vp=somme.at(this)/lambda;//somme des vecteur propre des sommet voisins divise par lambda
}

///mise a jour de l'indice de centralité de proximité
///normalise l'indice
void Sommet::calc_icp(double distance,double total)
{
    m_i_p=total/distance;
}

///mise a jour de l'indice de centralité d'intermediarité simplifier
///normalise l'indice
void Sommet::calc_ici_naif(double total,double a)
{
    m_i_is=total/a;
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

///Calcule des indice de centralité d'intermédiarité suivant l'alorithme de Brand
///normalisé et non
void Sommet::Brand(const std::map<const Sommet*,double>&Cb,const double&n)
{
    m_i_i_nn=0;
    if(Cb.count(this))
        m_i_i_nn=Cb.at(this);
    m_i_i=m_i_i_nn/(n*n-3*n+2);
}
///Algortihme de Brand
void Sommet::Brand(std::map<const Sommet*,double>&distance,std::priority_queue<std::pair<const Sommet*,std::pair<const Sommet*,double>>,std::vector<std::pair<const Sommet*,std::pair<const Sommet*,double>>>,myComparator>&q,std::map<const Sommet*,double>&sigma,std::map<const Sommet*,std::list<const Sommet*>>&predecesseur)const
{
    if(!distance.count(this))//Si le sommet n'a pas encore atteint son plus court chemin
    {
        distance[this]=q.top().second.second;//definir son plus court chemin (suit le principe de Dijkstra)
        for(const Arete* a : m_suivants)//parcourir l'ensemble de ses aretes adjacentes
            a->Brand(this,distance,distance.at(this),q,sigma,predecesseur);//parcourir les aretes
    }
    if(distance.at(this)==q.top().second.second && q.top().second.first != nullptr)//si la distance la plus courte du sommet est celle proposé par la file
    {
        sigma.at(this)+=sigma.at(q.top().second.first);//ajouter le nombre de chemin le plus court de son prédecesseur à lui même
        predecesseur.at(this).push_back(q.top().second.first);//ajouter son prédécesseur à l'ensemble de ses prédécesseur sur les plus courts chemins
    }
    else if(distance.at(this)>q.top().second.second)//si la distance minimal de ce sommet est supérieur à celle proposé dans la file erreur dans l'algo
        std::cout<<"Erreur"<<std::endl;
}
/**FIN CALCULE INDICES*/

/**DEBUT ETUDE DE CONNEXITE*/
/**etude de la k_arete connexite*/
///Sommet de départ
int Sommet::k_connexe(const Sommet* arrive)const
{
    //declaration des variables nécessaires
    int nombre_chemin=0;
    std::map<const Arete*,bool> arete;//permet de savoir si nous sommes déjà passé par l'arête
    std::map<const Sommet*,bool>sommet;//permet de savoir si nous sommes déjà passé par le sommet

    k_connexe(nombre_chemin,arete,sommet,arrive);

    return nombre_chemin;//retourne le nombre max de chemin sans passer deux fois par une ârete
}

///Sommet quelconque
void Sommet::k_connexe(int& nombre_chemin,std::map<const Arete*,bool>& arete,std::map<const Sommet*,bool>&sommet,const Sommet*arrive)const
{
    if(sommet.count(this))//si nous sommes déjà passer par ce sommet areter la récursivité
        return;
    if(arrive==this)//si nous sommes au sommet d'arrivé
    {
        nombre_chemin++;//ajouter un nouveau chemin
        return;//fin reccursivité
    }
    sommet[this]=true;//si n'existe pas et n'est pas le sommet d'arrivé marquer le sommet
    for(Arete* a : m_suivants)//parcourir l'ensemble des arets pour aller aux sommets suivants
        a->k_connexe(nombre_chemin,arete,sommet,arrive);
}
/**FIN ETUDE DE CONNEXITE*/

///Sauvegarde
void Sommet::sauvegarde(std::ofstream&fichier)const
{
    //ecriture dans le fichier
    fichier<<" indice de centrailite de degre : ("<<m_i_d_nn<<", "<<m_i_d<<"); ";
    fichier<<"indice de vecteur propre : "<<m_i_vp<<"; ";
    fichier<<"indice de proximite : "<<m_i_p<<"; ";
    fichier<<"indice de centralite d'intermediarite : ("<<m_i_i_nn<<", "<<m_i_d<<"); ";
}
