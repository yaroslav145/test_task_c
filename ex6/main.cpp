#include <iostream>

#include "VectMat.h"

using namespace std;

int main()
{
    Vector3<int> y(7, -3, 1);
    Vector3<int> u(7, -3, 1);
    cout << (y == u) << endl;
    cout << (y != u) << endl << endl;

    Vector3<int> v1(2, 0, 0);
    Vector3<int> v2(0, 3, 0);
    cout << v1 << endl;
    cout << v2 << endl;
    cout << v1 + v2 << endl;
    cout << v1 - v2 << endl;
    cout << v1 - v2*2 << endl;
    cout << v1.cross(v2) << endl;
    cout << v1.dot(v2) << endl << endl;


    Matrix<int> m1(9,3,5,2,0,3,0,1,-6);
    Matrix<int> m2(1,-1,-1,-1,4,7,8,1,-1);
    m1 *= m2;
    cout << m1 << endl << endl;


    Matrix<double> m3(1,2,3,4,5,6,7,8,9);
    Matrix<double> m4(0,3,4,5,6,7,8,1,0);
    m4(0, 0) = -0.5;
    m4(2, 2) = 3.3;
    m3 *= m4 + m1;
    cout << m3 << endl << endl;;

    Matrix<int> A(9,8,7,6,5,4,3,2,54);
    Vector3<double> v(4, 3, 9);
    Vector3<int> t(7, 14, 6);
    Matrix<double> B;
    Vector3<int> h;
    cout << A*v+t << endl << endl;
    convertAVTtoBH(A, v, t, B, h);
    cout << B << endl << h << endl << endl;


    Matrix<int> m5(1,2,3,4,5,6,7,8,9);
    Matrix<double> m6(1,2,3,4,5,6,7,8,9);
    cout << (m5 == m6) << endl;
    cout << (m5 != m6) << endl;
    m6(2, 1) = 15;
    cout << (m5 == m6) << endl;
    cout << (m5 != m6) << endl;


    return 0;
}
