#ifndef ONERUT_SCALAR_SCALAR_ABSTRACT_COMPLEX
#define ONERUT_SCALAR_SCALAR_ABSTRACT_COMPLEX

#include<complex>

namespace onerut_scalar {

    class Complex {
    public:
        virtual std::complex<double> value_complex() const = 0;
        virtual ~Complex() = default;
    };
}

#endif