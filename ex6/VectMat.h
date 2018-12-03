#ifndef VECTMAT_H_INCLUDED
#define VECTMAT_H_INCLUDED

#include <iostream>

using namespace std;


template<typename T>
class Vector3;


template<typename T>
ostream& operator << (ostream& os, const Vector3<T>& v)
{
    os << v.x << " " << v.y << " " << v.z;

    return os;
}


template<typename T>
class Vector3
{
    public:
        T x, y, z;

        Vector3();
        Vector3(Vector3<T>& v);
        Vector3(T _x, T _y, T _z);


        T& operator () (const int id);

        template<typename A>
        Vector3<T>& operator = (const Vector3<A>& v);

        template<typename A>
        bool operator == (const Vector3<A>& v);

        template<typename A>
        bool operator != (const Vector3<A>& v);

        template<typename A>
        Vector3<T> operator + (const Vector3<A>& v);


        template<typename A>
        Vector3<T>& operator += (const Vector3<A>& v);


        template<typename A>
        Vector3<T> operator - (const Vector3<A>& v);


        template<typename A>
        Vector3<T>& operator -= (const Vector3<A>& v);


        template<typename A>
        Vector3<T> operator * (const A k);


        template<typename A>
        Vector3<T>& operator *= (const A k);


        template<typename A>
        Vector3<T> operator / (const A k);


        template<typename A>
        Vector3<T>& operator /= (const A k);


        template<typename A>
        double dot(const Vector3<A>& v);


        template<typename A>
        Vector3<T> cross(const Vector3<A>& v);


        friend ostream& operator << <T>(ostream& os, const Vector3<T>& v);
};


const int rowsn = 3;
const int colsn = 3;
const int mSize = rowsn*colsn;

template<typename T>
class Matrix;


template<typename T>
ostream& operator << (ostream& os, const Matrix<T>& m)
{
    for(int i = 0; i < rowsn; ++i)
    {
        for(int j = 0; j < colsn; ++j)
        {
            os << m.matr[i][j] << "  ";
        }
        os << endl;
    }

    return os;
}



template<typename T>
class Matrix
{
    public:
        T matr[rowsn][colsn] = {0,0,0,0,0,0,0,0,0};

        Matrix();

        template<typename A>
        Matrix(Matrix<A>& m);


        Matrix(T m0, T m1, T m2, T m3, T m4, T m5, T m6, T m7, T m8);


        T& operator () (const int id1, const int id2);


        template<typename A>
        Matrix<T>& operator = (const Matrix<A>& m);


        template<typename A>
        bool operator == (const Matrix<A>& m);


        template<typename A>
        bool operator != (const Matrix<A>& m);


        template<typename A>
        Matrix<T> operator + (const Matrix<A>& m);


        template<typename A>
        Matrix<T>& operator += (const Matrix<A>& m);


        template<typename A>
        Matrix<T> operator - (const Matrix<A>& m);


        template<typename A>
        Matrix<T>& operator -= (const Matrix<A>& m);


        template<typename A>
        Matrix<T> operator * (const A k);


        template<typename A>
        Matrix<T> operator * (const Matrix<A>& m);


        template<typename A>
        Vector3<T> operator * (Vector3<A>& v);


        template<typename A>
        Matrix<T>& operator *= (const A k);


        template<typename A>
        Matrix<T>& operator *= (const Matrix<A>& m);


        template<typename A>
        Matrix<T> operator / (const A k);


        template<typename A>
        Matrix<T>& operator /= (const A k);


        friend ostream& operator << <T>(ostream& os, const Matrix<T>& v);
};


template<typename T, typename T1, typename T2, typename T3, typename T4>
void convertAVTtoBH(Matrix<T> A, Vector3<T1> v, Vector3<T2> t, Matrix<T3>& B, Vector3<T4>& h);






template<typename T>
Vector3<T>::Vector3() : x(0), y(0), z(0) {}

