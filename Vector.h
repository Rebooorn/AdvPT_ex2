#pragma once

#include "Matrix.h"
#include "math.h"
#include <functional>		

template<typename T, size_t rows, size_t cols> class Matrix;
template<typename T, size_t lengths> class Vector;
template<typename T> class Stencil;
template<typename T> Vector<T> operator+ (const Vector<T>& lhs, const Vector<T>& rhs);
template<typename T> Vector<T> operator- (const Vector<T>& lhs, const Vector<T>& rhs);


template<typename T, size_t lengths>
class Vector : public Matrix<T, lengths, 1> {
private:
	int length_;
	T init_;
	//T* pp_;	//pointor to data
public:
	friend class Matrix<T>;
	friend class Stencil<T>;
	Vector();
	Vector(int length , T init = 1); //define by length, ;
	Vector(const Vector& orig);		//define from another Vector
	Vector(int length, std::function<T*(int)> f);	//functional constructor
	~Vector();		//deconstructor;

	Vector& operator=(const Vector&);
	Vector& operator=(const Matrix<T>&);
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
	this->sizeX_ = length_;
	this->sizeY_ = 1;
	for (int i = 0;i < length_;i++) {
		this->p_[i] = orig.p_[i];
	}
}

template<typename T>
Vector<T>::Vector(int length, std::function<T*(int)> f) :
	length_(length)
{
	T* p = f(length_);
	this->p_ = new T[length_];
	this->sizeX_ = length_;
	this->sizeY_ = 1;
	for (int i = 0;i < length_;i++) {
		this->p_[i] = p[i];
	}
}

template<typename T>
Vector<T>::~Vector() {	// p_ will be deleted by ~Matrix()
	//delete[] this->p_;
}


template<typename T>
Vector<T>& Vector<T>::operator= (const Vector<T>& rhs){
	length_ = rhs.length_;
	this->sizeX_ = length_;
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
		norm += this->p_[i] * this->p_[i];
	}
	return sqrt(norm);
}

template<typename T>
int Vector<T>::size()const {
	return length_;
}

