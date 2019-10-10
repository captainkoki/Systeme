#include <iostream>
#include <cstdlib>

#include "objetsOFF.h"

using namespace std;


int main()
{
	Objet monObjet;
		monObjet.charge_OFF("can1k5.off");

		monObjet.calculNormalface();

		monObjet.calculNormalsommet();
		
		monObjet.infoNormS();

	return(EXIT_SUCCESS);
}
