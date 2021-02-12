## Composition

[Composition]{https://en.wikipedia.org/wiki/Composition_over_inheritance} is a closely related alternative to inheritance. Composition involves constructing(`composing`) classes from other classes, instead of inheriting traits from a parent class. 

A common way to distinguish "composition" from "inheritance" is to think about what an object can do, rather than what it is. This is often expressed as "has a" versus "is a"

**From the standpoint of composition, a cat "has a" head and "has a" set of paws and "has a" tail.**

**From the standpoint of inheritance, a cat "is a" mammal**

There is [no hard and fast rule]{https://stackoverflow.com/questions/49002/prefer-composition-over-inheritance#:~:text=You%20should%20use%20inheritance%20when,has%20some%20relationship%20to%20them} about when to prefer composition over inheritance. In general, if a class needs only extend a small amount of functionality beyond what is already offered by another class, it makes sense to **inherit** from that other class. However, if a class needs to contain functionality from a variety of otherwise unrelated classes, it makes sense to **compose** the class from those other classes.

---

