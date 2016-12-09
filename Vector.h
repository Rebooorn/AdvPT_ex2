#pragma once

#include "Matrix.h"
#include "math.h"
#include <functional>		

template<typename T, size_t rows, size_t cols> class Matrix;
template<typename T, size_t lengths> class Vector;
template<typename T, size_t rows, size_t cols> class Stencil;
template<typename T, size_t lengths> Vector<T, lengths> operator+ (const Vector<T, lengths>& lhs, const Vector<T, lengths>& rhs);
template<typename T, size_t lengths> Vector<T, lengths> operator- (const Vector<T, lengths>& lhs, const Vector<T, lengths>& rhs);


template<typename T, size_t lengths>
class Vector : public Matrix<T, lengths, 1> {
private:
	int length_;
	T init_;
	//T* pp_;	//pointor to data
public:
	friend class Matrix<T, lengths, 1>;
	friend class Matrix <T, lengths, lengths>;
	friend class Stencil<T, lengths, 1>;
	friend class Stencil<T, lengths, lengths>;
	Vector();
	Vector(int length , T init = 1); //define by length, ;
	Vector(const Vector& orig);		//define from another Vector
	Vector(int length, std::function<T*(int)> f);	//functional constructor
	~Vector();		//deconstructor;

	Vector& operator=(const Vector&);
	Vector& operator=(const Matrix<T, lengths, 1>&);
	friend Vector operator+<T> (const Vector&, const Vector&);
	friend Vector operator-<T> (const Vector&, const Vector&);
	T& operator()(int)const;
	double l2Norm()const;
	int size()const;
};


template<typename T, size_t lengths>
Vector<T, lengths>::Vector():length_(4),Matrix<T>(4,1){} //default constructor

template<typename T, size_t lengths>
Vector<T, lengths>::Vector(int length,T init):
	length_(length),
	Matrix<T, lengths, 1>(length,1,init){} //assign constructor

template<typename T, size_t lengths>
Vector<T, lengths>::Vector(const Vector<T, lengths>& orig):
	length_(orig.length_)
 {	//define by another vector
	this->p_ = new T[length_];
	this->sizeX_ = length_;
	this->sizeY_ = 1;
	for (int i = 0;i < length_;i++) {
		this->p_[i] = orig.p_[i];
	}
}

template<typename T, size_t lengths>
Vector<T, lengths>::Vector(int length, std::function<T*(int)> f) :
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

template<typename T, size_t lengths>
Vector<T, lengths>::~Vector() {	// p_ will be deleted by ~Matrix()
	//delete[] this->p_;
}


template<typename T, size_t lengths>
Vector<T, lengths>& Vector<T, lengths>::operator= (const Vector<T, lengths>& rhs){
	length_ = rhs.length_;
	this->sizeX_ = length_;
    this->p_=new T[length_];
	for (int i = 0; i < this->sizeX_*this->sizeY_;i++) {
		(this->p_)[i] = rhs.p_[i];
	}
    return *this;
}

template<typename T, size_t lengths>
Vector<T, lengths>& Vector<T, lengths>::operator= (const Matrix<T, lengths, 1>& rhs) {
	assert(rhs.sizeY_ == 1);
	length_ = rhs.sizeX_;
	this->p_ = new T[length_];
	for (int i = 0;i < length_;i++) {
		this->p_[i] = rhs.p_[i];
	}
	return *this;
}

template<typename T, size_t lengths>
Vector<T, lengths> operator+(const Vector<T, lengths>& lhs, const Vector<T, lengths>& rhs) {
	assert(lhs.length_ == rhs.length_);
	Vector<T, lengths> tmp(lhs.length_, 0.0);
	for (int i = 0;i < tmp.length_;i++) {
		tmp.p_[i] = lhs.p_[i] + rhs.p_[i];
	}
	return tmp;
}

template<typename T, size_t lengths>
Vector<T, lengths> operator-(const Vector<T, lengths>& lhs, const Vector<T, lengths>& rhs) {
	assert(lhs.length_ == rhs.length_);
	Vector<T, lengths> tmp(lhs.length_, 0.0);
	for (int i = 0;i < tmp.length_;i++) {
		tmp.p_[i] = lhs.p_[i] - rhs.p_[i];
	}
	return tmp;
}

template<typename T, size_t lengths>
T& Vector<T, lengths>::operator()(int index)const {
	return this->p_[index];
}

template<typename T, size_t lengths>
double Vector<T, lengths>::l2Norm() const {	//calculate l^2 norm
	double norm = 0;
	for (int i = 0;i < length_;i++) {
		norm += this->p_[i] * this->p_[i];
	}
	return sqrt(norm);
}

template<typename T, size_t lengths>
int Vector<T, lengths>::size()const {
	return length_;
}

