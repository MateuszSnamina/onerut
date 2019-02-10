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
        using BaseType = Integer;
        template<class T>
        long extract(std::shared_ptr<T> arg) const;
    };

    struct ArgReal {
        using BaseType = Real;
        template<class T>
        double extract(std::shared_ptr<T> arg) const;
    };

    struct ArgComplex {
        using BaseType = Complex;
        template<class T>
        std::complex<double> extract(std::shared_ptr<T> arg) const;
    };

    template<class T>
    long ArgInteger::extract(std::shared_ptr<T> arg) const {
        static_assert(std::is_base_of<BaseType, T>::value);
        return arg->value_integer();
    }

    template<class T>
    double ArgReal::extract(std::shared_ptr<T> arg) const {
        static_assert(std::is_base_of<BaseType, T>::value);
        return arg->value_real();
    }

    template<class T>
    std::complex<double> ArgComplex::extract(std::shared_ptr<T> arg) const {
        static_assert(std::is_base_of<BaseType, T>::value);
        return arg->value_complex();
    }

    // -------------------------------------------------------------------------

    struct ReturnInteger {
        using BaseType = Integer;
    };

    struct ReturnReal {
        using BaseType = Real;
    };

    struct ReturnComplex {
        using BaseType = Complex;
    };

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

    template<class T>
    struct IsReturn : public std::false_type {
    };

    template<>
    struct IsReturn<ReturnInteger> : public std::true_type {
    };

    template<>
    struct IsReturn<ReturnReal> : public std::true_type {
    };

    template<>
    struct IsReturn<ReturnComplex> : public std::true_type {
    };

    // -------------------------------------------------------------------------
    // -------------- FUNCTION CLASES  -----------------------------------------
    // -------------------------------------------------------------------------

    template<typename Arg1, typename Callable>
    class UnaryComplexFunction : public Complex {
    public:
        static_assert(IsArg<Arg1>::value);
        using U1 = typename Arg1::BaseType;
        UnaryComplexFunction(Callable callable, std::shared_ptr<U1> arg);
        std::complex<double> value_complex() const override;
    private:
        Callable callable;
        const std::shared_ptr<U1> arg;
    };

    template<typename Arg1, typename Callable>
    UnaryComplexFunction<Arg1, Callable>::UnaryComplexFunction(
            Callable callable, std::shared_ptr<U1> arg) :
    callable(callable),
    arg(arg) {
        assert(arg);
    }

    template<typename Arg1, typename Callable>
    std::complex<double>
    UnaryComplexFunction<Arg1, Callable>::value_complex() const {
        const auto& x = Arg1().extract(arg);
        const std::complex<double> y = callable(x);
        return y;
    }

    // -------------------------------------------------------------------------

    template<typename Arg1, typename Arg2, typename Callable>
    class BinaryComplexFunction : public Complex {
    public:
        static_assert(IsArg<Arg1>::value);
        static_assert(IsArg<Arg2>::value);
        using U1 = typename Arg1::BaseType;
        using U2 = typename Arg2::BaseType;
        BinaryComplexFunction(Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg);
        std::complex<double> value_complex() const override;
    private:
        Callable callable;
        const std::shared_ptr<U1> first_arg;
        const std::shared_ptr<U2> second_arg;
    };

    template<typename Arg1, typename Arg2, typename Callable>
    BinaryComplexFunction<Arg1, Arg2, Callable>::BinaryComplexFunction(
            Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg) :
    callable(callable),
    first_arg(first_arg),
    second_arg(second_arg) {
        assert(first_arg);
        assert(second_arg);
    }

    template<typename Arg1, typename Arg2, typename Callable>
    std::complex<double>
    BinaryComplexFunction<Arg1, Arg2, Callable>::value_complex() const {
        const auto& firts_x = Arg1().extract(first_arg);
        const auto& second_x = Arg2().extract(second_arg);
        const std::complex<double> y = callable(firts_x, second_x);
        return y;
    }

    // -------------------------------------------------------------------------

    template<typename Arg1, typename Callable>
    class UnaryRealFunction : public Real {
    public:
        static_assert(IsArg<Arg1>::value);
        using U1 = typename Arg1::BaseType;
        UnaryRealFunction(Callable callable, std::shared_ptr<U1> arg);
        double value_real() const override;
    private:
        Callable callable;
        const std::shared_ptr<U1> arg;
    };

    template<typename Arg1, typename Callable>
    UnaryRealFunction<Arg1, Callable>::UnaryRealFunction(
            Callable callable, std::shared_ptr<U1> arg) :
    callable(callable),
    arg(arg) {
        assert(arg);
    }

    template<typename Arg1, typename Callable>
    double
    UnaryRealFunction<Arg1, Callable>::value_real() const {
        const auto& x = Arg1().extract(arg);
        const double y = callable(x);
        return y;
    }

    // -------------------------------------------------------------------------

    template<typename Arg1, typename Arg2, typename Callable>
    class BinaryRealFunction : public Real {
    public:
        static_assert(IsArg<Arg1>::value);
        static_assert(IsArg<Arg2>::value);
        using U1 = typename Arg1::BaseType;
        using U2 = typename Arg2::BaseType;
        BinaryRealFunction(Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg);
        double value_real() const override;
    private:
        Callable callable;
        const std::shared_ptr<U1> first_arg;
        const std::shared_ptr<U2> second_arg;
    };

    template<typename Arg1, typename Arg2, typename Callable>
    BinaryRealFunction<Arg1, Arg2, Callable>::BinaryRealFunction(
            Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg) :
    callable(callable),
    first_arg(first_arg),
    second_arg(second_arg) {
        assert(first_arg);
        assert(second_arg);
    }

    template<typename Arg1, typename Arg2, typename Callable>
    double
    BinaryRealFunction<Arg1, Arg2, Callable>::value_real() const {
        const auto& firts_x = Arg1().extract(first_arg);
        const auto& second_x = Arg2().extract(second_arg);
        const double y = callable(firts_x, second_x);
        return y;
    }

    // -------------------------------------------------------------------------
    // ------------PREFERRED PUBLIC API ----------------------------------------
    // -------------------------------------------------------------------------

    template <class Return, class Callable, class... Args>
    class Function;

    template <class Callable, class Arg1>
    class Function<ReturnComplex, Callable, Arg1> : public UnaryComplexFunction<Arg1, Callable> {
    public:
        static_assert(IsArg<Arg1>::value);
        using U1 = typename Arg1::BaseType;

        Function(Callable callable, std::shared_ptr<U1> arg) :
        UnaryComplexFunction<Arg1, Callable>(callable, arg) {

        }
    };

    template <class Callable, class Arg1>
    class Function<ReturnReal, Callable, Arg1> : public UnaryRealFunction<Arg1, Callable> {
    public:
        static_assert(IsArg<Arg1>::value);
        using U1 = typename Arg1::BaseType;

        Function(Callable callable, std::shared_ptr<U1> arg) :
        UnaryRealFunction<Arg1, Callable>(callable, arg) {

        }

    };

    template <class Callable, class Arg1, class Arg2>
    class Function<ReturnComplex, Callable, Arg1, Arg2> : public BinaryComplexFunction<Arg1, Arg2, Callable> {
    public:
        static_assert(IsArg<Arg1>::value);
        static_assert(IsArg<Arg2>::value);
        using U1 = typename Arg1::BaseType;
        using U2 = typename Arg2::BaseType;

        Function(Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg) :
        BinaryComplexFunction<Arg1, Arg2, Callable>(callable, first_arg, second_arg) {
        }
    };

    template <class Callable, class Arg1, class Arg2>
    class Function<ReturnReal, Callable, Arg1, Arg2> : public BinaryRealFunction<Arg1, Arg2, Callable> {
    public:
        static_assert(IsArg<Arg1>::value);
        static_assert(IsArg<Arg2>::value);
        using U1 = typename Arg1::BaseType;
        using U2 = typename Arg2::BaseType;

        Function(Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg) :
        BinaryRealFunction<Arg1, Arg2, Callable>(callable, first_arg, second_arg) {

        }
    };

}
#endif