## Passing Variables by Value

```c++
#include <iostream>

void AddTwo(int val){
  val += 2;
}

int main(){
  int val = 0;
  AddTwo(val);
  val += 2;
  
  std::cout << "val = " << val << std::endl;
  return 0;
}
```

When calling a function, its parameters (in this case myInt) are used to create local copies of the information provided by caller. The caller is not sharing the parameter with the function but intead a proprietary copy is created using the assignment operator `=` (more about that later). When passing parameters in such a way, it is ensured that changes made to local copy will not affect the original on the caller side. The upside to this is that inner workings of the function and the data owned by the caller are kept neatly separate. 

However, there are two major downsides to this:

1. Passing parameters by value means that a copy is created, which is an expensive operation that might consume large amounts of memory, depending on the data that is transferred. (Think about "move semantics", which is an effective way to compensate for this downside)
2. Passing by value also means that the created copy can not be used a back channel for communicating with the caller, for example by directly writing the desired information into the variable.

---

Consider the example on the code above. In main, the integer `val` is initialized with 0. When passing it to the function `AddTwo`, so the add-operation has no effect on `val` on the caller side. So when `main`returns, `val`has value of 2 intead of 4. 

However, with a slight modification, we can easily create a backchannel to the caller side. 

Consider the code on the below.

---

```c++
#include <iostream>

void AddThree(int *val){
  *val += 3;
}

int main(){
  int val = 0;
  AddThree(&val);
  val += 2;
  
  std::cout << "val = " << val << std::endl;
  return 0;
}
```

In this case, when passing the parameter to the function `AddThree`, we are creating a local copy as well but note that we are now passing a pointer variable. This means that a copy of the memory address of `val`is created, which we can then use to directly modify its content by using the dereference operator `*`.

## Passing Variables by Reference

The second major way of passing parameters to a function is by reference. With this way, the function receives a reference to the parameter, rather than a copy of its valuue. As with the example of `AddThree` above, the function can now modify the argument such that the changes also happen on the caller side. In addition to the possibility to directly exchange information between function and caller, passing variable by reference is also faster as no information needs to be copied, as well as more memory-efficient.

A major disadvantage is that the caller does not always know what will happen to the data it passes to a function (especially when the function code can not be modified easily). Thus, in some cases, special steps must be taken to protect ones data from inappropriate modification. 

```c++
#include <iostream>
void AddFour(int &val)
{
    val += 4;
}

int main()
{
    int val = 0;
    AddFour(val);
    val += 2;

    std::cout << "val = " << val << std::endl;
 
    return 0;
}
```

To pass a variable by reference, we simply declare the function parameters as references using `&`rather than as normal variables. When the function is called, `val` will become a reference to the argument. Since a reference to a variable is treated exactly the same as the variable itself, any changes made to the reference are passed through to the argument.

---

An additional advantage of passing variables by reference is the possibility to modify several variables. When using the function return value for such a purpose, returning several variables is usually very cumbersome. 

```c++
void AddFive(int &val, bool& success){
  val += 5;
  success = true;
}
```



## Pointers vs References.

As we have seen in the examples above, the use of pointers and references to directly manipulate function arguments in a memory-effective way is very similar.

```c++
#include <iostream>

void AddFour(int &val)
{
    val += 4;
}

void AddSix(int *val)
{
    *val += 6; 
}

int main()
{
    int val = 0;
    AddFour(val);
    AddSix(&val);

    std::cout << "val = " << val << std::endl;
 
    return 0;
}
```



As can be seen, pointer and reference are both implemented by using a memory address. In the case of `AddFour` the caller does not even realize that `val` might be modified while with `AddSix`, the reference to `val` has to be explicitly writting by using `&` 

If passing by value needs to be avoided, both pointers and references are a way to achieve this. The following selection of properties contrasts the two methods so it will be easier to decide which to use from the perspective of the use-case at hand:

* Pointers can be declared without initialization. This means we can pass an uninitialized pointer to a function who then internally performs the initialization for us
* Pointers can be reassigned to another memory block on the heap
* References are usually easier to use (depending on the expertise level of the programmer). Sometimes however, if a third-party function is used without properly looking at the parameter definition, it might go unnoticed that a value has been modified.

```c++
#include <stdio.h>
    
void CallByValue(int i)
{
    int j = 1; 
    printf ("call-by-value: %p\n",&j);
}

void CallByPointer(int *i)
{
    int j = 1; 
    printf ("call-by-pointer: %p\n",&j);
}

void CallByReference(int &i)
{
    int j = 1; 
    printf ("call-by-reference: %p\n",&j);
}

int main()
{
    int i = 0;
    printf ("stack bottom: %p\n",&i);
    
    CallByValue(i);

    CallByPointer(&i);

    CallByReference(i);

    return 0;
}
```

After creating a local variable `i` in `main` to give us the address of the stack bottom, we are passing i by-value to our first function. Inside `CallByValue`, the memory address of a local variable `j` is printed to the console, which serves as a marker for the stack pointer. With the second function call in`main`, we are passing a reference to `i` to `CallByPointer`. Lastly, the function `CallByReference` is called in main, which again takes the integer `i` as an argument. However, from looking at `main` alone, we can not tell wether `i` will be passed by value or by reference. 