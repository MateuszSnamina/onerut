#ifndef ONERUT_SCALAR_FUNCTION_REAL
#define ONERUT_SCALAR_FUNCTION_REAL

#include<cassert>

#include<onerut_scalar/scalar_real.hpp>

namespace onerut_scalar {

    // -------------------------------------------------------------------------
    // -------------- FUNCTION CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    template<typename Callable>
    class UnaryRealFunction : public Real {
    public:
        UnaryRealFunction(Callable callable, std::shared_ptr<Real> arg);
        double value_real() const override;
    private:
        Callable callable;
        const std::shared_ptr<Real> arg;
    };

    template<typename Callable>
    UnaryRealFunction<Callable>::UnaryRealFunction(Callable callable, std::shared_ptr<Real> arg) :
    callable(callable),
    arg(arg) {
        assert(arg);
    }

    template<typename Callable>
    double UnaryRealFunction<Callable>::value_real() const {
        const double x = arg->value_real();
        const double y = callable(x);
        return y;
    }

    // -------------------------------------------------------------------------

    template<typename Callable>
    class BinaryRealFunction : public Real {
    public:
        BinaryRealFunction(Callable callable, std::shared_ptr<Real> first_arg, std::shared_ptr<Real> second_arg);
        double value_real() const override;
    private:
        Callable callable;
        const std::shared_ptr<Real> first_arg;
        const std::shared_ptr<Real> second_arg;
    };

    template<typename Callable>
    BinaryRealFunction<Callable>::BinaryRealFunction(Callable callable, std::shared_ptr<Real> first_arg, std::shared_ptr<Real> second_arg) :
    callable(callable),
    first_arg(first_arg),
    second_arg(second_arg) {
        assert(first_arg);
        assert(second_arg);
    }

    template<typename Callable>
    double BinaryRealFunction<Callable>::value_real() const {
        const double firts_x = first_arg->value_real();
        const double second_x = second_arg->value_real();
        const double y = callable(firts_x, second_x);
        return y;
    }
    
}

#endif