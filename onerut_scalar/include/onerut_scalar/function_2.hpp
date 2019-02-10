#ifndef ONERUT_SCALAR_FUNCTION_2
#define ONERUT_SCALAR_FUNCTION_2

#include<cassert>
#include<type_traits>

#include<onerut_scalar/scalar_abstract_complex.hpp>
#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_scalar/scalar_abstract_integer.hpp>

namespace onerut_scalar {

    // -------------------------------------------------------------------------

    struct ArgInteger {
        template<class T>
        long extract(std::shared_ptr<T> arg) const;
    };

    struct ArgReal {
        template<class T>
        double extract(std::shared_ptr<T> arg) const;
    };

    struct ArgComplex {
        template<class T>
        std::complex<double> extract(std::shared_ptr<T> arg) const;
    };

    template<class T>
    long ArgInteger::extract(std::shared_ptr<T> arg) const {
        static_assert(std::is_base_of<Integer, T>::value);
        return arg->value_integer();
    }

    template<class T>
    double ArgReal::extract(std::shared_ptr<T> arg) const {
        static_assert(std::is_base_of<Real, T>::value);
        return arg->value_real();
    }

    template<class T>
    std::complex<double> ArgComplex::extract(std::shared_ptr<T> arg) const {
        static_assert(std::is_base_of<Complex, T>::value);
        return arg->value_complex();
    }

    // -------------------------------------------------------------------------

    template<class T>
    struct IsArg : public std::false_type {
    };

    template<>
    struct IsArg<ArgInteger> : public std::true_type {
    };

    template<>
    struct IsArg<ArgReal> : public std::true_type {
    };

    template<>
    struct IsArg<ArgComplex> : public std::true_type {
    };

    // -------------------------------------------------------------------------
    // -------------- FUNCTION CLASES  -----------------------------------------
    // -------------------------------------------------------------------------

    template<typename Arg1, typename Callable, typename U1>
    class UnaryComplexFunction : public Complex {
    public:
        static_assert(IsArg<Arg1>::value);
        UnaryComplexFunction(Callable callable, std::shared_ptr<U1> arg);
        std::complex<double> value_complex() const override;
    private:
        Callable callable;
        const std::shared_ptr<U1> arg;
    };

    template<typename Arg1, typename Callable, typename U1>
    UnaryComplexFunction<Arg1, Callable, U1>::UnaryComplexFunction(Callable callable, std::shared_ptr<U1> arg) :
    callable(callable),
    arg(arg) {
        assert(arg);
    }

    template<typename Arg1, typename Callable, typename U1>
    std::complex<double>
    UnaryComplexFunction<Arg1, Callable, U1>::value_complex() const {
        const auto& x = Arg1().extract(arg);
        const std::complex<double> y = callable(x);
        return y;
    }

    // -------------------------------------------------------------------------

    template<typename Arg1, typename Arg2, typename Callable, typename U1, typename U2>
    class BinaryComplexFunction : public Complex {
    public:
        static_assert(IsArg<Arg1>::value);
        static_assert(IsArg<Arg2>::value);
        BinaryComplexFunction(Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg);
        std::complex<double> value_complex() const override;
    private:
        Callable callable;
        const std::shared_ptr<U1> first_arg;
        const std::shared_ptr<U2> second_arg;
    };

    template<typename Arg1, typename Arg2, typename Callable, typename U1, typename U2>
    BinaryComplexFunction<Arg1, Arg2, Callable, U1, U2>::BinaryComplexFunction(Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg) :
    callable(callable),
    first_arg(first_arg),
    second_arg(second_arg) {
        assert(first_arg);
        assert(second_arg);
    }

    template<typename Arg1, typename Arg2, typename Callable, typename U1, typename U2>
    std::complex<double>
    BinaryComplexFunction<Arg1, Arg2, Callable, U1, U2>::value_complex() const {
        const auto& firts_x = Arg1().extract(first_arg);
        const auto& second_x = Arg2().extract(second_arg);
        const std::complex<double> y = callable(firts_x, second_x);
        return y;
    }
    
    // -------------------------------------------------------------------------
    
    template<typename Arg1, typename Callable, typename U1>
    class UnaryRealFunction : public Real {
    public:
        static_assert(IsArg<Arg1>::value);
        UnaryRealFunction(Callable callable, std::shared_ptr<U1> arg);
        double value_real() const override;
    private:
        Callable callable;
        const std::shared_ptr<U1> arg;
    };

    template<typename Arg1, typename Callable, typename U1>
    UnaryRealFunction<Arg1, Callable, U1>::UnaryRealFunction(Callable callable, std::shared_ptr<U1> arg) :
    callable(callable),
    arg(arg) {
        assert(arg);
    }

    template<typename Arg1, typename Callable, typename U1>
    double
    UnaryRealFunction<Arg1, Callable, U1>::value_real() const {
        const auto& x = Arg1().extract(arg);
        const double y = callable(x);
        return y;
    }

    // -------------------------------------------------------------------------

    template<typename Arg1, typename Arg2, typename Callable, typename U1, typename U2>
    class BinaryRealFunction : public Real {
    public:
        static_assert(IsArg<Arg1>::value);
        static_assert(IsArg<Arg2>::value);
        BinaryRealFunction(Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg);
        double value_real() const override;
    private:
        Callable callable;
        const std::shared_ptr<U1> first_arg;
        const std::shared_ptr<U2> second_arg;
    };

    template<typename Arg1, typename Arg2, typename Callable, typename U1, typename U2>
    BinaryRealFunction<Arg1, Arg2, Callable, U1, U2>::BinaryRealFunction(Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg) :
    callable(callable),
    first_arg(first_arg),
    second_arg(second_arg) {
        assert(first_arg);
        assert(second_arg);
    }

    template<typename Arg1, typename Arg2, typename Callable, typename U1, typename U2>
    double
    BinaryRealFunction<Arg1, Arg2, Callable, U1, U2>::value_real() const {
        const auto& firts_x = Arg1().extract(first_arg);
        const auto& second_x = Arg2().extract(second_arg);
        const double y = callable(firts_x, second_x);
        return y;
    }

}

#endif