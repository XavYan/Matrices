#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <cmath>

template <class T>
class matrix {
    private:
    int m_; //filas
    int n_; //columnas
    std::vector<T> v_;

    public:
    matrix(int m = 0, int n = 0);
    matrix(const matrix<T>& M);
    ~matrix(void);

    //Selectores y asignadores
    T& at (int i, int j);
    const T& at (int i, int j) const;
    int get_m (void);
    int get_n (void);
    void resize (int m, int n);

    //Analisis y operaciones con matrices
    bool is_row (void);
    bool is_column (void);
    bool is_square (void);
    bool is_lower_triangular_matrix (void);
    bool is_upper_triangular_matrix (void);
    bool is_identity (void);
    bool is_null (void);

    //Operaciones con matrices

    matrix<T> operator+ (const matrix<T>& M);
    matrix<T> operator- (const matrix<T>& M);
    matrix<T> operator* (const matrix<T>& M);
    matrix<T> scal_prod (int n);

    matrix<T> transpose (void);
    int minorOf (int i, int j) const;

    int det (void);

    matrix<T> reverse (void);

    //Metodos de flujo E/S
    std::ostream& write (std::ostream& os) const;
    std::istream& read (std::istream& is);

    //Sobrecarga de operadores
    T& operator() (int i, int j);
    const T& operator() (int i, int j) const;
    matrix<T>& operator= (const matrix<T>& M);

    private:

    int pos (int i, int j) const;

    int Sarrus (const matrix<T>& A); //Suponemos que este metodo se accede desde det() y ahi comprobamos que es cuadrada
    int devByMinor (const matrix<T>& A);
};

//Constructores
template <class T>
matrix<T>::matrix(int m, int n) : m_(m), n_(n), v_(m*n) {}

template <class T>
matrix<T>::matrix(const matrix<T>& M) : m_(M.m_), n_(M.n_), v_(M.m_*M.n_) {
    for (int i = 0; i < m_; i++) {
        for (int j = 0; j < n_; j++) {
            at(i,j) = M(i,j);
        }
    }
}

//METODOS PUBLICOS///////////////////////////////////////////////////////////////////////

//Destructor
template <class T>
matrix<T>::~matrix(void) { v_.clear(); }

//Selectores y asignadores
template <class T>
T& matrix<T>::at (int i, int j) {
    return v_[pos(i,j)];
}

template <class T>
const T& matrix<T>::at (int i, int j) const {
    return v_[pos(i,j)];
}

template <class T>
int matrix<T>::get_m() {
   return m_;
}

template <class T>
int matrix<T>::get_n() {
   return n_;
}

template <class T>
void matrix<T>::resize(int m, int n) {
   m_ = m;
   n_ = n;
   v_.resize(m_*n_);
}

//Analisis y operaciones con matrices
template <class T>
bool matrix<T>::is_row(void) {
   return (m_ == 1);
}

template <class T>
bool matrix<T>::is_column(void) {
   return (n_ == 1);
}

template <class T>
bool matrix<T>::is_square(void) {
   return (m_ == n_);
}

template <class T>
bool matrix<T>::is_lower_triangular_matrix(void) {
   if (!is_square()) return false;
   for (int i = 0; i < m_; i++) {
      for (int j  = i+1; j < n_; j++) {
         if (at(i,j) != 0) return false;
      }
   }
   return true;
}

template <class T>
bool matrix<T>::is_upper_triangular_matrix(void) {
   if (!is_square()) return false;
   for (int i = 1; i < m_; i++) {
      for (int j  = 0; j <= i; j++) {
         if (at(i,j) != 0) return false;
      }
   }
   return true;
}

template <class T>
bool matrix<T>::is_identity(void) {
   if (!is_lower_triangular_matrix() || !is_upper_triangular_matrix()) return false;
   for (int i = 0; i < m_; i++) {
      if (at(i,i) != 1) return false;
   }
   return true;
}

template <class T>
bool matrix<T>::is_null(void) {
   for (int i = 0; i < m_; i++) {
      for (int j = 0; j < n_; j++) {
         if (at(i,j) != 0) return false;
      }
   }
   return true;
}

//Operaciones con matrices
template <class T>
matrix<T> matrix<T>::transpose (void) {
    matrix<T> result(n_,m_);
    for (int j = 0; j < n_; j++) {
        for (int i = 0; i < m_; i++) {
            result(i,j) = at(j,i);
        }
    }
    return result;
}

template<class T>
matrix<T> matrix<T>::operator+ (const matrix<T>& M) {
   assert(m_ == M.m_ && n_ == M.n_);
   matrix<T> result(m_,n_);
   for (int i = 0; i < m_; i++) {
      for (int j = 0; j < n_; j++) {
         result(i,j) = at(i,j) + M(i,j);
      }
   }
   return result;
}

template <class T>
matrix<T> matrix<T>::operator- (const matrix<T>& M) {
   assert(m_ == M.m_ && n_ == M.n_);
   matrix<T> result(m_, n_);
   for (int i  = 0; i < m_; i++) {
      for (int j = 0; j < n_; j++) {
         result(i,j) = at(i,j) - M(i,j);
      }
   }
   return result;
}

