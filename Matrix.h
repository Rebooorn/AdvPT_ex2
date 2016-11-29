#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cassert>

using std::endl;
using std::cout;
using std::ostream;

template<typename T> class Matrix;
template<typename T> Matrix<T> operator+ (const Matrix<T>& lhs, const Matrix<T>& rhs);
template<typename T> Matrix<T> operator- (const Matrix<T>& lhs, const Matrix<T>& rhs);
template<typename T> Matrix<T> operator* (const Matrix<T>& lhs, const Matrix<T>& rhs);
template<typename T> bool operator== (const Matrix<T>& lhs, const Matrix<T>& rhs);
template<typename T> bool operator!= (const Matrix<T>& lhs, const Matrix<T>& rhs);
//template<typename T> ostream& operator<<(ostream &os, const Matrix<T>& rhs);

template<typename T>
class Matrix{
	public:
		//use 1-dimension array to store matrix
		Matrix();// default construct creates a 4*4 matrix of 1;
		Matrix(int sizeX,int sizeY,T init = 1);// assignment constructor
		Matrix(const Matrix& orig);//copy assignment
		~Matrix();//delete constructor
        Matrix& operator=(const Matrix &rhs);//operator =
		T& operator()(int row, int col)const;// return matrix element
        Matrix& operator+=(const Matrix& rhs);// operator +=
		Matrix& operator-=(const Matrix& rhs);
		Matrix& operator*=(const Matrix& rhs);
		friend Matrix operator+<T>(const Matrix& lhs, const Matrix& rhs);// operator +
		friend Matrix operator-<T>(const Matrix& lhs, const Matrix& rhs);//operator -
		friend Matrix operator*<T>(const Matrix& lhs, const Matrix& rhs);// operator *
		 /*????*///friend ostream& operator<< <T>(ostream &os, const Matrix& rhs);//operator <<
		template<typename T> friend ostream& operator<< (ostream& os, const Matrix<T>& rhs);
		friend bool operator== <T>(const Matrix& lhs, const Matrix& rhs);//operator==
		friend bool operator!= <T>(const Matrix& lhs, const Matrix& rhs);//operator!=
		friend T* getbegin(const Matrix& m);
		// output matrix;

	private:
		int sizeX_, sizeY_;
		T init_;
		T* p_;
};

/*
template<typename T>
class Vector : Matrix<T> {
private:
	int length_;
	T* p_;	//pointor to data
public:
	Vector() :length_(1) { cout << "sssss" << endl; };
};
*/

//default constructor
template<typename T>
Matrix<T>::Matrix():sizeX_(4),sizeY_(4),init_(1){
   // cout<< "default constructor"<<endl;
    p_ =new T[sizeX_*sizeY_];
    for(int i=0;i<sizeX_*sizeY_;i++){
        p_[i]= init_;
    }
}

//assignment constructor
template<typename T>
Matrix<T>::Matrix(int sizeX,int sizeY,T init):sizeX_(sizeX),sizeY_(sizeY),init_(init){
   // cout<< "normal constructor"<<endl;
    p_ =new T[sizeX_*sizeY_];
    for(int i=0;i<sizeX_*sizeY_;i++){
        p_[i]= init_;
    }
}
//delete constructor
template<typename T>
Matrix<T>::~Matrix() {
	delete[] p_;
}

