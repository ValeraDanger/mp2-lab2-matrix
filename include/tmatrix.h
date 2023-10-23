// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 1000000;
const int MAX_MATRIX_SIZE = 1000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size is too large");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    if (arr == nullptr) {
        throw ("TDynamicVector requires non-nullptr arg");
    }
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      this->sz = v.sz;
      this->pMem = new T[this->sz];
      for (size_t i = 0; i < this->sz; i++) {
          this->pMem[i] = v.pMem[i];
      }
  }

  ~TDynamicVector()
  {
      delete[] this->pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this->pMem != v.pMem) {
          if (this->sz != v.sz) {
              delete[] this->pMem;
              this->sz = v.sz;
              this->pMem = new T[v.sz];
          }
          for (size_t i = 0; i < v.sz; i++) {
              this->pMem[i] = v.pMem[i];
          }
      }

      return *this;
  }

  size_t size() const noexcept { 
      return sz; 
  }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }


  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this->sz != v.sz) {
          return false;
      }

      for (size_t i = 0; i < this->sz; i++) {
          if ((*this)[i] != v[i]) {
              return false;
          }
      }

      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = (*this)[i] + val;
      }

      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = (*this)[i] - val;
      }

      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = (*this)[i] * val;
      }

      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (this->sz != v.sz) {
          throw std::length_error("Vectors' sizes not equal");
      }
      TDynamicVector res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = (*this)[i] + v[i];
      }

      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (this->sz != v.sz) {
          throw std::length_error("Vectors' sizes not equal");
      }
      TDynamicVector res(this->sz);
      for (size_t i = 0; i < v.sz; i++) {
          res[i] = (*this)[i] - v[i];
      }

      return res;
  }
  T operator*(const TDynamicVector& v) 
  {
      if (this->sz != v.sz) {
          throw std::length_error("Vectors' sizes not equal");
      }
      T res = 0;
      for (size_t i = 0; i < v.sz; i++) {
          res += (*this)[i] * v[i];
      }

      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << '\t'; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1)
  {
      if (s > MAX_MATRIX_SIZE) {
          throw "Too large matrix size";
      }
      this->sz = s;
      this->pMem = new TDynamicVector<T>[this->sz];
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = TDynamicVector<T>(this->sz);
      }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  TDynamicMatrix& operator=(const TDynamicMatrix& v) {
      if (this->pMem != v.pMem) {
          if (this->sz != v.sz) {
              delete[] this->pMem;
              this->sz = v.sz;
              this->pMem = new TDynamicVector<T>[this->sz];
          }
          for (size_t i = 0; i < sz; i++) {
              this->pMem[i] = v.pMem[i];
          }
      }

      return *this;
  }

  size_t size() const noexcept {
      return sz;
  }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this->sz != m.sz) {
          return false;
      }

      for (size_t i = 0; i < this->sz; i++) {
          if ((*this)[i] != m[i]) {
              return false;
          }
      }

      return true;
  }

  bool operator!= (const TDynamicMatrix& m) const noexcept {
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = (*this)[i] * val;
      }
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (this->sz != v.size()) {
          throw std::length_error("Vector and matrix dimensions must be equal");
      }
      TDynamicVector<T> res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          for (size_t j = 0; j < this->sz; j++) {
              res[i] += (*this)[i][j] * v[j];
          }
      }

      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz) {
          throw std::length_error("Vector and matrix dimensions must be equal");
      }
      TDynamicMatrix res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = (*this)[i] + m[i];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz) {
          throw std::length_error("Vector and matrix dimensions must be equal");
      }
      TDynamicMatrix res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          res[i] = (*this)[i] - m[i];
      }

      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz) {
          throw std::length_error("Vector and matrix dimensions must be equal");
      }
      TDynamicMatrix res(this->sz);
      for (size_t i = 0; i < this->sz; i++) {
          for (size_t j = 0; j < this->sz; j++) {
              res[i][j] = 0;
              for (size_t k = 0; k < this->sz; k++) {
                  res[i][j] += (*this)[i][k] * m[k][j];
              }
          }

      }

      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++)
          istr >> m[i]; // требуется оператор>> для типа T
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++)
          ostr << m[i] << endl; // требуется оператор>> для типа T
      return ostr;
  }
};

#endif
