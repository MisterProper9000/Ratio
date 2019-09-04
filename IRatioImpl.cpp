#include "IRatio.h"
#include "ILog.h"
#include "limits.h"

namespace{
    class IRatioImpl: public virtual IRatio
    {
    public:
        virtual int getId() const;

        static IRatio* createRatio(int nom, int denom);

        /*operations*/
        virtual int add(IRatio const* const right);
        virtual int subtract(IRatio const* const right);
        virtual int multiply(IRatio const* const right);
        virtual int divide(IRatio const* const right);

        /*comparators*/
        virtual int gt(IRatio const* const right, bool& result) const;
        virtual int lt(IRatio const* const right, bool& result) const;
        virtual int eq(IRatio const* const right, bool& result) const;

        virtual IRatio* clone() const;
        virtual int get(int& nom, int& denom) const;

        /*D-TOR*/
        ~IRatioImpl(){}

    protected:
        IRatioImpl(int nom, int denom);

        int m_nominator;
        int m_denominator;

    private:
        /*non default copyable*/
        IRatioImpl(const IRatioImpl& other) = delete;
        void operator=(const IRatioImpl& other) = delete;

        int gcd (int a, int b);

    };
}

int IRatioImpl::gcd (int a, int b) {
    while (b) {
            a %= b;
            a = a + b;
            b = a - b;
            a = a - b;
    }
    return a;
}

IRatio* IRatio::createRatio(int nom, int denom)
{
    return IRatioImpl::createRatio(nom, denom);
}

IRatio* IRatioImpl::createRatio(int nom, int denom)
{
    if(denom == 0)
    {
        ILog::report("IRatio.createRatio: denominator can't be zero");
        return 0;
    }

    return new IRatioImpl(nom, (nom == 0)?1:denom);
}

IRatioImpl::IRatioImpl(int nom, int denom)
{
    int _gcd = gcd(nom, denom);
    nom /= _gcd;
    denom /= _gcd;

    m_nominator = nom;
    m_denominator = denom;
}

int IRatioImpl::getId() const
{
    return INTERFACE_0;
}

int IRatioImpl::get(int& nom, int& denom) const
{
    nom = m_nominator;
    denom = m_denominator;
    return ERR_OK;
}

IRatio* IRatioImpl::clone() const
{
    return IRatio::createRatio(m_nominator, m_denominator);
}

int IRatioImpl::add(const IRatio *const right)
{
    if (!right)
    {
        ILog::report("IRatioImpl.add error: wrong arg");
        return ERR_WRONG_ARG;
    }

    int lastError;
    int nom, denom;
    lastError = right->get(nom, denom);

    if(lastError != ERR_OK)
    {
        return lastError;
    }

    if (nom == 0 || m_nominator == 0)
        return ERR_OK;

    // Checking if addition will cause overflow
    if((double)m_nominator <= (double)INT_MAX/denom &&
            (double)m_denominator <= (double)INT_MAX/nom &&
            m_nominator*denom <= INT_MAX - m_denominator*nom &&
            (double)m_denominator <= INT_MAX/denom)
    {
        m_nominator = m_nominator*denom + m_denominator*nom;
        m_denominator *= denom;

        int _gcd = gcd(m_nominator, m_denominator);
        m_nominator /= _gcd;
        m_denominator /= _gcd;

        return ERR_OK;
    }
    else
    {
        ILog::report("IRatioImpl.add: int overfulls");
        return ERR_OVERFULL;
    }
}

int IRatioImpl::subtract(const IRatio *const right)
{
    if (!right)
    {
        ILog::report("IRatioImpl.subtract error: wrong arg");
        return ERR_WRONG_ARG;
    }

    int lastError;
    int nom, denom;
    lastError = right->get(nom, denom);

    if(lastError != ERR_OK)
    {
        return lastError;
    }

    if (nom == 0 || m_nominator == 0)
        return ERR_OK;

    // Checking if subtraction will cause overflow
    if((double)m_nominator <= (double)INT_MAX/denom &&
            (double)m_denominator <= (double)INT_MAX/nom &&
            m_nominator*denom >= INT_MIN + m_denominator*nom &&
            (double)m_denominator <= INT_MAX/denom)
    {
        m_nominator = m_nominator*denom - m_denominator*nom;
        m_denominator *= denom;

        int _gcd = gcd(m_nominator, m_denominator);
        m_nominator /= _gcd;
        m_denominator /= _gcd;

        return ERR_OK;
    }
    else
    {
        ILog::report("IRatioImpl.subtract: int overfulls");
        return ERR_OVERFULL;
    }
}

int IRatioImpl::multiply(const IRatio *const right)
{
    if (!right)
    {
        ILog::report("IRatioImpl.multiply error: wrong arg");
        return ERR_WRONG_ARG;
    }

    int lastError;
    int nom, denom;
    lastError = right->get(nom, denom);

    if(lastError != ERR_OK)
    {
        return lastError;
    }

    if (nom == 0 || m_nominator == 0)
    {
        m_nominator = 0;
        return ERR_OK;
    }

    // Checking if subtraction will cause overflow
    if((double)m_nominator <= (double)INT_MAX/nom &&
            (double)m_denominator <= (double)INT_MAX/denom)
    {
        m_nominator *= nom;
        m_denominator *= denom;

        int _gcd = gcd(m_nominator, m_denominator);
        m_nominator /= _gcd;
        m_denominator /= _gcd;

        return ERR_OK;
    }
    else
    {
        ILog::report("IRatioImpl.multiply: int overfulls");
        return ERR_OVERFULL;
    }
}