//copy assignment
template<typename T>
Matrix<T>::Matrix(const Matrix<T> &orig ):
			sizeX_(orig.sizeX_),
			sizeY_(orig.sizeY_)
{
 //   cout<<"copy constructor"<<endl;
	//p_ = & orig.p_[0];	deadly wrong because orig is delete and orig.p_ is also deleted, *this.p_ and orig.p_ points to same direction
	p_ = new T[orig.sizeX_* orig.sizeY_];
	for (int i = 0;i < sizeX_*sizeY_;i++) {
		p_[i] = orig.p_[i];
	}

}
//operator =
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &rhs){
//    cout<< "copy-assignment operator"<<endl;
    sizeX_= rhs.sizeX_;
    sizeY_= rhs.sizeY_;
	//T* p= p_;
	for (int i = 0; i < sizeX_*sizeY_;i++) {
		p_[i] = rhs.p_[i];
      //  p_++;
	}
	//p_=p;
    return *this;
}
//return element reference
template<typename T>
T& Matrix<T>::operator()(int row, int col)const{
 //   cout<< "element assignment"<<endl;
    return p_[row*sizeY_+col];
}
// operator +=
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs){
//    cout<< "add operation"<<endl;
	assert(sizeX_ == rhs.sizeX_ && sizeY_ == rhs.sizeY_);
    for(int i=0;i<sizeX_;i++){
        for (int j=0;j<sizeY_;j++){
            p_[i*sizeY_+j]=p_[i*sizeY_+j]+rhs.p_[i*sizeY_+j];
        }
    }
    return *this;
}
// operator -=
template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
//	cout << "subtract operation" << endl;
	assert(sizeX_ == rhs.sizeX_ && sizeY_ == rhs.sizeY_);

	T* p = p_;
	T* pr = rhs.p_;

	for (int i = 0;i < sizeX_;i++) {
		for (int j = 0;j < sizeY_;j++) {
			*p -= *pr;
			p++;
			pr++;
		}
	}
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
//	cout << "multiply-self operation";
	assert(sizeX_ == rhs.sizeX_ && sizeY_ != rhs.sizeY_);

	T* p = p_;		//get the initial pointer place
	T* pr = rhs.p_;
	for (int i = 0;i < sizeX_;i++) {
		for (int j = 0;j < sizeY_;j++) {
			*p_ *= *pr;
			p_++;
			pr++;
		}
	}
	p_ = p;
	return *this;
}
// operator +
template<typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs){
// improvement ==> change to pointer

//    cout<< "add operation 2 "<<endl;
	assert(lhs.sizeX_ == rhs.sizeX_ && lhs.sizeY_ == rhs.sizeY_);

    Matrix<T> sum(lhs.sizeX_,lhs.sizeY_);
    for (int i=0;i<lhs.sizeX_;i++){
        for(int j=0;j<lhs.sizeY_;j++){
            sum.p_[i*lhs.sizeY_+j]=lhs.p_[i*lhs.sizeY_+j]+rhs.p_[i*lhs.sizeY_+j];
        }
    }
    return sum;
}
template<typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
//	cout << "substract operation" << endl;
	assert(lhs.sizeX_ == rhs.sizeX_ && lhs.sizeY_ == rhs.sizeY_);

	Matrix<T> tmp = lhs;
	tmp -= rhs;
	return tmp;
}
//operator *
template<typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs){		//pay attention to matrix size
//    cout<< "times operation"<<endl;
	assert(lhs.sizeY_ == rhs.sizeX_);
	T* pl=lhs.p_;	//left operand
    T* pr=rhs.p_;	//right oprand
    Matrix<T> prod(lhs.sizeX_,rhs.sizeY_,0.0);
    T* pt=prod.p_;		//product
    for (int i=0;i<prod.sizeX_;i++){
        for (int j=0;j<prod.sizeY_;j++){
            pl = lhs.p_+i*lhs.sizeY_;    //reset pointor
            pr = rhs.p_+j;
            for(int m=0;m<lhs.sizeY_;m++){
                * pt += (*pl)*(*pr);
                pl++;
                pr+=rhs.sizeY_;
            }
            pt++;
        }
    }
    return prod;
}

template<typename T>
ostream& operator<<(ostream &os, const Matrix<T>& rhs){
//    cout<< "Matrix output"<<endl;
	T* p = rhs.p_;
	for (int i = 0;i < rhs.sizeX_;i++) {
		for (int j = 0;j < rhs.sizeY_;j++) {
			os << *p << " ";
			p++;
		}
		os << endl;
	}
	return os;
}

// matrix identity
template<typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
//	cout << "Matrix compare" << endl;
	assert(lhs.sizeX_ == rhs.sizeX_ && lhs.sizeY_ == rhs.sizeY_);

	T* pl = lhs.p_;
	T* pr = rhs.p_;
	int nx = lhs.sizeX_, ny = lhs.sizeY_;
	bool flag = true;

	for (int i = 0;i < nx*ny;i++) {
		if (*pl != *pr) {
			flag = false;
			break;
		}
		pl++;
		pr++;
	}

	return flag;
}

template<typename T>
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs) {
//	cout << "matrix not equal" << endl;
	return ~(lhs == rhs);
}

// get the data pointer of m
template<typename T>
T* getbegin(const Matrix<T>& m) {
	return m.p_;
}

#endif // !MATRIX_H