#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray(): data(NULL), numElements(0) {}

IntArray::IntArray(int n): data(new int[n]), numElements(n) {}

IntArray::IntArray(const IntArray & rhs) {
    numElements = rhs.numElements;
//is it possible to initialize this->data and this->numElements here? yes it is.
    data = new int[rhs.numElements];//先把空给分配的一样多
    for (int i = 0; i < numElements; i++) {
        data[i] = rhs.data[i];//再往空里填该填的数
    }
}

IntArray::~IntArray() {
    delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
    if (this != &rhs) {
        int * a = new int[rhs.numElements];
        int num = rhs.numElements;
        for (int i = 0; i < num; i++) {
            a[i] = rhs.data[i];
        }
        delete[] data; //clear the original this->data
        numElements = rhs.numElements;
        data = a;
    }
    return *this;
}

const int & IntArray::operator[](int index) const {//The first one specifies the return value is a constant reference and as such the object it points to cannot be changed.  The one at the end identifies the function as "accessor" with no modification to the current object.
    assert (index >= 0);//assert里面写对的，错的才会被捕获
    assert (index < numElements);//check if index is in bounds
    const int & a = data[index];
    return a;
}

int & IntArray::operator[](int index) {
    assert (index >= 0);
    assert (index < numElements);//check if index is in bounds
    int & a = data[index];
    return a;    
}

int IntArray::size() const {
    return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
    if (numElements != rhs.numElements) {
        return false;
    }
    else {
        for (int i = 0; i < numElements; i++) {
            if (data[i] != rhs.data[i]) {
                return false;
            }
        }
        return true;
    }
}

bool IntArray::operator!=(const IntArray & rhs) const {//or just return !(*this == rhs)
    if (numElements != rhs.numElements) {
        return true;
    }
    else {
        for (int i = 0; i < numElements; i++) {
            if (data[i] != rhs.data[i]) {
                return true;
            }
        }
        return false;
    }    
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {//you don't have IntArray here, so you can not go into rhs to get numElements
    s << "{";//means print output into s, while s will output all into screen
    for (int i = 0; i < rhs.IntArray::size(); i++) {//use .size() to get the length of the array, why? you have wrote for it!
        s << rhs[i];//this is a overloading of int & IntArray::operator[](int index), so you can use it go get the number with index in IntArray & rhs
        if (i != rhs.IntArray::size() - 1) {
            s << ", ";
        }
    }
    s << "}";
    return s;
}
