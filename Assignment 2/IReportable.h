#ifndef IREPORTABLE_H
#define IREPORTABLE_H

// Abstract interface: Seller, Buyer, Admin each report differently
class IReportable {
public:
    virtual void showReport() = 0;
    virtual int getID() = 0;
    virtual ~IReportable() {}
};

#endif