template <class T>
matrix<T> matrix<T>::operator* (const matrix<T>& M) {
 assert(n_ == M.m_);
 matrix<T> result(m_,M.n_);
 for (int i = 0; i < m_; i++) {
    for (int j = 0; j < M.n_; j++) {
       for (int k = 0; k < n_; k++) {
          result(i,j) += at(i,k) * M(k,j);
       }
    }
 }
 return result;
}

template <class T>
matrix<T> matrix<T>::scal_prod (int n) {
   matrix<T> result(m_,n_);
   for (int i = 0; i < m_; i++) {
      for (int j = 0; j < n_; j++) {
         result(i,j) = at(i,j) * n;
      }
   }
   return result;
}

//Menor de un numero
template <class T>
int matrix<T>::minorOf (int i, int j) const {
    assert(i >= 0 && i < m_ && j >= 0 && j < n_);

    //Creamos la matriz del adjunto
    matrix<T> adj(m_-1,n_-1);

    /*
        Debemos tener en cuenta que un menor es el determinante de
        la matriz que resulte de tachar la fila y la columna de la matriz original.
        Ademas, hay que multiplicarla por ese termino y por -1 elevado a la suma de sus
        posiciones (contando desde 1).
    */

    int k = 0; int s = 0;
    for (int m = 0; m < m_; m++) {
        if (m == i) continue;
        for (int n = 0; n < n_; n++) {
            if (n == j) continue;
            adj(k,s) = at(m,n);
            if (s < adj.n_-1) s++; else { s = 0; k++; }
        }
    }

    int det = adj.det(); //Determinante del adjunto

    int result = pow(-1,(i+1)+(j+1)) * at(i,j) * det; //nuestro resultado

    return result;
}

//Determinante
template <class T>
int matrix<T>::det (void) {
    assert(is_square());

    if (m_ >= 4) return devByMinor(*this);

    return Sarrus(*this);
}

//Inversa
template <class T>
matrix<T> matrix<T>::reverse (void) {

}

//Metodos de flujo E/S
template <class T>
std::ostream& matrix<T>::write (std::ostream& os) const {
    for (int i = 0; i < m_; i++) {
        for (int j = 0; j < n_; j++) {
            os << "[" << std::setw(4) << at(i,j) << "]" << " ";
        }
        os << '\n';
    }
    return os;
}

template <class T>
std::istream& matrix<T>::read (std::istream& is) {
    is >> m_;
    is >> n_;
    v_.resize(m_*n_);
    for (int i = 0; i < m_; i++) {
        for (int j = 0; j < n_; j++) {
            is >> at(i,j);
        }
    }
    return is;
}

//Sobrecarga de operadores

template <class T>
T& matrix<T>::operator() (int i, int j) {
    return at(i,j);
}

template <class T>
const T& matrix<T>::operator() (int i, int j) const {
    return at(i,j);
}

template <class T>
matrix<T>& matrix<T>::operator= (const matrix<T>& M) {
   resize(M.m_, M.n_);
   for (int i = 0; i < m_; i++) {
      for (int j = 0; j < n_; j++) {
         at(i,j) = M(i,j);
      }
   }
   return *this;
}

//METODOS PRIVADOS /////////////////////////////////////////////////////////////////////////

template <class T>
int matrix<T>::pos (int i, int j) const {
   return (i * m_ + j);
}

//Suponemos que este metodo se accede desde det() y ahi
//comprobamos que es cuadrada
template <class T>
int matrix<T>::Sarrus (const matrix<T>& A) {

    assert(m_ < 4);

    if (m_ == 1) return A(0,0);
    if (m_ == 2) return (at(0,0)*at(1,1)-at(0,1)*at(1,0));

    int izq = 0;
    int der = 0;

    int aux = 1;
    //Primero calculamos la diagonal
    for (int i = 0; i < m_; i++) {
        aux *= at(i,i);
    }
    izq = aux;

    //Ahora los extremos
    izq += at(0,1) * at(1,2) * at(2,0);
    izq += at(1,0) * at(2,1) * at(0,2);

    //Diagonal secundaria
    aux = 1;
    for (int i = 0, j = m_-1; i < m_ && j >= 0; i++, j--) {
        aux *= at(i,j);
    }
    der = aux;

    //Extremos
    der += at(0,1) * at(1,0) * at(2,2);
    der += at(1,2) * at(2,1) * at(0,0);

    //Fusionamos
    int result = izq - der;

    return result;
}

template <class T>
int matrix<T>::devByMinor (const matrix<T>& A) {

    int result = 0;
    for (int i = 0; i < A.m_; i++) {
        result += A.minorOf(0,i);
    }
    return result;
}

//METODOS EXTERNOS///////////////////////////////////////////////////////////////////////////////

template <class T>
std::ostream& operator<< (std::ostream& os, const matrix<T>& A) {
    A.write(os);
    return os;
}

template <class T>
std::ostream& operator>> (std::istream& is, const matrix<T>& A) {
    A.read(is);
    return is;
}