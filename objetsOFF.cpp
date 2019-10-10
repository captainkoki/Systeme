#include <errno.h>
#include <unistd.h>

#include <cstring>
#include <cstdlib>
#include <cstdio>

#include <cmath>

#include <iostream>

#include "objetsOFF.h"


point3 VecteurFromPoints(const point3 * _p1, const point3 * _p2) {
point3 res;
	res.x = _p2->x - _p1->x;
	res.y = _p2->y - _p1->y;
	res.z = _p2->z - _p1->z;
return res;
}

Objet::Objet() {
	strcpy(nom, "nil");
	nbsommets=0;
	nbfaces=0;
	id=0;
}

Objet::~Objet() {
//nil
}
///////////////////////////////cm
void Objet::calculNormalface()
{
	//initialise le tableau pour pouvoir mettre les valeurs dedans
	

	std::cout << somparfaces.size() << "\n";

	point3 Vab(0 , 0 , 0); 
	point3 Vbc(0 , 0 , 0);
	point3 pV(0 , 0 , 0);
	
	double norme;

	for (unsigned long i = 0; i < nbfaces; ++i)
	{

		point3 A(lpoints[lifaces[i].s0]);
		point3 B(lpoints[lifaces[i].s1]);
		point3 C(lpoints[lifaces[i].s2]);
		
		Vab.x = abs(B.x + A.x);
		Vab.y = abs(B.y + A.y);
		Vab.z = abs(B.z + A.z);

		Vbc.x = C.x - B.x;
		Vbc.y = C.y - B.y;
		Vbc.z = C.z - B.z;

		pV.x = Vab.y * Vbc.z - Vab.z * Vbc.y;
		pV.y = Vab.z * Vbc.x - Vab.x * Vbc.z;
		pV.z = Vab.x * Vbc.y - Vab.y * Vbc.x;

		norme = sqrt(pV.x * pV.x + pV.y * pV.y + pV.z * pV.z);

		point3 ui(pV.x / norme, pV.y / norme, pV.z / norme);

		std::cout << ui << "\n";

		somparfaces[lifaces[i].s0].push_back(ui);
		somparfaces[lifaces[i].s1].push_back(ui);
		somparfaces[lifaces[i].s2].push_back(ui);

		std::cout << i << "\n";
		//NormFace.push_back(nface);
	}
}

void Objet::calculNormalsommet()
{
	std::cout << "Normalsommet" << "\n";
	double X = 1, Y = 1, Z = 1;
	for (unsigned long i = 0; i < somparfaces.size(); ++i)
	{

		std::cout << i << "\n";
		for (unsigned long j = 0; j < somparfaces[i].size(); ++j)
		{
			X = X * somparfaces[i][j].x;
			Y = Y * somparfaces[i][j].y;
			Z = Z * somparfaces[i][j].z;
		}
		X = X / somparfaces[i].size();
		Y = Y / somparfaces[i].size();
		Z = Z / somparfaces[i].size();
		NormSommet.push_back(point3(X, Y, Z));
		std::cout << "[" << X << " ; " << Y << " ; " << Z << "]\n";
	}
}

void Objet::infoNormS()
{
	std::cout << "\n NORMAL AU SOMMETS\n";
	for (unsigned int i = 0; i < NormSommet.size(); ++i)
	{
		std::cout << i << " : [" << NormSommet[i].x << " ; " << NormSommet[i].y << " ; " << NormSommet[i].z << "]\n";
	}
}


/////////////////////////////

void Objet::charge_OFF(const char nom_fichier[40])
{
unsigned int i;
FILE * fichier;
unsigned int n;

char magic[10];

if ((fichier=fopen(nom_fichier,"r"))==NULL)
        {
		perror("Erreur a l'ouverture du fichier OFF");
        	exit(1);
        }

fscanf(fichier,"%s\n",magic);

if (strcmp(magic, "OFF")!=0) {
	perror("Erreur dans l'en tête du fichier OFF");
        exit(0);
}

fscanf(fichier,"%u %u %u\n",&nbsommets, &nbfaces, &i);

//Remplissage de la liste de points
point3 temp;

for (i=0;i<nbsommets;i++)
{
    fscanf(fichier,"%lf %lf %lf\n",&temp.x,&temp.y,&temp.z);
	if (min.x>temp.x)
		min.x=temp.x;
	if (min.y>temp.y)
		min.y=temp.y;
	if (min.z>temp.z)
		min.z=temp.z;

	if (max.x<temp.x)
		max.x=temp.x;
	if (max.y<temp.y)
		max.y=temp.y;
	if (max.z<temp.z)
		max.z=temp.z;

	lpoints.push_back(temp);

	/////////////////
	//Ajout du nombre de case max (qui correspond au nombre de sommets)
	somparfaces.push_back(std::deque<point3>());
	////////////////

}


//Remplissage de la liste de faces
iFaceTri ftemp;

for (i=0;i<nbfaces;i++)
{
   fscanf(fichier,"%u %u %u %u\n",&n, &ftemp.s0, &ftemp.s1,&ftemp.s2);
	if (n!=3) {
		perror("Erreur au chargement des faces, non triangulaires");
		exit(1);
		}
	lifaces.push_back(ftemp);
}


//calcul du centroid de l'objet à partir de la boîte min/max
centroid.x = (max.x + min.x) / 2.0f;
centroid.y = (max.y + min.y) / 2.0f;
centroid.z = (max.z + min.z) / 2.0f;

std::cerr << "Chargement du fichier " << nom_fichier << std::endl;
std::cerr << "\t" << nom_fichier << " : " << nbsommets << " points - " << nbfaces << " faces" << std::endl;
std::cerr << "\t" << nom_fichier << " MAX : " << max.x << " " << max.y << " " << max.z << std::endl;
std::cerr << "\t" << nom_fichier << " MIN : " << min.x << " " << min.y << " " << min.z << std::endl;
std::cerr << "\t" << nom_fichier << " CENTROID : " << centroid.x << " " << centroid.y << " " << centroid.z << std::endl;

fclose(fichier);
}


void Objet::infos()
{
   std::cerr << "Objet " << nom << ", nbsommets " << nbsommets << " nbfaces " << nbfaces << "\n";

	std::cerr << "\n SOMMETS\n";
	std::deque<point3>::iterator pit, pitend = lpoints.end();

	for( pit = lpoints.begin(); pit != pitend; ++pit)
		std::cerr << "[" << (*pit).x << " " << (*pit).y << " " << (*pit).z << "]\n";

	std::cerr << "\n FACES\n";
	std::deque<iFaceTri>::iterator fit, fitend = lifaces.end();

	for(fit = lifaces.begin() ; fit != fitend ; ++fit)
		std::cerr << "{" << (*fit).s0 << " " << (*fit).s1 << " " << (*fit).s2 << "}\n";
}
