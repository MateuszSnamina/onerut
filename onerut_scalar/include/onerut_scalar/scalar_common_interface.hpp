#ifndef ONERUT_SCALAR_COMMON_INTERFACE
#define ONERUT_SCALAR_COMMON_INTERFACE

// Often functions for all kind of numbers are analogical.
// In such a cases it is desirable to write only one cpp-function
// (possibly a template function) to handle all the three scalar types 
// (Integer, Real, Complex).
//
// The API used by onerut-scalar-base-classes requires overriding 
// value_integer(), value_real() and value_complex() member functions 
// Necessity of overriding different functions is inconvenient
// when writing a unified function.
//
// This header provides unified API
// in which you override value() function, no mater the scalar type, 
// in contrast to overriding value_integer(), value_real() and value_complex()
// member functions.

namespace onerut_scalar {

    template<class OnerutBaseType>
    class CommonInterface {
    };

    template<>
    class CommonInterface<Integer> : public Integer {
    public:
        long value_integer() const final;
        virtual long value() const = 0;
    };

    template<>
    class CommonInterface<Real> : public Real {
    public:
        double value_real() const final;
        virtual double value() const = 0;
    };

    template<>
    class CommonInterface<Complex> : public Complex {
    public:
        std::complex<double> value_complex() const final;
        virtual std::complex<double> value() const = 0;
    };

    // -------------------------------------------------------------------------
    // -----   Implementation:   -----------------------------------------------
    // -------------------------------------------------------------------------

    inline
    long CommonInterface<Integer>::value_integer() const {
        return value();
    }

    inline
    double CommonInterface<Real>::value_real() const {
        return value();
    }

    inline
    std::complex<double> CommonInterface<Complex>::value_complex() const {
        return value();
    }

}

#endif