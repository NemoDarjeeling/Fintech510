#include "IntMatrix.h"

IntMatrix::IntMatrix(): numRows(0), numColumns(0), rows() {}
IntMatrix::IntMatrix(int r, int c): numRows(r), numColumns(c) {//???initialize or assignment???
    rows = new IntArray * [numRows];
    for (int i = 0; i < numRows; i++) {
        rows[i] = new IntArray(numColumns);
    } 
}//动态二维数组法

IntMatrix::IntMatrix(const IntMatrix & rhs): numRows(rhs.numRows), numColumns(rhs.numColumns) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;//复制非数组元素

    rows = new IntArray * [rhs.numRows];
    for (int i = 0; i < numRows; i++) {
        rows[i] = new IntArray(numColumns);
    }//先改造一样多的空

    for (int i = 0; i < rhs.numRows; i++) {
        for (int j = 0; j < rhs.numColumns; j++) {
            (*rows[i])[j] = (*rhs.rows[i])[j];//???same problem???
        }
    }//再往空里填该填的数
}

IntMatrix::~IntMatrix() {
    for (int i = 0; i < numRows; i++) {
        delete rows[i];
    }
    delete []rows;
}

IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
    if (this != &rhs) {
    IntArray ** a = new IntArray * [rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
        a[i] = new IntArray(rhs.numColumns); 
    }//创造和rhs内部一样的结构

    for (int i = 0; i < rhs.numRows; i++) {
        for (int j = 0; j < rhs.numColumns; j++) {
            (*a[i])[j] = (*rhs.rows[i])[j];//???same problem???
        }
    }//深拷贝rhs的内容

    for (int i = 0; i < numRows; i++) {
        delete rows[i];
    }
    delete []rows;//clearing the old “this”

    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = a;
    }
    return *this;
}

int IntMatrix::getRows() const {
    return numRows;
}

int IntMatrix::getColumns() const {
    return numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
    assert(index >= 0);
    assert(index < numRows);
    const IntArray & a = *rows[index];//why I have to add *? rows[index] not enough to have the array?
    return a; 
}

IntArray & IntMatrix::operator[](int index){
    assert(index >= 0);
    assert(index < numRows);
    IntArray & a = *rows[index];
    return a;
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
        return false;
    }
    else {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numColumns; j++) {
                if ((*rows[i])[j] != (*rhs.rows[i])[j]) {//???same problem???
                    return false;
                } 
            }
        }
        return true;
    }
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
    assert(numRows == rhs.numRows);
    assert(numColumns == rhs.numColumns);
    IntMatrix a(numRows, numColumns); 
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            (*a.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];//a[]does not call the function I wrote?？？same problem???
        }
    }
    a.numRows = numRows;
    a.numColumns = numColumns;
    return a;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
    s << "[ ";
    for (int i = 0; i < rhs.IntMatrix::getRows(); i++) {
        s << rhs[i];//???why is it working???
        if (i != rhs.IntMatrix::getRows() - 1) {
            s << ",\n";
        }
    }
    s << " ]";
    return s;
}
