#include "Pyramid.h"
#include <cassert>

//Testing
int main(){
    //Instantiate class
    Pyramid pyramid(4, 5, 6);
    assert(pyramid.Length() == 4);
    assert(pyramid.Width() == 5);
    assert(pyramid.Height() == 6);
    assert(pyramid.Volume() == 40);

    //Initialize the flags
    bool caught{false};
    try {
        Pyramid invalid(-1, 2, 3);
    }
    //Catch Everything
    catch(...){
        caught = true;
    }
    assert(caught);
}