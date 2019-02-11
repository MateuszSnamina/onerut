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
    // ########## ONERUT SCALAR FUNCTION CLASES -- VERBOSE API #################
    // #########################################################################

    template <class _ReturnTag, class _Callable, class... _Args>
    class Function;

    // -------------------------------------------------------------------------

    template<typename _Callable, typename _ReturnTag, typename _Arg1>
    class Function<_Callable, _ReturnTag, _Arg1> : public CommonInterface<typename _ReturnTag::OnerutBaseType > {
    public:
        using ReturnTag = _ReturnTag;
        static_assert(IsArg<_Arg1>::value);
        using U1 = typename _Arg1::OnerutBaseType;
        Function(_Callable callable, std::shared_ptr<U1> arg);
        typename _ReturnTag::BuildInCppType value() const final;
    private:
        _Callable callable;
        const std::shared_ptr<U1> arg;
    };

    template<typename _Callable, typename _ReturnTag, typename _Arg1, typename _Arg2>
    class Function<_Callable, _ReturnTag, _Arg1, _Arg2> : public CommonInterface<typename _ReturnTag::OnerutBaseType > {
    public:
        using ReturnTag = _ReturnTag;
        static_assert(IsArg<_Arg1>::value);
        static_assert(IsArg<_Arg2>::value);
        using U1 = typename _Arg1::OnerutBaseType;
        using U2 = typename _Arg2::OnerutBaseType;
        Function(_Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg);
        typename _ReturnTag::BuildInCppType value() const final;
    private:
        _Callable callable;
        const std::shared_ptr<U1> first_arg;
        const std::shared_ptr<U2> second_arg;
    };

    // -------------------------------------------------------------------------
    // -----   Implementation:   -----------------------------------------------
    // -------------------------------------------------------------------------

    template<typename _Callable, typename _ReturnTag, typename _Arg1>
    Function<_Callable, _ReturnTag, _Arg1>::Function(
            _Callable callable, std::shared_ptr<U1> arg) :
    callable(callable),
    arg(arg) {
        assert(arg);
    }

    template<typename _Callable, typename _ReturnTag, typename _Arg1>
    typename _ReturnTag::BuildInCppType
    Function<_Callable, _ReturnTag, _Arg1>::value() const {
        const auto& x = _Arg1().extract(arg);
        const auto& y = callable(x);
        return y;
    }

    // -------------------------------------------------------------------------

    template<typename _Callable, typename _ReturnTag, typename _Arg1, typename _Arg2>
    Function<_Callable, _ReturnTag, _Arg1, _Arg2>::Function(
            _Callable callable, std::shared_ptr<U1> first_arg, std::shared_ptr<U2> second_arg) :
    callable(callable),
    first_arg(first_arg),
    second_arg(second_arg) {
        assert(first_arg);
        assert(second_arg);
    }

    template<typename _Callable, typename _ReturnTag, typename _Arg1, typename _Arg2>
    typename _ReturnTag::BuildInCppType
    Function<_Callable, _ReturnTag, _Arg1, _Arg2>::value() const {
        const auto& firts_x = _Arg1().extract(first_arg);
        const auto& second_x = _Arg2().extract(second_arg);
        const auto y = callable(firts_x, second_x);
        return y;
    }

    // #########################################################################
    // ########## ONERUT SCALAR FUNCTION CLASES -- CONCISE API #################
    // #########################################################################
    /*
    template<class T>
    struct DeducedArg {
    };

    template<>
    struct DeducedArg<long> {
        using Arg = ArgInteger;
    };

    template<>
    struct DeducedArg<double> {
        using Arg = ArgReal;
    };

    template<>
    struct DeducedArg<std::complex<double> > {
        using Arg = ArgComplex;
    };

    // -------------------------------------------------------------------------

    template<class T>
    struct DeducedReturn {
    };

    template<>
    struct DeducedReturn<long> {
        using Return = ReturnInteger;
    };

    template<>
    struct DeducedReturn<double> {
        using Return = ReturnReal;
    };

    template<>
    struct DeducedReturn<std::complex<double> > {
        using Return = ReturnComplex;
    };

    // -------------------------------------------------------------------------

    template<class >
    struct CallableInfo {
    };

    template<class CppReturn, class CppArg>
    struct CallableInfo<CppReturn(*)(CppArg)> {
        using DeducedFunPtr = CppReturn(*)(CppArg);
        using DeducedReturn = typename DeducedReturn<CppReturn>::Return;
        using DeducedArg = typename DeducedArg<CppArg>::Arg;
        using DeducedFunction = Function<DeducedFunPtr, DeducedReturn, DeducedArg>;
    };

    template<class CppReturn, class CppArg1, class CppArg2>
    struct CallableInfo<CppReturn(*)(CppArg1, CppArg2)> {
        using DeducedFunPtr = CppReturn(*)(CppArg1, CppArg2);
        using DeducedReturn = typename DeducedReturn<CppReturn>::Return;
        using DeducedArg1 = typename DeducedArg<CppArg1>::Arg;
        using DeducedArg2 = typename DeducedArg<CppArg2>::Arg;
        using DeducedFunction = Function<DeducedFunPtr, DeducedReturn, DeducedArg1, DeducedArg2>;
    };
     */
    // -------------------------------------------------------------------------

}

#endif