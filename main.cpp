#include <QtCore/QCoreApplication>
#include "IRatio.h"
#include "ILog.h"
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a1(argc, argv);
    ILog::init("out.txt");
    int a,b;
    IRatio* r1 = IRatio::createRatio(1,0);
    IRatio* r2 = IRatio::createRatio(1,2);
    IRatio* r3 = IRatio::createRatio(0,1);
    IRatio* r4 = IRatio::createRatio(2,4);

    bool res;
    r2->gt(r3, res);
    std::cout << res << std::endl;
    r2->lt(r3, res);
    std::cout << res << std::endl;
    r2->eq(r3, res);
    std::cout << res << std::endl;
    r2->eq(r2, res);
    std::cout << res << std::endl;

    r4->get(a,b);
    std::cout << a << " " << b << std::endl;
    IRatio* r5 = IRatio::createRatio(4,2);
    r5->get(a,b);
    std::cout << a << " " << b << std::endl;
    r2->add(r3);
    r2->get(a,b);
    std::cout << a << " " << b << std::endl;

    r2->subtract(r3);
    r2->get(a,b);
    std::cout << a << " " << b << std::endl;

    r2->multiply(r3);
    r2->get(a,b);
    std::cout << a << " " << b << std::endl;

    r2->divide(r3);
    r2->get(a,b);
    std::cout << a << " " << b << std::endl;

    ILog::destroy();
    return a1.exec();
}
