#include <cstdlib>
#include <sstream>
#include <string>

class Expression {//a abstract method
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {//a subclass of Expression, in which we have a number
  long number;

 public:
  NumExpression(long n) : number(n) {}//convert the number into string
  virtual std::string toString() const {//overload toString(), used to convert a number into string
    std::stringstream sstream;
    sstream << number;
    return sstream.str();//returns the pointer to the beginning of the buffer, after freezing it
  }
  virtual ~NumExpression() {}
};

class OpExpression : public Expression {//create a operating expression, which is a subclass of expression, in which we have a operator and two expressions of numbers
  const char * op;
  Expression * lhs;
  Expression * rhs;

 public:
  OpExpression(const char * op, Expression * lhs, Expression * rhs): op(op), lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {//overload toString(), used to convert the expression function (such as 1 + 2, 1 - 2) into strings
    std::stringstream sstream;
    sstream << '(' << lhs->toString() << ' ' << *op << ' ' << rhs->toString() << ')';
    return sstream.str();
  }
  virtual ~OpExpression() {
  delete lhs;
  delete rhs;
  }
};

class PlusExpression : public OpExpression {//create a plus expression, which is a subclass of operating expression, only we specify it to "plus"
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression("+", lhs, rhs) {}
};// ~PlusExpression(){}?