#include "Graph.h"
#include "Arete.h"
#include "Sommet.h"
#include "myComparator.h"
#include "svgfile.h"

/**DEBUT CHARGMENT INFOS LIEE AU GRAPH*/
///Constructeur de graph:
///Prend en paramettre le nom du fichier utilisé
/// Crée et initialise les valeur des arretes et sommet en utilisant leur constructeur avec les information du fichier
Graph::Graph(std::ifstream&ifs)
{
    std::string line;
    size_t ot=0;
    if(!std::getline(ifs,line) || !is_int(line))
        throw(1);
    m_oriente=(bool)std::stoi(line);//orientation du graphe
    if(!std::getline(ifs,line) || !is_int(line))
        throw(1);
    ot=(size_t)std::stoi(line);//ordre du graph
    if(ifs.fail())
        throw(1);
    ///lecture Sommets
    for(size_t i=0; i<ot; i++)
    {
        std::string nom;
        int verrif=0;
        double x=0,y=0;
        if(!std::getline(ifs,line))
            throw(1);//recupération ligne du fichier
        std::stringstream iss(line);
        iss>>verrif;
        if(iss.fail()|| verrif!=(int)i)
            throw(1);
        iss>>nom;
        if(iss.fail())
            throw(1);
        iss>>x;
        if(iss.fail())
            throw(1);
        iss>>y;
        if(iss.fail())
            throw(1);
        m_sommets.push_back(new Sommet(nom,x,y));// Creation d'une sommet avec les parametre du fichier nom, x, y
    }
    if(!std::getline(ifs,line) || !is_int(line))
        throw(1);
    ot=(size_t)std::stoi(line);//taille du graph
    ///lecture Arete
    for(size_t i=0; i<ot; i++)
    {
        std::string line;
        size_t verrif=0, s1=0,s2=0;
        if(!std::getline(ifs,line))
            throw(1);
        std::stringstream iss(line);
        iss>>verrif;
        if(iss.fail()||verrif!=i)
            throw(1);
        iss>>s1;
        if(ifs.fail() || s1>m_sommets.size())
            throw(1);
        iss>>s2;
        if(ifs.fail() || s2>m_sommets.size())
            throw(1);
        m_aretes.push_back(new Arete(m_sommets[s1],m_sommets[s2],m_oriente));// Creation d'une Arete a partir des informations du fichier
    }
}
///Construction d'un graph partiel
///Reccupération du graph à copié et suppression du changment reccupéré en string
Graph::Graph(Graph* Gmodel,std::string changement)
    :m_oriente(Gmodel->m_oriente)//MODIF
{
    std::string ext1="",ext2="";
    ext1=changement[0];
    if (changement.size()==1)
        ext2=" ";
    if (changement.size()==2)
        ext2=changement[1];
    std::map<const Sommet*,Sommet*>traducteur;//MODIF
    if (ext2==" ")//retrait d'un sommet
    {
        for (auto s: Gmodel->m_sommets)
            if (s->getnom()!=ext1)
            {
                m_sommets.push_back(new Sommet(s));//MODIF
                traducteur[s]=m_sommets.back();//MODIF
            }

        for (auto s: Gmodel->m_aretes)
        {
            try
            {
                Arete* temp=new Arete(s,traducteur);//MODIF
                m_aretes.push_back(temp);//MODIF
            }
            catch(int a)
            {
            }
        }
    }
    else//retrait d'une arete
    {
        for (auto s: Gmodel->m_sommets)//récuppération des valeur d'un sommet et copie dans un nouveau sommet
        {
            m_sommets.push_back(new Sommet(s));//MODIF
            traducteur[s]=m_sommets.back();//MODIF
        }

        for (auto s: Gmodel->m_aretes)
        {
            if (s->verrif(ext1,ext2))//selection des aretes à copier
            {
                m_aretes.push_back(new Arete(s,traducteur));//copie des aretes//MODIF
            }
        }
    }
}

///Destructeur de Graph
///Supression de tout les sommets et de toutes les aretes qui le compose
Graph::~Graph()
{
    for(Sommet* s: m_sommets)
        delete s;//Suppression de l'ensemble des sommets
    for(Arete* a : m_aretes)
        delete a;//suppression de l'ensemble des aretes
}