template<typename T>
Vector3<T>::Vector3(Vector3<T>& v) : x(v.x), y(v.y), z(v.z) {}

template<typename T>
Vector3<T>::Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}


template<typename T>
T& Vector3<T>::operator () (const int id)
{
    if(id == 0)
        return this->x;

    if(id == 1)
        return this->y;

    if(id == 2)
        return this->z;
}


template<typename T>
template<typename A>
Vector3<T>& Vector3<T>::operator = (const Vector3<A>& v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    return *this;
}


template<typename T>
template<typename A>
bool Vector3<T>::operator == (const Vector3<A>& v)
{
    return (this->x == v.x) && (this->y == v.y) && (this->z == v.z);
}


template<typename T>
template<typename A>
bool Vector3<T>::operator != (const Vector3<A>& v)
{
    return (this->x != v.x) && (this->y != v.y) && (this->z != v.z);
}


template<typename T>
template<typename A>
Vector3<T> Vector3<T>::operator + (const Vector3<A>& v)
{
    Vector3<T> temp;
    temp.x = this->x + v.x;
    temp.y = this->y + v.y;
    temp.z = this->z + v.z;
    return temp;
}


template<typename T>
template<typename A>
Vector3<T>& Vector3<T>::operator += (const Vector3<A>& v)
{
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
    return *this;
}

template<typename T>
template<typename A>
Vector3<T> Vector3<T>::operator - (const Vector3<A>& v)
{
    Vector3<T> temp;
    temp.x = this->x - v.x;
    temp.y = this->y - v.y;
    temp.z = this->z - v.z;
    return temp;
}

template<typename T>
template<typename A>
Vector3<T>& Vector3<T>::operator -= (const Vector3<A>& v)
{
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
    return *this;
}

template<typename T>
template<typename A>
Vector3<T> Vector3<T>::operator * (const A k)
{
    Vector3<T> temp;
    temp.x = this->x * k;
    temp.y = this->y * k;
    temp.z = this->z * k;
    return temp;
}

template<typename T>
template<typename A>
Vector3<T>& Vector3<T>::operator *= (const A k)
{
    this->x *= k;
    this->y *= k;
    this->z *= k;
    return *this;
}

template<typename T>
template<typename A>
Vector3<T> Vector3<T>::operator / (const A k)
{
    Vector3<T> temp;
    temp.x = this->x / k;
    temp.y = this->y / k;
    temp.z = this->z / k;
    return temp;
}

template<typename T>
template<typename A>
Vector3<T>& Vector3<T>::operator /= (const A k)
{
    this->x /= k;
    this->y /= k;
    this->z /= k;
    return *this;
}

template<typename T>
template<typename A>
double Vector3<T>::dot(const Vector3<A>& v)
{
    return this->x*v.x + this->y*v.y + this->z*v.z;
}

template<typename T>
template<typename A>
Vector3<T> Vector3<T>::cross(const Vector3<A>& v)
{
    Vector3<T> temp;
    temp.x = this->y * v.z - this->z * v.y;
    temp.y = this->z * v.x - this->x * v.z;
    temp.z = this->x * v.y - this->y * v.x;
    return temp;
}







template<typename T>
Matrix<T>::Matrix() {}


template<typename T>
template<typename A>
Matrix<T>::Matrix(Matrix<A>& m)
{
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            this->matr[i][j] = m.matr[i][j];
}


template<typename T>
Matrix<T>::Matrix(T m0, T m1, T m2, T m3, T m4, T m5, T m6, T m7, T m8)
{
    this->matr[0][0] = m0;
    this->matr[0][1] = m1;
    this->matr[0][2] = m2;
    this->matr[1][0] = m3;
    this->matr[1][1] = m4;
    this->matr[1][2] = m5;
    this->matr[2][0] = m6;
    this->matr[2][1] = m7;
    this->matr[2][2] = m8;
}


