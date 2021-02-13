## Polymorphism

Polymorphism is means "assuming many forms".

In the context of object-oriented programming, [Polymorephism](https://en.wikipedia.org/wiki/Polymorphism_(computer_science)) describes a paradigm in which a function may behave differently depending on how it is called. In particular, the function will perform differently based on its inputs. 

Polymorphyism can be achieved in tow ways in C++: overloading and overriding. 

## Overloading

 in C++, you can **write to (ore more) version of a function with the same name**. This is called ["Overloading"](https://en.wikipedia.org/wiki/Function_overloading). Overloading requires that we leave the function name the same, but **we modify the function signature.** For example, we might define the same function name with multiple different configuration of input arguments.

This example of  `class Date` overloads:

```c++
#include <ctime>
class Date {
  public:
  // Consturctor. 
  Date(int day, int month, int year) : day_(day), month_(month), year_(year) {}
    
  Date(int day, int month) : day_(day), month_(month) // automatically sets the date to the current year
  {
  	time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    year_ = timePtr->tm_year
  }
  
 private:
  int day_;
  int month_;
  int year_;
}
```

Another Example

```c++
#include <cassert>
#include <string>

//Declare the classes
class Water {};
class Alcohol {};
class Coffee {};

class Human{
  public:
  	std::string condition("happy");
  	void Drink(Water water){ condition = "hydrated"; }
  	//Function Overload
  	void Drink(Alcohol alcohol){ condition = "impaired"; }
  	//Function Overload
  	void Drink(Coffee coffee){ condition = "focus"; }
  	
};

int main(){
  Human nick;
  assert(nick.condition == "happy");
  nick.Drink(Water());
  assert(nick.condition == "hydrated");
  nick.Drink(Alcohol());
  assert(nick.condition == "impaired");
  nick.Drink(Coffee());
  assert(nick.condition == "focus");
}
```

Last Example

```c++
#include <iostream>

class Human {};
class Dog {};
class Cat {};

// TODO: Write hello() function
void hello() { std::cout << "Hello, World!\n"; }

// TODO: Overload hello() three times
void hello(Human human) { std::cout << "Hello, Human!\n"; }
void hello(Dog dog) { std::cout << "Hello, Dog!\n"; }
void hello(Cat cat) { std::cout << "Hello, Cat!\n"; }

// TODO: Call hello() from main()
int main()
{
    hello();
    hello(Human());
    hello(Dog());
    hello(Cat());
}
```