///Chargement de la ponderation
///mise en place d'une ponderation au arete du graph a partir d'un fichier
void Graph::chargementPonderation(std::string nomfichier)
{
    std::ifstream ifs(nomfichier);
    std::string line;
    int taille;

    try
    {
        if(!ifs.is_open())
            throw("probleme a l'ouverture du fichier:"+nomfichier);

        //recuperation de la taille du graph
        if(std::getline(ifs, line))
        {
            std::stringstream iss(line);
            iss>>taille;
        }
        else
            throw("probleme dans la lecture de la ligne du "+nomfichier+" : fichier corompu");

        if(taille>(int)m_aretes.size())
            throw(nomfichier+" non comforme : trops d'arrete pour la taille du graph // fichier peu etre corompu");

        for (int i=0; i<taille; i++)
        {
            std::getline(ifs, line);
            std::stringstream iss(line);
            int indice;
            iss >> indice;//recuperation de la position de l'arrete dans le vecteur d'arete de graph

            if (iss.fail())
                throw("probleme dans la lecture de la ligne du "+nomfichier+" : fichier corompu");

            if (indice>taille)
                throw("fichier non comforme : trops d'arrete pour la taille du graph // fichier peu etre corompu");

            m_aretes[indice]->ponderation(iss);//apele de la fonction de arete pour modifier la valeur du poid
        }
    }
    catch (std::string probleme)
    {
        std::cout<<probleme;
    }
}
/**FIN DES INFOS LIEE AU CHARGEMENT*/

/**DEBUT DE L'AFFICHAGE D'UN GRAPH*/
void Graph::affichage_poly()const
{
    Svgfile svgout;
    affichage(svgout);
    affichageconsole();
}

/// Affichage du graph au format svg
/// Appel des fonction affichage pour chaque sommets et chaque arretes
void Graph::affichage(Svgfile& svgout)const
{
    for (Sommet* S:m_sommets)
        S->affichage(svgout);//affiche l'ensemble des sommets
    for (Arete* A:m_aretes)
        A->affichage(svgout);//affiche l'ensemble des aretes
}

void Graph::affichage_suppression()
{
    std::cout<<"Voici la liste des sommet du graph :\n";
    for (auto s:m_sommets)
        std::cout<< s->getnom()<<"  -  ";

    std::cout<<std::endl;
    for (auto s:m_aretes)
        std::cout<<s->getext1()->getnom()<<" "<<s->getext2()->getnom()<<std::endl;

}

///Affichage des parametre du graphe en console
///utiliser pour verification du chargement du graphe
void Graph::affichageconsole()const
{
    std::cout<<" Sommet composant le graf :"<<std::endl;
    for( auto s:m_sommets)
    {
        s->affichageconsole();//Appel de l'affichage des paramettre des Sommets
        std::cout<<std::endl;
    }
    /*std::cout <<" Arete composant le graph : "<<std::endl;
    for (auto s:m_aretes)
    {
        s->affichageconsole();//Appel de l'affichage de aretes qui affiche ces attribues
        std::cout<<std::endl;
    }*/
}

/**CALCULE DES INDICES DU GRAPH*/

void Graph::calcule_indices()
{

    calc_icd();
    calc_vect_propre();
    calc_icp();
    Brand();
    if(k_connexe())
        calc_ici_naif();
}

///Calcule de l'indice de centralité de degrée
void Graph::calc_icd()
{
    for (auto s:m_sommets)
        s->calc_icd(m_sommets.size());
}

///Calucle de l'indice de vecteur propre
void Graph::calc_vect_propre()
{
    double lambda=-1,l=0;

    while(abs(lambda-l)>=0.001)//tant que variance de lambda superieur à 10^-3
    {
        std::map<Sommet*,double>somme;
        lambda = l;
        l=0;
        for(Sommet* s : m_sommets)
            s->calc_vp(somme);//somme de vecteur propre de sommet voisins pour chaque sommets
        for(Sommet* s : m_sommets)
            l+=somme.at(s)*somme.at(s);//somme des carré des sommes ci-dessus
        l=sqrt(l);//racine de la somme
        for(Sommet* s : m_sommets)
            s->indice_vp(somme,l);//actualisation des indices
    }
}
///Calcule de l'indice de centralité d'intermédiarité avec l'algorithme de Brand
void Graph::Brand()
{
    std::map<const Sommet*,double>Cb;
    for(const Sommet* s : m_sommets)
        Cb[s]=0;
    for(Sommet* d : m_sommets)
    {
        //Déclarations
        std::stack<const Sommet*>p;
        std::map<const Sommet*,bool> verrif;
        std::map<const Sommet*,double>delta;
        std::map<const Sommet*,std::list<const Sommet*>>predecesseur;
        std::map<const Sommet*,double>sigma;
        std::map<const Sommet*,double>distance;
        std::priority_queue<std::pair<const Sommet*,std::pair<const Sommet*,double>>,std::vector<std::pair<const Sommet*,std::pair<const Sommet*,double>>>,myComparator>q;
        //utiliser Dijkstra
        q.push(std::pair<const Sommet*,std::pair<const Sommet*,double>> {d,std::pair<const Sommet*,double>{nullptr,0}});
        sigma[d]=1;
        while(!q.empty())
        {
            if(!verrif.count(q.top().first))
            {
                p.push(q.top().first);
                verrif[q.top().first]=true;
            }
            q.top().first->Brand(distance,q,sigma,predecesseur);
            q.pop();
        }
        for(const Sommet* v : m_sommets)
            delta[v]=0;
        //Méthode de BRAND
        while(!p.empty())
        {
            if(p.top()!=d)
            {
                for(const Sommet* pre : predecesseur.at(p.top()))
                    delta.at(pre)+=(sigma.at(pre)/sigma.at(p.top()))*(1+delta.at(p.top()));
                Cb.at(p.top())+=delta.at(p.top());
            }
            p.pop();
        }
    }
    //affiliation des valeurs calculé au différentssommets du graphe
    for(Sommet* s : m_sommets)
        s->Brand(Cb,(double)m_sommets.size());
}

