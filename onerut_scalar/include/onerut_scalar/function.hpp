#ifndef ONERUT_SCALAR_FUNCTION_2
#define ONERUT_SCALAR_FUNCTION_2

#include<cassert>
#include<type_traits>
#include<tuple>

#include<onerut_scalar/scalar_abstract_complex.hpp>
#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_scalar/scalar_abstract_integer.hpp>
#include<onerut_scalar/scalar_common_interface.hpp>
#include<onerut_scalar/utility_callable_on_tuple.hpp>
#include<onerut_scalar/utility_static_all_of.hpp>

namespace onerut_scalar {

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

    //    template <class _Callable, class _ReturnTag>
    //    class Function<_Callable, _ReturnTag> : public CommonInterface<typename _ReturnTag::OnerutBaseType > {
    //    public:
    //        using ReturnTag = _ReturnTag;
    //        Function(_Callable callable);
    //        typename _ReturnTag::BuildInCppType value() const final;
    //    private:
    //        _Callable callable;
    //    };

    // -------------------------------------------------------------------------
    // -----   Implementation:   -----------------------------------------------
    // -------------------------------------------------------------------------    

    template <class _Callable, class _ReturnTag, class... _Args>
    Function<_Callable, _ReturnTag, _Args...>::Function(
            _Callable callable, std::shared_ptr<typename _Args::OnerutBaseType>... args) :
    callable(callable),
    args(args...) {
    }

    // Functions extract(ptr) defined below 
    // are used in conjuction with callable_on_tuple function
    // used by Function<_Callable, _ReturnTag, _Args...>::value().

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

    // -------------------------------------------------------------------------

    //    template<typename _Callable, typename _ReturnTag>
    //    Function<_Callable, _ReturnTag>::Function(
    //            _Callable callable) :
    //    callable(callable) {
    //    }
    //
    //    template<typename _Callable, typename _ReturnTag>
    //    typename _ReturnTag::BuildInCppType
    //    Function<_Callable, _ReturnTag>::value() const {
    //        const auto& y = callable();
    //        return y;
    //    }

    // #########################################################################
    // ########## ONERUT-SCALAR-FUNCTION CLASES -- AUTOMATIC API ###############
    // #########################################################################

    // When you need to create a onerut-scalar-function you have to provide its type.
    // The explicite API above requires providing:
    // (1) callable type, (2) return type, and (3) argument types 
    // as template parameters.
    //
    // But the return type may be deduced from callable type and argumnet types.
    // Automatic API defined below is to provide onerut-scalar-function type
    // when callable type and argument types are provided by user,
    // but the return type is left for the deduction.
    
    // Using autmatic API you
    // no longer need to declare onerut-scalar-function type manually.
    // You take it out from DeduceFunction helper template
    // is which the desired onerut-scalar-function type is defined as
    // DeducedFunction member type.
    
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