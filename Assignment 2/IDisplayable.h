#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H
#include<string>
using namespace std;

// Abstract interface: forces every class to implement its own display()
class IDisplayable {
public:
    virtual void display() = 0;
    virtual string getType() = 0;
    virtual ~IDisplayable() {}
};

#endif