///calcule de l'indicateur de centralité de proximité pour chaque sommet
/// On test ainsi tout les chemins possible entre 2 sommets pour sommer les distances
void Graph::calc_icp()
{
    for (auto i:m_sommets)
    {
        double distance=0;
        for(auto s:m_sommets)
        {
            if (s!=i)
                distance+=Dijkstra(i,s);
        }
        i->calc_icp(distance,m_sommets.size()-1);//envoie les valeur pour modifier la valeur de l'indice icp des sommet
    }
}

///calcul de l'indice de centralité d'intermédiarité avec l'agorithme naïf
///considère qu'il n'y a que un plus court chemin
void Graph::calc_ici_naif()
{
    for(auto i:m_sommets)
    {
        double total=0;
        double a=0;
        for (unsigned int j=0; j<m_sommets.size()-1; j++)
        {
            if (i!=m_sommets[j])
            {
                for (unsigned int k=j; k<m_sommets.size()-1; k++)
                {
                    if (i!=m_sommets[k])
                    {
                        if (m_sommets[j]!=m_sommets[k])
                        {
                            ///Dijtra renvoie un bool
                            total+=Dijkstra(m_sommets[j],m_sommets[k],i);
                            a++;
                        }
                    }
                }
            }
        }
        ///initialisation du ici
        i->calc_ici_naif(total,a);
    }
}
/**Début Dijkstra*/
bool Graph:: Dijkstra(Sommet* depart,Sommet* arriver,Sommet* passage)
{
    std::vector<Sommet*> Som;
    std::map<std::string,std::pair<bool,Sommet*>> marque;
    std::map<std::string,double> poids;

    double poidarete=0;
    Sommet* sommetActif;
    Arete* areteactive;

    //ajout du Sommet de depart a la liste
    Som.push_back(depart);

    //initialisation des maps utiliser
    for (auto s: m_sommets)
    {
        marque[s->getnom()]=std::pair<bool,Sommet*>(0,nullptr);
        poids[s->getnom()]=0;
    }

    while (marque[arriver->getnom()].first==0 && !Som.empty())//La boucle tourne tant que la liste est remplie et le Sommet d'arriver n'est pas marquer
    {
        //Determiner le sommet actif
        sommetActif=Som[0];
        for (auto s:Som)
        {
            if (poids[s->getnom()]<poids[sommetActif->getnom()])
                sommetActif=s;
        }

        sommetActif->ajoutvoisin(Som,marque,poids);
        marque[sommetActif->getnom()].first=1; //Marquage du sommetActif pour qu'il ne soit plus ajouter a la liste des suivant

        //Determination du poidtotal du chemin le plus cours pour chaque arete du graphe tant que sommet n'est pas decouvert
        if (marque[sommetActif->getnom()].second!=nullptr)
        {
            areteactive=sommetActif->trouverArete(marque[sommetActif->getnom()].second);
            poidarete=areteactive->get_poid();
        }

        if (marque[sommetActif->getnom()].second==nullptr)
        {
            poids[sommetActif->getnom()]=poidarete;
        }
        else
        {
            poids[sommetActif->getnom()]=poids[marque[sommetActif->getnom()].second->getnom()]+poidarete;
        }

        //supression de la liste du Sommet actif
        for (size_t i=0; i<Som.size(); i++)
        {
            if (Som[i]==sommetActif)
                Som.erase(Som.begin()+i);
        }
    }

    unsigned int i=0;
    sommetActif=arriver;
    while(sommetActif!=depart && i<m_sommets.size())
    {
        if (marque[sommetActif->getnom()].second==passage)
            return 1;
        sommetActif=marque[sommetActif->getnom()].second;
        i++;
    }
    return 0;
}

