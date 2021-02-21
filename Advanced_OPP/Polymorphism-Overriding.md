## Polymorphism: Overriding

["Overriding"](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#glossary) a function occurs when :

1. A base class declares a `virtual`function
2. A derived class overrides that virtual function by defining its own implementation with an identical function signature (i.e the same function name and argument types)

```c++
class Animal {
  public:
  virtual std::string Talk() const = 0;
};

class Cat{
  public:
  std::string Talk const { return std::string("Meow"); }
}
```

In this example, `Animal` exposes a `virtual` function: `Talk()`, but does not define it. Because `Animal::Talk()` is undefined, it is called a pure virtual function, as opposed to an ordinary virtual function.

Furthermore, because `Animal` contains a pure virtual function, the user cannot instantiate an object of type `Animal`. This makes `Animal` an abstract class.

`Cat`, however, inherits from `Animal` and override `Animal::Talk()` with `Cat::Talk()`, which is defined Therefore, it is possible to instantiate an object of type `Cat`. 

