#ifndef ONERUT_SCALAR_FUNCTION_COMPLEX
#define ONERUT_SCALAR_FUNCTION_COMPLEX

#include<cassert>

#include<onerut_scalar/scalar_abstract_complex.hpp>

namespace onerut_scalar {

    // -------------------------------------------------------------------------
    // -------------- FUNCTION CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    template<typename Callable>
    class UnaryComplexFunction : public Complex {
    public:
        UnaryComplexFunction(Callable callable, std::shared_ptr<Complex> arg);
        std::complex<double> value_complex() const override;
    private:
        Callable callable;
        const std::shared_ptr<Complex> arg;
    };

    template<typename Callable>
    UnaryComplexFunction<Callable>::UnaryComplexFunction(Callable callable, std::shared_ptr<Complex> arg) :
    callable(callable),
    arg(arg) {
        assert(arg);
    }

    template<typename Callable>
    std::complex<double> UnaryComplexFunction<Callable>::value_complex() const {
        const std::complex<double>& x = arg->value_complex();
        const std::complex<double> y = callable(x);
        return y;
    }

    // -------------------------------------------------------------------------

    template<typename Callable>
    class BinaryComplexFunction : public Complex {
    public:
        BinaryComplexFunction(Callable callable, std::shared_ptr<Complex> first_arg, std::shared_ptr<Complex> second_arg);
        std::complex<double> value_complex() const override;
    private:
        Callable callable;
        const std::shared_ptr<Complex> first_arg;
        const std::shared_ptr<Complex> second_arg;
    };

    template<typename Callable>
    BinaryComplexFunction<Callable>::BinaryComplexFunction(Callable callable, std::shared_ptr<Complex> first_arg, std::shared_ptr<Complex> second_arg) :
    callable(callable),
    first_arg(first_arg),
    second_arg(second_arg) {
        assert(first_arg);
        assert(second_arg);
    }

    template<typename Callable>
    std::complex<double> BinaryComplexFunction<Callable>::value_complex() const {
        const std::complex<double>& firts_x = first_arg->value_complex();
        const std::complex<double>& second_x = second_arg->value_complex();
        const std::complex<double> y = callable(firts_x, second_x);
        return y;
    }
    
}

#endif