template<typename T>
T& Matrix<T>::operator () (const int id1, const int id2)
{
    if(id1 < rowsn)
        if(id2 < colsn)
            return this->matr[id1][id2];
}


template<typename T>
template<typename A>
Matrix<T>& Matrix<T>::operator = (const Matrix<A>& m)
{
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            this->matr[i][j] = m.matr[i][j];

    return *this;
}


template<typename T>
template<typename A>
bool Matrix<T>::operator == (const Matrix<A>& m)
{
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            if(this->matr[i][j] != m.matr[i][j])
                return false;

    return true;
}


template<typename T>
template<typename A>
bool Matrix<T>::operator != (const Matrix<A>& m)
{
    return !(*this == m);
}



template<typename T>
template<typename A>
Matrix<T> Matrix<T>::operator + (const Matrix<A>& m)
{
    Matrix<T> temp;
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            temp.matr[i][j] = this->matr[i][j] + m.matr[i][j];

    return temp;
}


template<typename T>
template<typename A>
Matrix<T>& Matrix<T>::operator += (const Matrix<A>& m)
{
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            this->matr[i][j] += m.matr[i][j];

    return *this;
}


template<typename T>
template<typename A>
Matrix<T> Matrix<T>::operator - (const Matrix<A>& m)
{
    Matrix<T> temp;
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            temp.matr[i][j] = this->matr[i][j] - m.matr[i][j];

    return temp;
}


template<typename T>
template<typename A>
Matrix<T>& Matrix<T>::operator -= (const Matrix<A>& m)
{
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            this->matr[i][j] -= m.matr[i][j];

    return *this;
}


template<typename T>
template<typename A>
Matrix<T> Matrix<T>::operator * (const A k)
{
    Matrix<T> temp;
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            temp.matr[i][j] = this->matr[i][j] * k;

    return temp;
}


template<typename T>
template<typename A>
Matrix<T> Matrix<T>::operator * (const Matrix<A>& m)
{
    Matrix<T> temp;
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            for(int k = 0; k < rowsn; ++k)
                temp.matr[i][j] += this->matr[i][k] * m.matr[k][j];

    return temp;
}


template<typename T>
template<typename A>
Vector3<T> Matrix<T>::operator * (Vector3<A>& v)
{
    Vector3<T> temp;
    for(int i = 0; i < colsn; ++i)
        for(int j = 0; j < rowsn; ++j)
                temp(i) += this->matr[i][j] * v(j);

    return temp;
}


template<typename T>
template<typename A>
Matrix<T>& Matrix<T>::operator *= (const A k)
{
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            this->matr[i][j] *= k;

    return *this;
}


template<typename T>
template<typename A>
Matrix<T>& Matrix<T>::operator *= (const Matrix<A>& m)
{
    Matrix<T> temp;

    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            for(int k = 0; k < rowsn; ++k)
                temp.matr[i][j] += this->matr[i][k] * m.matr[k][j];

    *this = temp;
    return *this;
}


template<typename T>
template<typename A>
Matrix<T> Matrix<T>::operator / (const A k)
{
    Matrix<T> temp;
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            temp.matr[i][j] = this->matr[i][j] / k;

    return temp;
}


template<typename T>
template<typename A>
Matrix<T>& Matrix<T>::operator /= (const A k)
{
    for(int i = 0; i < rowsn; ++i)
        for(int j = 0; j < colsn; ++j)
            this->matr[i][j] /= k;

    return *this;
}


template<typename T, typename T1, typename T2, typename T3, typename T4>
void convertAVTtoBH(Matrix<T> A, Vector3<T1> v, Vector3<T2> t, Matrix<T3>& B, Vector3<T4>& h)
{
    t = A*v+t;

    h(0) = 1;
    h(1) = 0;
    h(2) = 0;

    B(0, 0) = t(0);
    B(1, 0) = t(1);
    B(2, 0) = t(2);
}



#endif // VECTMAT_H_INCLUDED
