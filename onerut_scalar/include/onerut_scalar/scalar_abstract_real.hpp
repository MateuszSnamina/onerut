#ifndef ONERUT_SCALAR_SCALAR_ABSTRACT_REAL
#define ONERUT_SCALAR_SCALAR_ABSTRACT_REAL

#include<onerut_scalar/scalar_abstract_complex.hpp>

namespace onerut_scalar {

    class Real : public Complex {
    public:
        virtual double value_real() const = 0;
        virtual std::complex<double> value_complex() const override;
        virtual ~Real() = default;
    };

}

#endif