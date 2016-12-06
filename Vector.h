#pragma once

#include "Matrix.h"

template<typename T> class Matrix;
template<typename T> class Vector;
template<typename T> Vector<T> operator+ (const Vector<T>& lhs, const Vector<T>& rhs);
template<typename T> Vector<T> operator- (const Vector<T>& lhs, const Vector<T>& rhs);


template<typename T>
class Vector : public Matrix<T> {
private:
	int length_;
	T init_;
	//T* pp_;	//pointor to data
public:
	friend class Matrix<T>;
	Vector();
	Vector(int length , T init = 1); //define by length, ;
	Vector(const Vector& orig);		//define from another Vector
	~Vector();		//deconstructor;
	
	Vector& operator=(const Vector&);
	Vector& operator=(const Matrix&);
	friend Vector operator+<T> (const Vector&, const Vector&);
	friend Vector operator-<T> (const Vector&, const Vector&);
	T& operator()(int)const;
	double l2Norm()const;
	int size()const;
};


template<typename T>
Vector<T>::Vector():length_(4),Matrix<T>(4,1){} //default constructor

template<typename T>
Vector<T>::Vector(int length,T init):
	length_(length),
	Matrix<T>(length,1,init){} //assign constructor

template<typename T>
Vector<T>::Vector(const Vector<T>& orig):
	length_(orig.length_)
{	//define by another vector
	this->p_ = new T[length_];
	sizeX_ = length_;
	sizeY_ = 1;
	for (int i = 0;i < length_;i++) {
		this->p_[i] = orig.p_[i];
	}
}

template<typename T>
Vector<T>::~Vector() {	// p_ will be deleted by ~Matrix()
	//delete[] this->p_;
}


template<typename T>
Vector<T>& Vector<T>::operator= (const Vector<T>& rhs){
	length_ = rhs.length_;
	sizeX_ = length_;
    this->p_=new T[length_];
	for (int i = 0; i < this->sizeX_*this->sizeY_;i++) {
		(this->p_)[i] = rhs.p_[i];
	}
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator= (const Matrix<T>& rhs) {
	assert(rhs.sizeY_ == 1);
	length_ = rhs.sizeX_;
	this->p_ = new T[length_];
	for (int i = 0;i < length_;i++) {
		this->p_[i] = rhs.p_[i];
	}
	return *this;
}

template<typename T>
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
	assert(lhs.length_ == rhs.length_);
	Vector<T> tmp(lhs.length_, 0.0);
	for (int i = 0;i < tmp.length_;i++) {
		tmp.p_[i] = lhs.p_[i] + rhs.p_[i];
	}
	return tmp;
}

template<typename T>
Vector<T> operator-(const Vector<T>& lhs, const Vector<T>& rhs) {
	assert(lhs.length_ == rhs.length_);
	Vector<T> tmp(lhs.length_, 0.0);
	for (int i = 0;i < tmp.length_;i++) {
		tmp.p_[i] = lhs.p_[i] - rhs.p_[i];
	}
	return tmp;
}

template<typename T>
T& Vector<T>::operator()(int index)const {
	return this->p_[index];
}

template<typename T>
double Vector<T>::l2Norm() const {	//calculate l^2 norm
	double norm = 0;
	for (int i = 0;i < length_;i++) {
		norm += p_[i] * p_[i];
	}
	return sqrt(norm);
}

template<typename T>
int Vector<T>::size()const {
	return length_;
}

