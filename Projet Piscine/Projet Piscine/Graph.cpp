#include "Graph.h"
#include "Arete.h"
#include "Sommet.h"
#include "svgfile.h"


///Constructeur de graph:
///Prend en paramettre le nom du fichier utilisé
/// Crée et initialise les valeur des arretes et sommet en utilisant leur constructeur avec les information du fichier
Graph::Graph(std::ifstream&ifs)
{
    std::string line;
    size_t ot=0;
    if(!std::getline(ifs,line) || !is_int(line))throw(1);
        m_oriente=(bool)std::stoi(line);
    if(!std::getline(ifs,line) || !is_int(line))throw(1);
        ot=(size_t)std::stoi(line);
    if(ifs.fail())throw(1);
    for(size_t i=0;i<ot;i++)
    {
        std::string nom;
        int verrif=0;
        double x=0,y=0;
        if(!std::getline(ifs,line))throw(1);
        std::stringstream iss(line);
        iss>>verrif;
        if(iss.fail()|| verrif!=(int)i)throw(1);
        iss>>nom;
        if(iss.fail())throw(1);
        iss>>x;
        if(iss.fail())throw(1);
        iss>>y;
        if(iss.fail())throw(1);
        m_sommets.push_back(new Sommet(nom,x,y));// Creation d'une sommet avec les parametre du fichier nom, x, y
    }
    if(!std::getline(ifs,line) || !is_int(line))throw(1);
        ot=(size_t)std::stoi(line);
    for(size_t i=0;i<ot;i++)
    {
        std::string line;
        size_t verrif=0, s1=0,s2=0;
        if(!std::getline(ifs,line))throw(1);
        std::stringstream iss(line);
        iss>>verrif;
        if(iss.fail()||verrif!=i)throw(1);
        iss>>s1;
        if(ifs.fail() || s1>m_sommets.size())throw(1);
        iss>>s2;
        if(ifs.fail() || s2>m_sommets.size())throw(1);
        m_aretes.push_back(new Arete(m_sommets[s1],m_sommets[s2]));// Creation d'une Arete a partir des informations du fichier
    }
}


Graph::Graph(Graph* Gmodel,std::string changement)
{
    std::string ext1="",ext2="";
    ext1=changement[0];
    if (changement.size()==1)
        ext2=" ";
    if (changement.size()==2)
        ext2=changement[1];

    Sommet* Som1;
    Sommet* Som2;
    if (ext2==" ")
    {
        for (auto s: Gmodel->m_sommets)
            if (s->getnom()!=ext1)
                m_sommets.push_back(new Sommet(s->getnom(),s->getX(),s->getY()));

        for (auto s: Gmodel->m_aretes)
        {
            if (s->getext1()->getnom()!=ext1 && s->getext2()->getnom()!=ext1)
            {
                for (auto i:m_sommets)
                {
                    if (i->getnom()==s->getext1()->getnom())
                        Som1=i;
                    if(i->getnom()==s->getext2()->getnom())
                        Som2=i;
                }
                m_aretes.push_back(new Arete(Som1,Som2,s->get_poid()));
            }
        }
    }
    else{
        for (auto s: Gmodel->m_sommets)
            m_sommets.push_back(new Sommet(s->getnom(),s->getX(),s->getY()));

        for (auto s: Gmodel->m_aretes)
        {
                if (s->getext1()->getnom()!=ext1 || s->getext2()->getnom()!=ext2)
                {
                    for (auto i:m_sommets)
                {
                    if (i->getnom()==s->getext1()->getnom())
                        Som1=i;
                    if(i->getnom()==s->getext2()->getnom())
                        Som2=i;
                }
                m_aretes.push_back(new Arete(Som1,Som2,s->get_poid()));
            }
        }
    }

}

///Destructeur de Graph
///Supression de tout les sommets et de toutes les aretes qui le compose
Graph::~Graph()
{
    for(Sommet* s: m_sommets)
        delete s;
    for(Arete* a : m_aretes)
        delete a;
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

        for (int i=0;i<taille;i++)
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

/// Affichage du graph au format svg
/// Appel des fonction affichage pour chaque sommets et chaque arretes
void Graph::affichage(Svgfile& svgout)
{
    for (Sommet* S:m_sommets)
        S->affichage(svgout);
    for (Arete* A:m_aretes)
        A->affichage(svgout);
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
    std::cout <<" Arete composant le graph : "<<std::endl;
    for (auto s:m_aretes)
    {
        s->affichageconsole();//Appel de l'affichage de aretes qui affiche ces attribues
        std::cout<<std::endl;
    }
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

    while(abs(lambda-l)>=0.001)//tant que variance de lambda superieur à0,001
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

/**Sauvegarde*/
void Graph::sauvegarde(std::ofstream&fichier)const
{
    int i=0;
    for(Sommet* s : m_sommets)
    {
        fichier<<"Sommet : "<<i++;
        s->sauvegarde(fichier);
        fichier<<std::endl;
    }
}

int Graph::k_connexe()const
{
    int k=-1;

    for(Sommet*d : m_sommets)
    {
        for(Sommet * a : m_sommets)
        {
            if(a!=d)
            {
                int temp=d->k_connexe(a);
                if(temp<k || k< 0)
                    k=temp;
            }
        }
    }

    return k;
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
        i->calc_icp(distance,m_sommets.size()-1);///envoie les valeur pour modifier la valeur de l'indice icp des sommet
    }
}
void Graph::calc_ici_naif()
{
    for(auto i:m_sommets)
    {
        double total=0;
        double a=0;
        for (unsigned int j=0;j<m_sommets.size()-1;j++)
        {
            if (i!=m_sommets[j])
            {
                for (unsigned int k=j;k<m_sommets.size()-1;k++)
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
        std::cout<<total;
        i->calc_ici_naif(total,a);
    }
}

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
            else{
                    poids[sommetActif->getnom()]=poids[marque[sommetActif->getnom()].second->getnom()]+poidarete;
            }

           //supression de la liste du Sommet actif
            for (size_t i=0;i<Som.size();i++)
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
            else{
                    poids[sommetActif->getnom()]=poids[marque[sommetActif->getnom()].second->getnom()]+poidarete;
            }

           //supression de la liste du Sommet actif
            for (size_t i=0;i<Som.size();i++)
            {
                if (Som[i]==sommetActif)
                        Som.erase(Som.begin()+i);
            }
        }

    return poids[arriver->getnom()];//on retourne le poids du chemin
}



///  Vulnerabilité
Graph* Graph::Supression_element()
{
    Graph* etude_2;
    std::string choix;
    std::cout<<"quelle element voulez vous supprimer?";
    std::cin>>choix;

    etude_2=new Graph(this,choix);

    return etude_2;
}
