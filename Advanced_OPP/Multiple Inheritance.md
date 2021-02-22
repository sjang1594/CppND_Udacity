## Multiple Inheritance 

If you have class `Animal` and another class `pet`, then you can construct a class `dog`, which inherits from both of these base classes. In doing this, you are able to incorporate attributes of multiple base classes.

The core Guidelines have some worthwhile recommendations about how and when to use multiple inheritance:

* ["Use multiple inheritance to represent multiple distinct interfaces"](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c135-use-multiple-inheritance-to-represent-multiple-distinct-interfaces)
* ["Use multiple inheritance to represent the union of implementation attributes"](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c136-use-multiple-inheritance-to-represent-the-union-of-implementation-attributes)

```c++
#include <cassert>
#include <iostream>

class car{
  public:
  std::string Drive(){ return "I am driving"; }
}

class Boat{
  public:
  std::string Cruise(){ return "I am cruising"; }
}

// Multiple Inheritance
class AmphibiousCar : public Boat, public car {};

int main(){
  Car car;
  Boat boat;
  AmphibiousCar duck;
  
  assert(duck.Drive() == car.Drive());
  assert(duck.Cruise() == boat.Cruise());
}
```

```c++
#include <iostream>
#include <string>
#include <assert.h>

class Animal {
public:
    double age;
};

class Pet {
public:
    std::string name;
};

// Dog derives from *both* Animal and Pet
class Dog : public Animal, public Pet {
public:
    std::string breed;
};

class Cat : public Animal, public Pet {
public:
    std::string color;
};

int main()
{
    Cat cat;
    cat.color = "black";
    cat.age = 10;
    cat.name = "Max";
    assert(cat.color == "black");
    assert(cat.age == 10);
    assert(cat.name == "Max");
}
```