/**Algorithme de dijkstra modifier pour donner la longeur du plus cour chemin entre deux Sommets
Prend en paramettre l'adresse de depart et l'adresse d'arriver et renvoie une distance total*/
double Graph::Dijkstra(Sommet* depart,Sommet* arriver)
{
    //Declaration de variable
    std::vector<Sommet*> Som;
    std::map<std::string,std::pair<bool,Sommet*>> marque;
    std::map<std::string,double> poids;

    double poidarete=0;
    Sommet* sommetActif;
    Arete* areteactive;

    //ajout du Sommet de depart a la liste
    Som.push_back(depart);

    //initialisation des maps utiliser
    for (auto s: m_sommets)
    {
        marque[s->getnom()]=std::pair<bool,Sommet*>(0,nullptr);
        poids[s->getnom()]=0;
    }

    while (marque[arriver->getnom()].first==0 && !Som.empty())//La boucle tourne tant que la liste est remplie et le Sommet d'arriver n'est pas marquer
    {
        //Determiner le sommet actif
        sommetActif=Som[0];
        for (auto s:Som)
            if (poids[s->getnom()]<poids[sommetActif->getnom()])
                sommetActif=s;

        sommetActif->ajoutvoisin(Som,marque,poids);
        marque[sommetActif->getnom()].first=1; //Marquage du sommetActif pour qu'il ne soit plus ajouter a la liste des suivant

        //Determination du poidtotal du chemin le plus cours pour chaque arete du graphe tant que sommet n'est pas decouvert
        if (marque[sommetActif->getnom()].second!=nullptr)
        {
            areteactive=marque[sommetActif->getnom()].second->trouverArete(sommetActif);
            poidarete=areteactive->get_poid();
        }

        if (marque[sommetActif->getnom()].second==nullptr)
            poids[sommetActif->getnom()]=poidarete;
        else
            poids[sommetActif->getnom()]=poids[marque[sommetActif->getnom()].second->getnom()]+poidarete;

        //supression de la liste du Sommet actif
        for (size_t i=0; i<Som.size(); i++)
            if (Som[i]==sommetActif)
                Som.erase(Som.begin()+i);
    }

    return poids[arriver->getnom()];//on retourne le poids du chemin
}
/**Fin Dijkstra*/
/**FIN CALCULE DES INDICES DU GRAPH*/

/**TEST LA CONNEXITE DU GRAPH*/

///Test la k-arete-connexité d'un graph avec la méthode des flot
///la capacité de l'ensemble des aretes est équivalente à 1 pour 1 passage par arete
int Graph::k_connexe()const
{
    int k=-1;

    for(Sommet*d : m_sommets)//en partant de chaque sommet
    {
        for(Sommet * a : m_sommets)//pour aller à l'ensemble des autres sommet
        {
            if(a!=d)
            {
                int temp=d->k_connexe(a);//nombre de chemin existant pour aller de d à a
                if(temp<k || k< 0)//prend le plus grand nombre de chemin existant
                    k=temp;
            }
        }
    }
    return k;//retourne le nombre de chemin différent en empruntant qu'une seul fois les arete sois la k-arete-connexité
}
/**FIN DU TEST DE CONNEXITE D'UN GRAPH*/

/**DEBUT SAUVEGARDE*/
/**Sauvegarde*/
void Graph::sauvegarde(std::ofstream&fichier)const
{
    int i=0;
    for(Sommet* s : m_sommets)
    {
        fichier<<"Sommet : "<<i++;//indice du sommet
        s->sauvegarde(fichier);//écriture des données d'un sommet
        fichier<<std::endl;//retour à la ligne
    }
}
/**FIN SAUVEGARDE*/

/**DEBUT TEST LA VULNERABILTE D'UN GRAPH*/
///  Vulnerabilité
Graph* Graph::Supression_element()
{
    Graph* etude_2;
    std::string choix;
    std::cout<<"quelle element voulez vous supprimer?";
    std::cin>>choix;//saisie

    etude_2=new Graph(this,choix);

    if(etude_2->m_aretes.size() == m_aretes.size() && etude_2->m_sommets.size() == m_sommets.size() )
    {
        delete etude_2;
        throw (0);
    }


    return etude_2;
}

void Graph::comparaison_graph(Graph* ancien)
{
    std::cout<< "Evolution des indicateur apres la suppression \n";
    for (auto s:m_sommets)
    {
         bool fin=1;
        unsigned int  i=0;
        while(fin && i<ancien->m_sommets.size())
        {
            if (ancien->m_sommets[i]->getnom()==s->getnom())
                fin=0;

            else i++;
        }

        s->affichage_comparaison(ancien->m_sommets[i]);
    }
}

/**FIN TEST LA VULNERABILTE D'UN GRAPH*/
