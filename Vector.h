#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"

template<typename T>
class Vector : public Matrix<T> {
private:
	int length_;
	//T* pp_;	//pointor to data
public:
	Vector();
	Vector(int);
	Vector& operator=(const Vector& rhs);
};


template<typename T>
Vector<T>::Vector():length_(4),Matrix<T>(4,1){} //default constructor

template<typename T>
Vector<T>::Vector(int length):length_(length),Matrix<T>(length,1){} //assign constructor


template<typename T>
Vector<T>& Vector<T>::operator= (const Vector<T>& rhs){
    this->sizeX_=rhs.sizeX_;
    this->sizeY_=rhs.sizeY_;
    this->p_=new double[this->sizeX_*this->sizeY_];
	for (int i = 0; i < this->sizeX_*this->sizeY_;i++) {
		(this->p_)[i] = rhs.p_[i];
	}
    return *this;
}

    // default constructor, create a 3*1 matrix

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
