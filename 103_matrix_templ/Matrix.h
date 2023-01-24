#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;
 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix & rhs);
  //~Matrix();//vector will do the job
  Matrix<T> & operator=(const Matrix<T> & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix<T> & rhs) const;
  Matrix<T> operator+(const Matrix<T> & rhs) const;//what is Martix<T> & and what changes should be made?
  
  template<typename U>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<U> & rhs);
};

template<typename T>
Matrix<T>::Matrix(): numRows(0), numColumns(0), rows() {}//和正常一样的声明是哪个class，但是因为type T所以要说明是T

template<typename T>
Matrix<T>::Matrix(int r, int c): numRows(r), numColumns(c) {
    rows.resize(r);//resize each row
    for(typename std::vector<std::vector<T> >::iterator it = rows.begin(); it != rows.end(); ++it) {
        (*it).resize(c); //resize each column
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;//复制非数组元素
    rows = rhs.rows;//vector has = copy function
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
    return *this;//因为要求返回一个Matrix<T> & 类型的，那就给你来个*this
}

template<typename T>
int Matrix<T>::getRows() const {
    return numRows;
}

template<typename T>
int Matrix<T>::getColumns() const {
    return numColumns;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
    assert(index >= 0);
    assert(index < numRows);
    const std::vector<T> & a = rows[index];//no need to dereference
    return a;
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
    assert(index >= 0);
    assert(index < numRows);
    std::vector<T> & a = rows[index];//no need to dereference
    return a;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
        return false;
    }
    else {
        if (rows != rhs.rows) {
            return false;
        }
        else {
            return true;
        }
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
    assert(numRows == rhs.numRows);
    assert(numColumns == rhs.numColumns);
    Matrix<T> a(numRows, numColumns);//initialize a to store the result
    // std::vector<std::vector<T> >::iterator y;
    // for (y = a.begin(); y != a.end(); ++y) {
    //     std::vector<T>::iterator x;
    //     for (x = (*y).begin(); x != (*y).end(); ++x) {
    //         *x += 
    //     }
    // }
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            a.rows[i][j] = this->rows[i][j] + rhs.rows[i][j];//a[]does not call the function I wrote?？？same problem???
        }
    }
    return a;
}


// IntMatrix IntMatrix::operator+(const IntMatrix &rhs) const {
//  assert(numColumns == rhs.getColumns() && numRows == rhs.getRows());
//  IntMatrix temp(numRows,numColumns); /////
//  for (int i = 0; i < numRows; i++) {
//  for (int j = 0; j < numColumns; j++) {
//  temp[i][j] = (*this->rows[i])[j] + rhs[i][j]; 
//  }
//  }
//  return temp;
// }


template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {//如果想要声明这个可变类的变量，还是要Matrix<T>
  s << "[ ";
  typename std::vector<std::vector<T> >::const_iterator it;
  for (it = rhs.rows.begin(); it != rhs.rows.end(); ++it) {
    if (it != rhs.rows.begin()) {
      s << ",\n";
    }
    s << "{";
    typename std::vector<T>::const_iterator it_it;
    for (it_it = (*it).begin(); it_it != (*it).end(); ++it_it) {
      if (it_it != (*it).begin()) {
        s << ", ";
      }
      s << *it_it;
    }
    s << "}";
  }
  s << " ]";
  return s;
}




#endif
