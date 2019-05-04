#ifndef ONERUT_SCALAR_SCALAR_ABSTRACT_COMPLEX
#define ONERUT_SCALAR_SCALAR_ABSTRACT_COMPLEX

#include<complex>
#include<memory>
#include<vector>

#include<onerut_dependence/dependence.hpp>

namespace onerut_scalar {

    class Complex : public onerut_dependence::Dependable {
    public:
        virtual std::complex<double> value_complex() const = 0;
        virtual ~Complex() = default;
    };
}

#endif