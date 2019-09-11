#ifndef IRATIO_H
#define IRATIO_H

#include "error.h"
#define ABS(x) ((x) > 0 ? (x) : -(x))
//#include "SHARED_EXPORT.h"

class /*SHARED_EXPORT*/ IRatio
{
public:
    enum InterfaceTypes
    {
        INTERFACE_0,
        DIMENSION_INTERFACE_IMPL
    };

    virtual int getId() const = 0;

    /*factories*/
    static IRatio* createRatio(int nom, int denom);

    /*operations*/
    virtual int add(IRatio const* const right) = 0;
    virtual int subtract(IRatio const* const right) = 0;
    virtual int multiply(IRatio const* const right) = 0;
    virtual int divide(IRatio const* const right) = 0;

    /*static operations*/
    static IRatio* add(IRatio const* const left, IRatio const* const right);
    static IRatio* subtract(IRatio const* const left, IRatio const* const right);
    static IRatio* multiply(IRatio const* const left, IRatio const* const right);
    static IRatio* divide(IRatio const* const left, IRatio const* const right);

    /*comparators*/
    virtual int gt(IRatio const* const right, bool& result) const = 0;
    virtual int lt(IRatio const* const right, bool& result) const = 0;
    virtual int eq(IRatio const* const right, bool& result) const = 0;

    virtual IRatio* clone() const = 0;
    virtual int get(int& nom, int& denom) const = 0;

    /*D-TOR*/
    ~IRatio(){}

protected:
    IRatio() = default;

private:
    /*non default copyable*/
    IRatio(const IRatio& other) = delete;
    void operator=(const IRatio& other) = delete;
};

#endif // IRATIO_H
