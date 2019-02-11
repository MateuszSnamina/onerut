#ifndef ONERUT_SCALAR_FUNCTION_2
#define ONERUT_SCALAR_FUNCTION_2

#include<cassert>
#include<type_traits>

#include<onerut_scalar/scalar_abstract_complex.hpp>
#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_scalar/scalar_abstract_integer.hpp>

namespace onerut_scalar {

    // #########################################################################
    // ########## HELPER CLASSES ###############################################
    // #########################################################################

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

    long CommonInterface<Integer>::value_integer() const {
        return value();
    }

    double CommonInterface<Real>::value_real() const {
        return value();
    }

    std::complex<double> CommonInterface<Complex>::value_complex() const {
        return value();
    }

    // #########################################################################
    // #######  ONERUT SCALAR  FUNCTION ARGUMENT TYPE TAG-CLASSES  #############
    // #########################################################################

    struct ArgInteger {
        using OnerutBaseType = Integer;
        using BuildInCppType = long;
        template<class T>
        long extract(std::shared_ptr<T> arg) const;
    };

    struct ArgReal {
        using OnerutBaseType = Real;
        using BuildInCppType = double;
        template<class T>
        double extract(std::shared_ptr<T> arg) const;
    };

    struct ArgComplex {
        using OnerutBaseType = Complex;
        using BuildInCppType = std::complex<double>;
        template<class T>
        std::complex<double> extract(std::shared_ptr<T> arg) const;
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
    // -----   Implementation:   -----------------------------------------------
    // -------------------------------------------------------------------------

    template<class T>
    long ArgInteger::extract(std::shared_ptr<T> arg) const {
        static_assert(std::is_base_of<OnerutBaseType, T>::value);
        return arg->value_integer();
    }

    template<class T>
    double ArgReal::extract(std::shared_ptr<T> arg) const {
        static_assert(std::is_base_of<OnerutBaseType, T>::value);
        return arg->value_real();
    }

    template<class T>
    std::complex<double> ArgComplex::extract(std::shared_ptr<T> arg) const {
        static_assert(std::is_base_of<OnerutBaseType, T>::value);
        return arg->value_complex();
    }

    // #########################################################################
    // #######  ONERUT SCALAR FUNCTION RETURNS TYPE TAG-CLASSES  ###############
    // #########################################################################

    struct ReturnInteger {
        using OnerutBaseType = Integer;
        using BuildInCppType = long;
    };

    struct ReturnReal {
        using OnerutBaseType = Real;
        using BuildInCppType = double;
    };

    struct ReturnComplex {
        using OnerutBaseType = Complex;
        using BuildInCppType = std::complex<double>;
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

    // #########################################################################
    // ########## ONERUT SCALAR FUNCTION CLASES  ###############################
    // #########################################################################


    template <class Return, class Callable, class... Args>
    class Function;

    // -------------------------------------------------------------------------

    template<typename Callable, typename ReturnTag, typename Arg1>
    class Function<Callable, ReturnTag, Arg1> : public CommonInterface<typename ReturnTag::OnerutBaseType > {
    public:
        static_assert(IsArg<Arg1>::value);
        using U1 = typename Arg1::OnerutBaseType;
        Function(Callable callable, std::shared_ptr<U1> arg);
        typename ReturnTag::BuildInCppType value() const final;
    private:
        Callable callable;
        const std::shared_ptr<U1> arg;
    };

    template<typename Callable, typename ReturnTag, typename Arg1, typename Arg2>
    class Function<Callable, ReturnTag, Arg1, Arg2> : public CommonInterface<typename ReturnTag::OnerutBaseType > {
    public:
        static_assert(IsArg<Arg1>::value);
        static_assert(IsArg<Arg2>::value);
        using U1 = typename Arg1::OnerutBaseType;
        using U2 = typename Arg2::OnerutBaseType;
        Function(Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg);
        typename ReturnTag::BuildInCppType value() const final;
    private:
        Callable callable;
        const std::shared_ptr<U1> first_arg;
        const std::shared_ptr<U2> second_arg;
    };

    // -------------------------------------------------------------------------
    // -----   Implementation:   -----------------------------------------------
    // -------------------------------------------------------------------------

    template<typename Callable, typename ReturnTag, typename Arg1>
    Function<Callable, ReturnTag, Arg1>::Function(
            Callable callable, std::shared_ptr<U1> arg) :
    callable(callable),
    arg(arg) {
        assert(arg);
    }

    template<typename Callable, typename ReturnTag, typename Arg1>
    typename ReturnTag::BuildInCppType
    Function<Callable, ReturnTag, Arg1>::value() const {
        const auto& x = Arg1().extract(arg);
        const auto& y = callable(x);
        return y;
    }

    // -------------------------------------------------------------------------

    template<typename Callable, typename ReturnTag, typename Arg1, typename Arg2>
    Function<Callable, ReturnTag, Arg1, Arg2>::Function(
            Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg) :
    callable(callable),
    first_arg(first_arg),
    second_arg(second_arg) {
        assert(first_arg);
        assert(second_arg);
    }

    template<typename Callable, typename ReturnTag, typename Arg1, typename Arg2>
    typename ReturnTag::BuildInCppType
    Function<Callable, ReturnTag, Arg1, Arg2>::value() const {
        const auto& firts_x = Arg1().extract(first_arg);
        const auto& second_x = Arg2().extract(second_arg);
        const auto y = callable(firts_x, second_x);
        return y;
    }

}
#endif