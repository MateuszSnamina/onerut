#ifndef ONERUT_SCALAR_SCALAR_ABSTRACT_COMPLEX
#define ONERUT_SCALAR_SCALAR_ABSTRACT_COMPLEX

#include<complex>
#include<memory>
#include<vector>

namespace onerut_scalar {

    //class Complex;//TODO delete

    class Complex {
    public:
        virtual std::complex<double> value_complex() const = 0;
        virtual ~Complex() = default;
        virtual std::vector<std::shared_ptr<const Complex>> dependency() const = 0;
    };
}

#endif