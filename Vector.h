#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"

template<typename T>
class Vector : Matrix<T> {
private:
	int length_;
	T* p_;	//pointor to data
public:
	Vector() :length_(3),Matrix<T>(3,1) { 
		cout << "default Vector constructor" << endl;
		//cout << this->sizeX_ << endl; 
	}
};
	/*
	Vector();	//default constructor
	Vector(int length, T init = 1);
	Vector(const Vector& orig);
	~Vector();//deconstructor
	Vector& operator= (const Vector& rhs);
	T& operator()(int loc)const;
	Vector& operator+=(const Vector& rhs);// operator +=
	Vector& operator-=(const Vector& rhs);
	Vector& operator*=(const Vector& rhs);
	friend Vector operator+<T>(const Vector& lhs, const Vector& rhs);// operator +
	friend Vector operator-<T>(const Vector& lhs, const Vector& rhs);//operator -
	friend Vector operator*<T>(const Vector& lhs, const Vector& rhs);// operator *
	  ???? template<typename T> friend ostream& operator<<(ostream &os, const Vector<T>& rhs);//operator <<
	  friend bool operator== <T>(const Vector& lhs, const Vector& rhs);//operator==
	  friend bool operator!= <T>(const Vector& lhs, const Vector& rhs);//operator!=

	
	*/

#endif // !VECTOR_H