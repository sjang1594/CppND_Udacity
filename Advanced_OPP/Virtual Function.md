## Virtual Functions 

Virtual functions are a polymorephic feature these functions are declared (and possibly defined ) in a base class, and can be overriden by derived classes.

This approach declares an [Interface](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-glossary) at the base level, but delegates the implementation of the interface to the derived classes.

```c++
// Class Shape is the base class.
// Area() & Perimeter() should be virtual functions of the base class interface. Append = 0 to each of these functions in order to declare them to be "pure" virtual functions. 

// If you use the virtual function, that means that any inherrited classes have to define the virtual function. 
class Shape{
  public:
  Shape() {}
  virtual double Area() const = 0;
  virtual double Perimeter() const = 0;
}
```

A "pure virtual function" is a virtual function that the base class declares but does not define.

A pure virtual function has the side effect of making its class abstract. This means that the class cannot be instantiated. Instead, only classes that derive from the abstract class and override the pure virtual fucntion can be instantiated. 

Virtual functions can be defined by derived classes, but this is not required. However, if we mark the virtual function with `=0` in the bas class, then we are declaring the function to be a pure virtual function. This means that the base class does not define this function. A derived class must define this function, or else the derived class will be abstract. 

```c++
#include <iostream>

class Animal{
  virtual void Talk() const = 0
};

class Human : public Animal{
  void Talk() const override{
    std::cout << "Hello \n";
  }
};

int main(){
  // this will give an error that we can't declare a variable animal to be of type Animal. This is because the following virtual functions are pure within animal, the talk function. That means that animal is purely abstract class and we're not able to create objects of type animal
  Animal animal;
  Human human;
  human.Talk();
}
```

```c++
// Example solution for Shape inheritance
#include <assert.h>
#include <cmath>

// TODO: Define pi
#define PI 3.14159;

// TODO: Define the abstract class Shape
class Shape {
public:
  // Define public virtual functions Area() and Perimeter()
  // Append the declarations with = 0 to specify pure virtual functions
  virtual double Area() const = 0;
  virtual double Perimeter() const = 0;
};

// TODO: Define Rectangle to inherit publicly from Shape
class Rectangle : public Shape {
public:
  // TODO: Declare public constructor
  Rectangle(double w, double h) {
    Rectangle::width_ = w;
    Rectangle::height_ = h;
  }
  // TODO: Override virtual base class functions Area() and Perimeter()
  double Area() const override { return width_ * height_; }
  double Perimeter() const override { return 2 * (width_ + height_); }

private:
  // TODO: Declare private attributes width and height
  double width_;
  double height_;
};

// TODO: Define Circle to inherit from Shape
class Circle : public Shape {
public:
  // TODO: Declare public constructor
  Circle(double r) { radius_ = r; }
  // TODO: Override virtual base class functions Area() and Perimeter()
  double Area() const override { return pow(radius_, 2) * PI; }
  double Perimeter() const override { return 2 * radius_ * PI; }

private:
  // TODO: Declare private member variable radius
  double radius_;
};

// Test in main()
int main() {
  double epsilon = 0.1; // useful for floating point equality

  // Test circle
  Circle circle(12.31);
  assert(abs(circle.Perimeter() - 77.35) < epsilon);
  assert(abs(circle.Area() - 476.06) < epsilon);

  // Test rectangle
  Rectangle rectangle(10, 6);
  assert(rectangle.Perimeter() == 32);
  assert(rectangle.Area() == 60);
}
```

