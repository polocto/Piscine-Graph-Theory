#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"
/**CONSTUCTION DU ARETE DEBUT*/
///Constructeur de la class Arete
///Prend en parametre les adresses des deux extremit�e pour initialiser arrete et pour ajouter l'arrete a leur liste de suivant
///initialisation du poids a 1 cas d'un graph non ponder�
Arete::Arete(Sommet* s1, Sommet* s2,bool oriente)
    :m_ext1(s1),m_ext2(s2),m_poids(1)
{
    m_ext1->ajout(this);
    if (!oriente)
        m_ext2->ajout(this);
}
///constructeur copie arete
///Nouvelle proposition
Arete::Arete(const Arete* copie,const std::map<const Sommet*,Sommet*>&traducteur)
    :m_poids(copie->m_poids)
{
    if(!traducteur.count(copie->m_ext1) || !traducteur.count(copie->m_ext2))
        throw (0);

    m_ext1=traducteur.at(copie->m_ext1);
    m_ext2=traducteur.at(copie->m_ext2);
    m_ext1->ajout(this);
    m_ext2->ajout(this);
}
///fin

///initialisation des ponderation apartir d'un flot de fichier
void Arete::ponderation(std::stringstream& iss)
{
    iss>>m_poids;

    if (iss.fail())
        throw("probleme dans la lecture de la ligne du fichier: fichier corompu");
}
/**CONSTUCTION DE ARETE FIN*/
/**AFFICHAGE DE ARETE DEBUT*/
///Affichage des informations lier a Arete dans la console
void Arete::affichageconsole()const
{
    std::cout<<m_ext1->getnom()<<" "<<m_ext2->getnom()<<" "<<m_poids;//utilisation de getteur pour acceder au nom des sommets
}

/// Affichage au format svg d'une Arete du graph
void Arete::affichage(Svgfile& svgout,const bool&oriente)const
{
    int coef=15;
    int coef2=3;
    svgout.addLine(m_ext1->getX()*coef+2,m_ext1->getY()*coef+2,m_ext2->getX()*coef+2,m_ext2->getY()*coef+2,"BLACK");
    /*if(oriente)
    {
        double d_x=m_ext2->getX()*coef+2,d_y=m_ext2->getY()*coef+2;
        double x=m_ext2->getX()-m_ext1->getX(),y=m_ext2->getY()-m_ext1->getY();
        double module=sqrt(x*x+y*y);
        double a=(-y)/module,b=x/module;
        double coeff=3.5;
        x/=module;
        y/=module;
        double pointe_x = d_x-3*x, pointe_y=d_y-3*y;
        double ext1_x=d_x-(coef2+coeff)*x-a*coeff,ext1_y=d_y-(coef2+coeff)*y-coeff*b;
        double ext2_x=d_x-(coef2+coeff)*x+a*coeff,ext2_y=d_y-(coef2+coeff)*y+coeff*b;
        svgout.addTriangle(pointe_x,pointe_y,ext1_x,ext1_y,ext2_x,ext2_y,"black");
    }*/
}
/**AFFICHAGE DE ARETE FIN*/

/**GETTER DEBUT*/
///recupere l'indice de vecteur propre du voisin
double Arete::get_vp(Sommet*precedent)const
{
    if(precedent==m_ext1)
        return m_ext2->get_vp();
    return m_ext1->get_vp();
}

///getteur qui retourn le poids
double Arete::get_poid()const
{
    return m_poids;
}

///getteur qui renvoie l'adresse d'un sommet avec 1 arete et l'autre sommet
Sommet* Arete::getsuivant(Sommet* Som)const
{
    if (Som==m_ext1)
        return m_ext2;
    return m_ext1;
}
///Getteur des extremitées de l'arete
Sommet* Arete::getext1()
{
    return m_ext1;
}
Sommet*Arete::getext2()
{
    return m_ext2;

}
/**GETTER FIN*/


bool Arete::verrif(const std::string&ext1,const std::string&ext2)const
{
    return ext1!=m_ext1->getnom() || m_ext2->getnom()!=ext2;
}

/**Indice intermediarite*/
void Arete::Brand(const Sommet*precednent,std::map<const Sommet*,double>&distance,const double&d_a,std::priority_queue<std::pair<const Sommet*,std::pair<const Sommet*,double>>,std::vector<std::pair<const Sommet*,std::pair<const Sommet*,double>>>,myComparator>&q,std::map<const Sommet*,double>&sigma,std::map<const Sommet*,std::list<const Sommet*>>&predecesseur)const
{
    Sommet* suivant=nullptr;
    if(precednent==m_ext1)//definir qui est le sommet suivant
        suivant=m_ext2;
    else
        suivant=m_ext1;

    if(!distance.count(suivant) || distance.at(suivant)>d_a+m_poids)//si mon sommet n'a pas de distance ou que sa distance min est sup à nouvelle distance(ce sui ne devrai pas arriver)
    {
        q.push(std::pair<const Sommet*,std::pair<const Sommet*,double>> {suivant,std::pair<const Sommet*,double>{precednent,d_a+m_poids}}); //ajouter à la file
        sigma[suivant]=0;//initialiser son nombre de chemin dont il fait parti à zero
        predecesseur[suivant].clear();//vider sa liste de précédent
    }
    else if(distance.at(suivant)==d_a+m_poids)//si son nombre de sommet est égale
    {
        sigma.at(suivant)+=sigma.at(precednent);//actualiser son nombre de chemin
        predecesseur.at(suivant).push_back(precednent);//ajouter predecesseu à l'ensemble des predecesseur
    }
}
/**k-arete connexité*/
void Arete::k_connexe(int& nombre_chemin,std::map<const Arete*,bool>& arete,std::map<const Sommet*,bool>&sommet,const Sommet*arrive)const
{
    if(arete.count(this))//si l'arete est déjà emprunter (considéré comme saturé)
        return;//fin sous-programme
    arete[this]=true;//saturer l'arete
    if(!sommet.count(m_ext1))//si mon sommet ext1 n'a pas était emprunter
        m_ext1->k_connexe(nombre_chemin,arete,sommet,arrive);
    else if(!sommet.count(m_ext2))//si mon sommet ext2 n'a pas était emprunter
        m_ext2->k_connexe(nombre_chemin,arete,sommet,arrive);
}