int IRatioImpl::divide(const IRatio *const right)
{
    if (!right)
    {
        ILog::report("IRatioImpl.divide error: wrong arg");
        return ERR_WRONG_ARG;
    }

    int lastError;
    int nom, denom;
    lastError = right->get(nom, denom);

    if(lastError != ERR_OK)
    {
        return lastError;
    }

    if(nom == 0)
    {
        ILog::report("IRatioImpl.divide: division by zero");
        return ERR_DIV_BY_ZERO;
    }

    if(m_nominator == 0)
        return ERR_OK;

    // Checking if subtraction will cause overflow
    if((double)m_nominator <= (double)INT_MAX/denom &&
            (double)m_denominator <= (double)INT_MAX/nom)
    {
        m_nominator *= denom;
        m_denominator *= nom;

        int _gcd = gcd(m_nominator, m_denominator);
        m_nominator /= _gcd;
        m_denominator /= _gcd;

        return ERR_OK;
    }
    else
    {
        ILog::report("IRatioImpl.divide: int overfulls");
        return ERR_OVERFULL;
    }
}

IRatio* IRatio::add(IRatio const* const left, IRatio const* const right)
{
    if (!left || !right)
    {
        ILog::report("IRatioImpl.add: operand of addition is nullptr, expected IRatioImpl pointer");
        return 0;
    }

    IRatio* res = left->clone();
    if(!res)
    {
        return 0;
    }

    if (res->add(right) == ERR_OK)
        return res;
    else
        return 0;
}

IRatio* IRatio::subtract(IRatio const* const left, IRatio const* const right)
{
    if (!left || !right)
    {
        ILog::report("IRatioImpl.subtract: operand of subtraction is nullptr, expected IRatioImpl pointer");
        return 0;
    }

    IRatio* res = left->clone();
    if(!res)
    {
        return 0;
    }

    if (res->subtract(right) == ERR_OK)
        return res;
    else
        return 0;
}

IRatio* IRatio::multiply(IRatio const* const left, IRatio const* const right)
{
    if (!left || !right)
    {
        ILog::report("IRatioImpl.multiply: operand of multiplication is nullptr, expected IRatioImpl pointer");
        return 0;
    }

    IRatio* res = left->clone();
    if(!res)
    {
        return 0;
    }

    if (res->multiply(right) == ERR_OK)
        return res;
    else
        return 0;
}

IRatio* IRatio::divide(IRatio const* const left, IRatio const* const right)
{
    if (!left || !right)
    {
        ILog::report("IRatioImpl.divide: operand of division is nullptr, expected IRatioImpl pointer");
        return 0;
    }

    IRatio* res = left->clone();
    if(!res)
    {
        return 0;
    }

    if (res->divide(right) == ERR_OK)
        return res;
    else
        return 0;
}

int IRatioImpl::gt(IRatio const* const right, bool& result) const
{
    if (!right)
    {
        ILog::report("IRatioImpl.gt error: wrong arg");
        return ERR_WRONG_ARG;
    }

    int lastError;
    int nom, denom;
    lastError = right->get(nom, denom);

    if(lastError != ERR_OK)
    {
        return lastError;
    }
    if(m_nominator == 0 || (m_nominator == 0 && nom == 0))
    {
        result = false;
        return ERR_OK;
    }
    if(nom == 0)
    {
        result = true;
        return ERR_OK;
    }

    // Checking if subtraction will cause overflow
    if((double)m_nominator <= (double)INT_MAX/denom &&
            (double)m_denominator <= (double)INT_MAX/nom)
    {
        if(m_nominator*denom > m_denominator*nom)
            result = true;
        else
            result = false;

        return ERR_OK;
    }
    else
    {
        ILog::report("IRatioImpl.gt: int overfulls");
        return ERR_OVERFULL;
    }
}

int IRatioImpl::lt(IRatio const* const right, bool& result) const
{
    if (!right)
    {
        ILog::report("IRatioImpl.lt error: wrong arg");
        return ERR_WRONG_ARG;
    }

    int lastError;
    int nom, denom;
    lastError = right->get(nom, denom);

    if(lastError != ERR_OK)
    {
        return lastError;
    }
    if(nom == 0 || (m_nominator == 0 && nom == 0))
    {
        result = false;
        return ERR_OK;
    }
    if(m_nominator == 0)
    {
        result = true;
        return ERR_OK;
    }

    // Checking if subtraction will cause overflow
    if((double)m_nominator <= (double)INT_MAX/denom &&
            (double)m_denominator <= (double)INT_MAX/nom)
    {
        if(m_nominator*denom < m_denominator*nom)
            result = true;
        else
            result = false;

        return ERR_OK;
    }
    else
    {
        ILog::report("IRatioImpl.lt: int overfulls");
        return ERR_OVERFULL;
    }
}

int IRatioImpl::eq(IRatio const* const right, bool& result) const
{
    if (!right)
    {
        ILog::report("IRatioImpl.eq error: wrong arg");
        return ERR_WRONG_ARG;
    }

    if(right == this)
    {
        result = true;
        return ERR_OK;
    }

    int lastError;
    int nom, denom;
    lastError = right->get(nom, denom);

    if(lastError != ERR_OK)
    {
        return lastError;
    }
    if(m_nominator == 0 && nom == 0)
    {
        result = true;
        return ERR_OK;
    }
    if((nom == 0 && m_nominator != 0) || (nom != 0 && m_nominator == 0))
    {
        result = false;
        return ERR_OK;
    }

    // Checking if subtraction will cause overflow
    if((double)m_nominator <= (double)INT_MAX/denom &&
            (double)m_denominator <= (double)INT_MAX/nom)
    {
        if(m_nominator*denom == m_denominator*nom)
            result = true;
        else
            result = false;

        return ERR_OK;
    }
    else
    {
        ILog::report("IRatioImpl.eq: int overfulls");
        return ERR_OVERFULL;
    }
}
