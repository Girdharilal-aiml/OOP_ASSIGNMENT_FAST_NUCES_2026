#ifndef VEHICLE_H
#define VEHICLE_H
#include<string>
#include "IDisplayable.h"
#include "ISearchable.h"
using namespace std;

// Abstract base class for Car and Bike - never instantiated directly
class Vehicle : public IDisplayable, public ISearchable {
protected:
    string brand;
    string model;
    int year;
    int mileage;
    string color;

public:
    Vehicle();
    Vehicle(string b, string m, int y, int km, string c);
    Vehicle(const Vehicle& obj);

    void setBrand(string b); void setModel(string m);
    void setYear(int y);     void setMileage(int km);
    string getBrand();  string getModel();
    int getYear();      int getMileage();  string getColor();
    bool isOld();
    string summary();

    // pure virtuals - Car and Bike must implement
    virtual void display() = 0;
    virtual string getType() = 0;
    virtual bool matchesKeyword(string kw) = 0;
    virtual bool inBudget(double mn, double mx) = 0;

    bool operator==(const Vehicle& other) const;
    virtual ~Vehicle() {}
};

#endif
