#ifndef ISEARCHABLE_H
#define ISEARCHABLE_H
#include<string>
using namespace std;

// Abstract interface: forces searchable classes to implement keyword and budget check
class ISearchable {
public:
    virtual bool matchesKeyword(string kw) = 0;
    virtual bool inBudget(double mn, double mx) = 0;
    virtual ~ISearchable() {}
};

#endif
