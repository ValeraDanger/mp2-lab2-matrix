// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
  TDynamicMatrix<int> a(5), b(5), c(5);
  int i, j;
  c;
  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами"
    << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;


  TDynamicMatrix<int> m1(3);
  TDynamicVector<int> v(3);
  for (size_t i = 0; i < 3; i++) {
	  v[i] = i;
  }
  for (size_t i = 0; i < 3; i++) {
	  m1[i] = v;
  }

  cout << m1 << endl;

  m1 = m1 * m1;

  cout << m1 << endl;
}
//---------------------------------------------------------------------------
