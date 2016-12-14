#include <iostream>
#include <chrono>
#include <ctime>

//#include "Matrix.h"
#include "Vector.h"
#include "Stencil.h"
#include <functional>


#define PI 3.141592653589793

template<typename T, class Derived, size_t numPoints>
//void solve (const Matrix<T>& A, const Vector<T>& b, Vector<T>& u) {
void solve(const MatrixLike<T, Derived, numPoints, numPoints >& A, const Vector<T, numPoints>& b, Vector<T, numPoints>& u) {
	const size_t numGridPoints = u.size( );
	double initRes = (b - A * u).l2Norm( ); // determine the initial residual
	double curRes = initRes;
	std::cout << "Initial residual:\t\t" << initRes << std::endl;

	unsigned int curIt = 0; // store the current iteration index

	while (curRes > 1.e-5 * initRes) { // solve until the residual is reduced by a certain amount
		++curIt;

		u += A.inverseDiagonal( ) * (b - A * u); // Jacobi step

		curRes = (b - A * u).l2Norm( ); // update the residual

		if (0 == curIt % 500) // print some info every few steps
			std::cout << "Residual after iteration " << curIt << ":\t" << curRes << std::endl;
	}

	std::cout << "Residual after iteration " << curIt << ":\t" << curRes << std::endl << std::endl; // print the final number of iterations and the final residual
}

template<size_t numPoints>
void testFullMatrix (/*const int numGridPoints*/) {
	//const double hx = 1. / (numGridPoints - 1);
	const double hx = 1. / (numPoints - 1);
	const double hxSq = hx * hx;
	std::chrono::time_point<std::chrono::system_clock> start, end;		//timer start, end
	

	std::cout << "Starting full matrix solver for " << numPoints << " grid points" << std::endl;

	Matrix<double, numPoints, numPoints> A(0.);
	Vector<double, numPoints> u(numPoints, 0.);
	//Vector<double> b(numGridPoints, 0.);
	//use std::function to construct b
	Vector<double, numPoints> b(numPoints, [](int length) {
		double* p = new double[length];
		for (int x = 0; x < length; ++x) {
			 p[x]= sin(2. * PI * (x / (double)(length - 1)));
		}
		return p;
	});


	A(0, 0) = 1.;
	for (int x = 1; x < numPoints - 1; ++x) {
		A(x, x - 1) = 1. / hxSq;
		A(x, x) = -2. / hxSq;
		A(x, x + 1) = 1. / hxSq;
	}
	A(numPoints - 1, numPoints - 1) = 1.;

	//for (int x = 0; x < numGridPoints; ++x) {
	//	b(x) = sin(2. * PI * (x / (double)(numGridPoints - 1)));
	//}

	std::cout << "Initialization complete\n";
	//cout << A << endl;
	// TODO: start timing
	start = std::chrono::system_clock::now();
	solve(A, b, u);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = end - start;
	cout << "elapsed time: " << elapsedTime.count() << "s" << endl;
	// TODO: end timing and print elapsed time
	// for primitive methods: size:  17  || 33   || 65    || 129
	//					iteration:	146  || 594  || 2386  || 9553
	//					time:		0.016|| 0.19 || 2.48  || 38.31  s
	//Question 1: why elapsed time differs in every run?

	// for improved #1:		  size:  17  || 33   || 65    || 129
	//					iteration:	146  || 594  || 2386  || 9553
	//					time:		0.016|| 0.09 || 0.53  || 3.79   s
	
}

template<size_t numPoints>
void testStencil (/*const int numGridPoints*/) {
	// TODO: add stencil code
	// the stencil can be set up using
	const double hx = 1. / (numPoints - 1);
	const double hxSq = hx * hx;
    std::chrono::time_point<std::chrono::system_clock> start, end;		//timer start, end


	std::cout << "Starting full matrix solver for " << numPoints << " grid points, using Stencil" << std::endl;

	Stencil<double, numPoints, numPoints> ASten( { { 0, 1. } }, { { -1, 1. / hxSq },{ 0, -2. / hxSq },{ 1, 1. / hxSq } });
	Vector<double, numPoints> u(numPoints, 0.);
	Vector<double, numPoints> b(numPoints, 0.);

	ASten.setSize(numPoints);
	for (int x = 0; x < numPoints; ++x) {
		b(x) = sin(2. * PI * (x / (double)(numPoints - 1)));
	}

	std::cout << "Initialization complete\n";
	start = std::chrono::system_clock::now();
	solve(ASten, b, u);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = end - start;
	cout << "elapsed time: " << elapsedTime.count() << "s" << endl;



}

int main(int argc, char** argv) {
	//testFullMatrix<17>();
	testStencil<17>( );
	//testFullMatrix<33>();
	testStencil<33>();
	//testFullMatrix<65>();
	testStencil<65>();
	//testFullMatrix<129>();
	testStencil<129>();

	return 0;
}
