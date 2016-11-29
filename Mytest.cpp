#include "Matrix.h"
#include "Vector.h"
#include <iostream>

using namespace std;
// for testing programme
void main(){
	Matrix<double> m1(2, 2, 2.1);
	Matrix<double> m2(2, 2, 1.1);
	//Vector<int> r;
	cout << m1 << endl;
	//Matrix<double>* p = &m1;
	
	/*cout << "m1:" << endl;
	cout << m1 << endl;
	cout << "m1+m2=" << endl;
	cout << m1 + m2 << endl;
	*/
}