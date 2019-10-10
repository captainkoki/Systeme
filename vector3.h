#ifndef _VECTOR3_H
#define _VECTOR3_H


class point3;

/*! \class vector3
* \bug nil
* \warning nil
* \version 1.0
*/

class vector3 {
public:
	double      x;
	double      y;
	double      z;

	vector3();  // (0,0,0) par defaut
	vector3(const double&,const double&,const double&);
	vector3(const point3&);
	vector3(const point3&, const point3&);
    vector3(const vector3&);
    ~vector3();

	int         operator==(const vector3 &op)const;
	vector3&    operator=(const vector3 &op);
	vector3&    operator=(const point3 &op);
	vector3     operator+()const;
	vector3     operator+(const vector3 &)const;
	vector3     operator+(const point3 &)const;

	vector3&    operator+=(const vector3 &op);
	vector3     operator-()const;
	vector3     operator-(const vector3 &op)const;
	vector3&    operator-=(const vector3 &op);
	vector3&    operator*=(const double op); //produit par un scalaire
	vector3     operator*(const double op)const; //idem
	vector3&    operator/=(const double op); //division par un scalaire
	vector3     operator/(const double op)const; //idem
	double      operator*(const vector3 &op)const; //produit scalaire
	vector3&    operator^=(const vector3 &op); //produit vectoriel
	vector3     operator^(const vector3 &op)const;

	vector3     normalize(const  double lg); //normalise un vecteur a la longueur lg
	double      length(); //longueur du vecteur
};

#endif
