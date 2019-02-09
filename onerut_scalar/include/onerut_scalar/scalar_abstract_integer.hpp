#ifndef ONERUT_SCALAR_SCALAR_ABSTRACT_INTEGER
#define ONERUT_SCALAR_SCALAR_ABSTRACT_INTEGER

#include<onerut_scalar/scalar_abstract_real.hpp>

namespace onerut_scalar {

    class Integer : public Real {
    public:
        virtual long value_integer() const = 0;
        virtual double value_real() const override;
        virtual ~Integer() = default;
    };

}

#endif