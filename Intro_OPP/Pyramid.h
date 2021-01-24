#include <stdexcept>
#ifndef PYRAMID_H
#define PYRAMID_H


class Pyramid {
public:
    //Constructor
    //Using Initializer Lists.
    Pyramid(int length, int width, int height): length_(length), width_(width), height_(height){
        Validate();
    }

    //accessors
    // Using const because they are designed not to change the interior state of an object and they
    // often just return a private member variable but by channeling access to that private member variable
    // through a public accessor function.

    // "Const" : Accessors should only retrieve data. They should not change the data stored in the object
    // The main role of the "const" specifier in accessor methods is to protect member data. When you
    // specify a member function as const, the compiler will prohibit that function from changing any of the
    // object's member data

    int Length() const { return length_;}
    int Width() const { return width_;}
    int Height() const{ return height_;}

    void Length(int length){
        length_ = length;
        Validate();
    }

    void Width(int width){
        width_ = width;
        Validate();
    }

    void Height(int height){
        height_ = height;
        Validate();
    }

    //Since it's calculating the pyramid volume.
    float Volume() const {return Length() * Width() * Height() / 3.0;}

private:
    int length_;
    int width_;
    int height_;

    void Validate(){
        if(length_ <= 0 || width_ <= 0 || height_ <= 0)
            throw std::invalid_argument("negative dimension");
    }
};

#endif PYRAMID_H
