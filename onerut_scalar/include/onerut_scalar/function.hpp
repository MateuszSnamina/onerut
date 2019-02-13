#ifndef ONERUT_SCALAR_FUNCTION_2
#define ONERUT_SCALAR_FUNCTION_2

#include<cassert>
#include<type_traits>
#include<tuple>

#include<onerut_scalar/scalar_abstract_complex.hpp>
#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_scalar/scalar_abstract_integer.hpp>
#include<onerut_scalar/callable_on_tuple.hpp>

namespace onerut_scalar {

    // #########################################################################

    namespace utility {
        template <typename ... Types>
        struct static_all_of;

        template <>
        struct static_all_of<>
        : std::true_type {
        };

        template <typename ... Types>
        struct static_all_of<std::false_type, Types...>
        : std::false_type {
        };

        template <typename ... Types>
        struct static_all_of<std::true_type, Types...>
        : static_all_of<Types...>::type {
        };
    }
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
    };

    struct ArgReal {
        using OnerutBaseType = Real;
        using BuildInCppType = double;
    };

    struct ArgComplex {
        using OnerutBaseType = Complex;
        using BuildInCppType = std::complex<double>;
    };

    // -------------------------------------------------------------------------

    template<class T>
    struct IsArg : public std::false_type {
        using type = std::false_type;
    };

    template<>
    struct IsArg<ArgInteger> : public std::true_type {
        using type = std::true_type;
    };

    template<>
    struct IsArg<ArgReal> : public std::true_type {
        using type = std::true_type;
    };

    template<>
    struct IsArg<ArgComplex> : public std::true_type {
        using type = std::true_type;
    };

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

    template <class _Callable, class _ReturnTag, class... _Args>
    class Function : public CommonInterface<typename _ReturnTag::OnerutBaseType > {
    public:
        using ReturnTag = _ReturnTag;
        static_assert(utility::static_all_of<typename IsArg<_Args>::type...>::value);
        Function(_Callable callable, std::shared_ptr<typename _Args::OnerutBaseType>... args);
        typename _ReturnTag::BuildInCppType value() const final;
    private:
        _Callable callable;
        std::tuple<std::shared_ptr<typename _Args::OnerutBaseType>... > args;
    };


    // -------------------------------------------------------------------------
    // -----   Implementation:   -----------------------------------------------
    // -------------------------------------------------------------------------    

    template <class _Callable, class _ReturnTag, class... _Args>
    Function<_Callable, _ReturnTag, _Args...>::Function(
            _Callable callable, std::shared_ptr<typename _Args::OnerutBaseType>... args) :
    callable(callable),
    args(args...) {
    }

    // the functions extract(ptr) are used in conjuction with callable_on_tuple

    long
    extract(std::shared_ptr<Integer> ptr) {
        return ptr->value_integer();
    }

    double
    extract(std::shared_ptr<Real> ptr) {
        return ptr->value_real();
    }

    std::complex<double>
    extract(std::shared_ptr<Complex> ptr) {
        return ptr->value_complex();
    }

    template<typename _Callable, typename _ReturnTag, typename... _Args>
    typename _ReturnTag::BuildInCppType Function<_Callable, _ReturnTag, _Args...>::value() const {
        return utility::callable_on_tuple(callable, args);
    }


    /*
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
     */
    // #########################################################################
    // #########  AUTOMATIC API  ###############################################
    // #########################################################################

    template<class T>
    struct BuildInCppType2ReturnTag {
    };

    template<>
    struct BuildInCppType2ReturnTag<long> {
        using ReturnTag = ReturnInteger;
    };

    template<>
    struct BuildInCppType2ReturnTag<double> {
        using ReturnTag = ReturnReal;
    };

    template<>
    struct BuildInCppType2ReturnTag<std::complex<double> > {
        using ReturnTag = ReturnComplex;
    };

    // -------------------------------------------------------------------------

    template <class _Callable, class... _Args>
    struct DeduceFunction {
        using DeducedBuildInCppReturnType = decltype(std::declval<_Callable>()(std::declval<typename _Args::BuildInCppType>()...));
        using DeducedReturnTag = typename BuildInCppType2ReturnTag<DeducedBuildInCppReturnType>::ReturnTag;
        using DeducedFunction = Function<_Callable, DeducedReturnTag, _Args...>;
    };

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