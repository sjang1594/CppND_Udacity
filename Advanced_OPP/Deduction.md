## Deduction.

["Deduction"](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rt-deduce) : Occurs when you instantiate an object without explicitly identifying the type. Instead, the complier "deduces" the types. This can be helpful or writing code that is generic and can handle a variety of inputs

```c++
#include <cassert>
#include <string>
#include <vector>

template <Typename T>
T Max(T a, T b){
  return a > b ? a : b;
}

int main(){
  assert(Max(2,4) == 4);
  assert(Max(-1.0, -2.3) == -1.0);
  
  std::vector<int> v(1, 2, 3);
  assert(v.size() == 3);
  
  //can we eliminate this ?
  std::vector v(1,2,3);
  
  // Use g++ -std=c++17 template.cpp
  //then compiler will deduce the type.
}
```

