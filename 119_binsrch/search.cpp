#include <cstdlib>
#include <iostream>

#include "function.h"
#include <assert.h>

#include <cmath>
#include <cstdio>

// class CountedIntFn : public Function<int,int> {
// protected:
//   unsigned remaining;
//   Function<int,int> * f;
//   const char * mesg;
// public:
//   CountedIntFn(unsigned n, Function<int,int> * fn, const char * m)://a constructor, passes in the maximum invocations allowed, the Function used in computation, auxiliary sentence, help to check if computation times is over maximum invocations allowed
//     remaining(n),
//     f(fn),
// 	mesg(m) {}
//   virtual int invoke(int arg) {
//     if (remaining == 0) {
//       fprintf(stderr,"Too many function invocations in %s\n", mesg);
//       exit(EXIT_FAILURE);
//     }
//     remaining--;
//     return f->invoke(arg);
//   }
// };

// int binarySearchForZero(Function<int, int> * f, int low, int high);

// class SinFunction : public Function<int, int> {
// public:
//   virtual int invoke(int arg) {
//     return 10000000 * (sin(arg/100000.0) - 0.5);
//   }
// };

// class PropFunc : public Function<int, int> {
// public:
//   virtual int invoke(int arg) {
//     return arg;
//   }    
// };


// void check(Function<int,int> * f, int low, int high, int expected_ans, const char * mesg) {
//     size_t maxInvo;
//     if (high > low) {
//         maxInvo = log2(high - low) + 1;
//     }
//     else {
//         maxInvo = 1;
//     }

//     CountedIntFn * countCheck = new CountedIntFn(maxInvo, f, mesg);//check if binary search is completed in maximum invocation times

//     int ans = binarySearchForZero(countCheck, low, high);//check if binary search is even right //???is it OK to just pass in SinFunction rather than coutCheck???
    
//     if (ans != expected_ans) {
//         std::cerr << "function answer does not match expected answer" << std::endl;
//         exit(EXIT_FAILURE);
//     }
//     delete countCheck;
// }

// int main() {
//     SinFunction * sf = new SinFunction();//???is invoke() a default constructor? no constructor in Function or SinFuction???
//     //answer: no, but there is an implicit default constructor in every class that you don't have to write explicitly
//     PropFunc * pf = new PropFunc(); 
//     check(sf, 0, 150000, 52359, "Sinfunction\n");

//     check(pf, -3, -1, -2, "all negative\n");
//     check(pf, 1, 3, 1, "all postive\n");
//     check(pf, -1, 4, 0, "0 is 0\n");//-1 1 0 to -1 4 0 solve the problem
//     check(pf, 0, 1, 0, "0 is low\n");
//     check(pf, -1, 0, -1, "0 is high\n");
//     check(pf, -2, -2, -2, "low is high, but negative");
//     check(pf, 1, 1, 1, "low is high, but positive\n");
//     check(pf, 0, 0, 0, "low is hight, but 0\n");
//     delete sf;
//     delete pf;
//     return EXIT_SUCCESS;
// }



int binarySearchForZero(Function<int, int> * f, int low, int high) {
    int LOW = low;
    int HIGH = high;
    int MID;
    int FX;
    if (LOW == HIGH) {
        return LOW;
    }
    if (f->invoke(LOW) >= 0) {
        return LOW;
    }
    if (f->invoke(HIGH - 1) <= 0) {
        return (HIGH - 1);
    }

    while (LOW <= HIGH) {
        MID = (LOW + HIGH) / 2;
        FX = f->invoke(MID);
        if (FX > 0) {
            HIGH = MID - 1;
        }
        else if (FX < 0) {
            LOW = MID + 1;
        }
        else {
            return MID;
        }
    }

    if (FX < 0) {
        return MID;
    }
    if (FX > 0) {
        return (MID - 1);
    }

    return 0;
}

