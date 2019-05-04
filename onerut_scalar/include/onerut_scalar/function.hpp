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
#include<onerut_scalar/utility_for_each_on_tuple.hpp>
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
    struct IsArgTag : public std::false_type {
        using type = std::false_type;
    };

    template<>
    struct IsArgTag<ArgInteger> : public std::true_type {
        using type = std::true_type;
    };

    template<>
    struct IsArgTag<ArgReal> : public std::true_type {
        using type = std::true_type;
    };

    template<>
    struct IsArgTag<ArgComplex> : public std::true_type {
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
    struct IsReturnTag : public std::false_type {
    };

    template<>
    struct IsReturnTag<ReturnInteger> : public std::true_type {
    };

    template<>
    struct IsReturnTag<ReturnReal> : public std::true_type {
    };

    template<>
    struct IsReturnTag<ReturnComplex> : public std::true_type {
    };

    // #########################################################################
    // ########## ONERUT SCALAR FUNCTION CLASES -- VERBOSE API #################
    // #########################################################################

    template <class _Callable, class _ReturnTag, class... _ArgTags>
    class Function : public CommonInterface<typename _ReturnTag::OnerutBaseType > {
    public:
        static_assert(IsReturnTag<_ReturnTag>::value);
        static_assert(utility::static_all_of<typename IsArgTag<_ArgTags>::type...>::value);
        using ReturnTag = _ReturnTag;
        Function(_Callable callable, std::shared_ptr<const typename _ArgTags::OnerutBaseType>... args);
        typename _ReturnTag::BuildInCppType value() const final;
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependence() const final;
    private:
        _Callable callable;
        std::tuple<std::shared_ptr<const typename _ArgTags::OnerutBaseType>... > args;
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

    template <class _Callable, class _ReturnTag, class... _ArgTags>
    Function<_Callable, _ReturnTag, _ArgTags...>::Function(
            _Callable callable, std::shared_ptr<const typename _ArgTags::OnerutBaseType>... args) :
    callable(callable),
    args(args...) {
#ifndef NDEBUG // Prevent compilation error of expression folding with empty macro (in release compilation).
        (assert(args), ...);
#endif        
    }

    // Functions extract(ptr) defined below 
    // are used in conjuction with callable_on_tuple function
    // used by Function<_Callable, _ReturnTag, _ArgTags...>::value().

    inline
    long
    extract(const std::shared_ptr<const Integer>& ptr) {
        assert(ptr);
        return ptr->value_integer();
    }

    inline
    double
    extract(const std::shared_ptr<const Real>& ptr) {
        assert(ptr);
        return ptr->value_real();
    }

    inline
    std::complex<double>
    extract(const std::shared_ptr<const Complex>& ptr) {
        assert(ptr);
        return ptr->value_complex();
    }

    template<typename _Callable, typename _ReturnTag, typename... _ArgTags>
    typename _ReturnTag::BuildInCppType Function<_Callable, _ReturnTag, _ArgTags...>::value() const {
        return utility::callable_on_tuple(callable, args);
    }

    template<typename _Callable, typename _ReturnTag, typename... _ArgTags>
    std::vector<std::weak_ptr<const onerut_dependence::Dependable>> Function<_Callable, _ReturnTag, _ArgTags...>::dependence() const {
        decltype(dependence()) result;
        const auto size = std::tuple_size<decltype(args)>::value;
        result.reserve(size);
        const auto adder_function =
                [&result](std::weak_ptr<const onerut_dependence::Dependable> arg) {
                    result.push_back(arg);
                };
        utility::for_each_on_tuple(adder_function, args);
        assert(0); //TODO
        return result;
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

    // -------------------------------------------------------------------------

    template<class T>
    struct BuildInCppType2ReturnTag;

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

    template <class _Callable, class... _ArgTags>
    struct DeduceFunction {
        static_assert(utility::static_all_of<typename IsArgTag<_ArgTags>::type...>::value);
        using DeducedBuildInCppReturnType = decltype(std::declval<_Callable>()(std::declval<typename _ArgTags::BuildInCppType>()...));
        using DeducedReturnTag = typename BuildInCppType2ReturnTag<DeducedBuildInCppReturnType>::ReturnTag;
        using DeducedFunction = Function<_Callable, DeducedReturnTag, _ArgTags...>;
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