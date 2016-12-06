#pragma once

#include <cassert>
#include <utility> //std::swap
#include <algorithm> // std::find_if
#include <vector>

#include "MatrixLike.h"

template<typename T>
using StencilEntry = std::pair<int, T>; // convenience type for stencil entries

template<typename T>
class Stencil: public MatrixLike< T,Stencil<T> > /* TODO: inherit MatrixLike */ {
public:
	Stencil(const std::vector<StencilEntry<T> >& boundaryEntries, const std::vector<StencilEntry<T> >& innerEntries)
		: boundaryStencil_(boundaryEntries), innerStencil_(innerEntries) { }
	Stencil(const std::vector<StencilEntry<T> >& innerEntries)	// c'tor for stencils w/o explicit boundary handling
		: boundaryStencil_(innerEntries), innerStencil_(innerEntries) { }

	Stencil(const Stencil & o);
	Stencil(Stencil && o) noexcept;

	~Stencil( ) noexcept override { }

	Stencil& operator=(const Stencil & o);
	Stencil& operator=(Stencil && o) noexcept;

	// HINT: stencil entries are stored as offset/coefficient pair, that is the offset specifies which element of a
	// vector, relative to the current index, is to be regarded. It is then multiplied with the according coefficient.
	// All of these expressions are evaluated and then summed up to get the final result.
	Vector<T> operator* (const Vector<T> & o) const override;
	T& operator() (int, int)override;
	const T& operator() (int, int)const override;


	Stencil<T> inverseDiagonal( ) const override;

	void setSize(int);


protected:
	// containers for the stencil entries -> boundary stencils represent the first and last rows of a corresponding
	// matrix and are to be applied to the first and last element of a target vector; inner stencils correspond to
	// the remaining rows of the matrix
	std::vector<StencilEntry<T> > boundaryStencil_;	// feel free to change the datatype if convenient
	std::vector<StencilEntry<T> > innerStencil_;	// feel free to change the datatype if convenient
	int size_;      //matrix size
	double rest_ =0;    //rest zeros;
};

template<typename T>
Stencil<T>::Stencil(const Stencil &o)
	:boundaryStencil_(o.boundaryStencil_),innerStencil_(o.innerStencil_){}

template<typename T>
Stencil<T>::Stencil(Stencil &&o)noexcept
	:boundaryStencil_(o.boundaryStencil_),innerStencil_(o.innerStencil_){}


template<typename T>        //operator ()
const T& Stencil<T>::operator() (int row, int col)const {
	if (row == 0 && col == 0) return boundaryStencil_[0].second;
	else if (row == size_-1 && col == size_-1) return boundaryStencil_[0].second;
	else if (row == col) return innerStencil_[1].second;
	else if (row == col+1) return innerStencil_[0].second;
    else if (row == col-1) return innerStencil_[2].second;
    else return rest_;
}


template<typename T>        //operator () #2
T& Stencil<T>::operator() (int row, int col) {

	if (row == 0 && col == 0) return boundaryStencil_[0].second;
	else if (row == size_-1 && col == size_-1) return boundaryStencil_[0].second;
	else if (row == col) return innerStencil_[1].second;
	else if (row == col+1) return innerStencil_[0].second;
    else if (row == col-1) return innerStencil_[2].second;
    else return rest_;
}


template<typename T>
Vector<T> Stencil<T>::operator* (const Vector<T>& rhs) const{
    //assert(size_==rhs.length_);
    Vector<T> res(size_,0.);
    res.p_[0]=rhs.p_[0]*boundaryStencil_[0].second;
    rhs.p_[size_-1]=rhs.p_[size_-1]*boundaryStencil_[0].second;
    for (int i=1;i<rhs.length_-1;i++){
        res.p_[i]=rhs.p_[i-1]*innerStencil_[0].second+rhs.p_[i]*innerStencil_[1].second+rhs.p_[i+1]*innerStencil_[2].second;
    }
    return res;
}

template<typename T>
Stencil<T> Stencil<T>::inverseDiagonal() const{
    Stencil<T> tmp( {{0,1.}},{{0, 1.0/this->innerStencil_[1].second}} );
    tmp.setSize(size_);
    return tmp;

}

template<typename T>
void Stencil<T>::setSize(int s){
    size_=s;
}
