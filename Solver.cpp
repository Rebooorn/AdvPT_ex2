#include <iostream>
#include <chrono>
#include <ctime>

//#include "Matrix.h"
#include "Vector.h"
#include "Stencil.h"


#define PI 3.141592653589793

template<typename T>
//void solve (const Matrix<T>& A, const Vector<T>& b, Vector<T>& u) {
void solve(const MatrixLike<T, Stencil<T> >& A, const Vector<T>& b, Vector<T>& u) {
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

void testFullMatrix (const int numGridPoints) {
	const double hx = 1. / (numGridPoints - 1);
	const double hxSq = hx * hx;
	std::chrono::time_point<std::chrono::system_clock> start, end;		//timer start, end


	std::cout << "Starting full matrix solver for " << numGridPoints << " grid points" << std::endl;

	Matrix<double> A(numGridPoints, numGridPoints, 0.);
	Vector<double> u(numGridPoints, 0.);
	Vector<double> b(numGridPoints, 0.);

	A(0, 0) = 1.;
	for (int x = 1; x < numGridPoints - 1; ++x) {
		A(x, x - 1) = 1. / hxSq;
		A(x, x) = -2. / hxSq;
		A(x, x + 1) = 1. / hxSq;
	}
	A(numGridPoints - 1, numGridPoints - 1) = 1.;

	for (int x = 0; x < numGridPoints; ++x) {
		b(x) = sin(2. * PI * (x / (double)(numGridPoints - 1)));
	}
/*
	std::cout << "Initialization complete\n";
	cout << A << endl;
	// TODO: start timing
	start = std::chrono::system_clock::now();
	solve(A, b, u);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = end - start;
	cout << "elapsed time: " << elapsedTime.count() << "s" << endl;
	// TODO: end timing and print elapsed time
	// for primitive methods: size:  17  || 33   || 65    || 129
	//					iteration:	146  || 594  || 2386  || 9553
	//					time:		5.35 || 23.8 || 271.8 || 3715.8  ms
	//Question 1: why elapsed time differs in every run?

	// for improved #1:		  size:  17  || 33   || 65    || 129
	//					iteration:	     ||      ||       ||
	//					time:		     ||      ||       ||         ms
	*/
}

void testStencil (const int numGridPoints) {
	// TODO: add stencil code
	// the stencil can be set up using
	const double hx = 1. / (numGridPoints - 1);
	const double hxSq = hx * hx;
    std::chrono::time_point<std::chrono::system_clock> start, end;		//timer start, end


	std::cout << "Starting full matrix solver for " << numGridPoints << " grid points, using Stencil" << std::endl;

	Stencil<double> ASten( { { 0, 1. } }, { { -1, 1. / hxSq },{ 0, -2. / hxSq },{ 1, 1. / hxSq } });
	Vector<double> u(numGridPoints, 0.);
	Vector<double> b(numGridPoints, 0.);

	ASten.setSize(numGridPoints);
	for (int x = 0; x < numGridPoints; ++x) {
		b(x) = sin(2. * PI * (x / (double)(numGridPoints - 1)));
	}

	std::cout << "Initialization complete\n";
	start = std::chrono::system_clock::now();
	solve(ASten, b, u);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedTime = end - start;
	cout << "elapsed time: " << elapsedTime.count() << "s" << endl;



}

int main(int argc, char** argv) {
	testFullMatrix( 33 );
	testStencil( 33 );

	return 0;
}
