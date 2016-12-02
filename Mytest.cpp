#include "Vector.h"
#include "Matrix.h"
#include <iostream>

using namespace std;
// for testing programme
void main(){
	Vector<double> v1(2, 1.2);
	Vector<double> v2(3);
	Matrix<double> m1(2, 2, 2);
	Matrix<double> m3;
	v2 = m1*v1;
	cout << v2 << endl;
	cout << "Norm: " << v2.l2Norm() << endl;
	m3 = m1.inverseDiagonal();
	cout << m3 << endl;
	//Matrix<double> m1(3, 4, 1.1);
	//cout << m1 << endl;
	//Matrix<double>* p = &m1;
	
	/*cout << "m1:" << endl;
	cout << m1 << endl;
	cout << "m1+m2=" << endl;
	cout << m1 + m2 << endl;
	*/
}