#include "Student.h"
#include <cassert>
#include <iostream>

int main() {
    Student student("Nick", 3, 4.0);
    //std::cout << student.Gpa() << "\n";

    assert(student.Name() == "Nick");
    assert(student.Grade() == 3);
    assert(student.GPA() == 4.0);

    bool caught{false};
    try{
        student.Grade(20);
    }
    catch(...){
        caught = true;
    }
    assert(caught);
}
