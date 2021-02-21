## Operator Overloading

```c++
#include <cassert>
#include <vector>

class Matrix{
  public:
  Matrix(int rows, int columns) : rows_(rows), columns_(columns), values_(rows * columns){}
  
  //Operator Overloading
  //The return type of this function is reference to the int because you want to override the operation to that memorry address
  int& operator()(int row, int column){
    return values_[row * columns_+column];
  }
  // accessor function though, it will just access it.
  int operator()(int row, int column) const {
    return values_[row * columns_+column];
  }
  //More Overloading maybe ?
  Matrix operator+[Matrixm]{}
  
  private:
  int rows_;
  int columns_;
  std::vector<int> values_;
};

int main(){
  Matrix matrix(2,2);
  matrix(0, 0) = 4;
  assert(matrix(0,0) == 4);
}
```

Operator overloading can be useful for many things. Consider the `+` operator. We can use it to add `int`s `double`s `float`s, or even `std::string`s.

In order to overload an operator, use the `operator` keyword in the function signature:

```c++
Complex operator+(const Complex& addend){
  //... logic to add complex number
}
```

Imagine vector addition. You might want to perform vector addition on a pair of points to add their x and y components. The compiler won't recognize this type of operation on its own, because this data is user defined. However, you can overlaod the `+` operator so it performs the action that you want to implement.

```c++
#include <assert.h>

// TODO: Define Point class
class Point {
public:
  // TODO: Define public constructor
  Point(int x = 0, int y = 0) : x(x), y(y) {}

  // TODO: Define + operator overload
  Point operator+(const Point& addend) {
    Point sum;
    sum.x = x + addend.x;
    sum.y = y + addend.y;
    return sum;
  }

  // TODO: Declare attributes x and y
  int x, y;
};

// Test in main()
int main() {
  Point p1(10, 5), p2(2, 4);
  Point p3 = p1 + p2; // An example call to "operator +";
  assert(p3.x == p1.x + p2.x);
  assert(p3.y == p1.y + p2.y);
}
```

