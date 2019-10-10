#ifndef _H_OBJETSOFF
#define _H_OBJETSOFF

#include <deque>
#include <cmath>

#include "point3.h"
#include "iFaceTri.h"

class Objet {

  public :
	char nom[40];

	unsigned int nbsommets;
	unsigned int nbfaces;

	unsigned int id;

	std::deque<point3> lpoints;
	std::deque<iFaceTri> lifaces;

	/////////////cm
	std::deque<point3> NormFace;
	std::deque<point3> NormSommet;
	std::deque<std::deque<point3>> somparfaces;
	////////////

	point3 min;
	point3 max;
	point3 centroid;

	Objet();
	Objet(const Objet&);
	~Objet();

	/////////////////////////////////////cm

	void calculNormalface();
	void calculNormalsommet();

	void infoNormF();
	void infoNormS();
	////////////////////////////////////


	void charge_OFF(const char nom_fichier[40]);

	void infos();

};

#endif
