#ifndef _POINT3_H
#define _POINT3_H

#include <iostream>

class vector3;

/******************* point3 ******************/

class point3{
public:
	double x;
	double y;
	double z;

	point3();  // (0,0,0) par defaut
	point3(const double X,const double Y,const double Z);
    point3(const point3&);
	point3( const vector3 & );
    ~point3();

    bool        operator==(const point3 &)const;
	point3&     operator=(const point3 &);
	point3&     operator=(const vector3 &);

	point3      operator+(const vector3 &)const; //equivalent a une translation
	point3      operator+(const point3 &)const;
	point3&     operator+=(const vector3 &); //pareil
	point3		operator-(const point3 &)const; //definition d'un vecteur
	point3&     operator*=(const double); //produit par un scalaire (a peu pres une homothetie)
	point3      operator*(const double)const; //idem
	point3&     operator/=(const double); //division par un scalaire (a peu pres une homothetie)
	point3      operator/(const double)const; //idem
	point3      operator*(const point3 &)const;
	point3&     operator*=(const point3 &); //pareil :)
	point3      operator/(const point3 &)const; //pareil :)
	point3&     operator/=(const point3 &); //pareil :)

	void Permutation(point3 *, point3 *); // Permutation de deux points
	friend std::ostream&  operator<<(std::ostream&, const point3&);
	friend std::istream&  operator>>(std::istream&, point3 &);
};

#endif