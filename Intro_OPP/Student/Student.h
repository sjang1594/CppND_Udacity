#include <string>
#include <stdexcept>

#ifndef STUDENT_STUDENT_H
#define STUDENT_STUDENT_H

// Taking 3 private member variables to the class : Name, Grade(e.g. 9th grade), grade point average.
// Created public member functions to set each of the member variables. Before setting the values
// verify that:
// 1. Grade is from 0 to 12.
// 2. GPA is from 0.0 to 4.0.
// 3. The function must either throw an exception if any of the invariants are violated
// 4. Within the main() (Outside of the class), declare an object of type Student and test out each of
// the member function calls.

class Student{
public:
    //Constructor
    //Instead of using mutator, use validator function, this is why
    Student(std::string name, int grade, float gpa) : name_(name), grade_(grade), gpa_(gpa){
        Validate();
    }
    //accessor
    std::string Name() const {
        return name_;
    }
    int Grade() const {
        return grade_;
    }
    float GPA() const {
        return gpa_;
    }

    //Mutator
    void Name(std::string name){
        name_ = name;
        Validate();
    }

    void Grade(int grade){
        grade_ = grade;
        Validate();
    }

    void GPA(float gpa){
        gpa_ = gpa;
        Validate();
    }

private:
    std::string name_;
    int grade_;
    float gpa_;

    void Validate() {
        if (Grade() < 0 || Grade() > 12 || GPA() < 0.0 || GPA() > 4.0)
            throw std::invalid_argument("argument out of bounds");
    }
};

#endif //STUDENT_STUDENT_H
