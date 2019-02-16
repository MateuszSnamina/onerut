#ifndef ONERUT_PARSER_TEMPLATES
#define ONERUT_PARSER_TEMPLATES

#include<algorithm>
#include<vector>

#include<onerut_parser/function_factory_abstract.hpp>
#include<onerut_parser/compile_result_utility.hpp>
#include<onerut_scalar/function.hpp>
#include<onerut_scalar/utility_static_all_of.hpp>

//#include<iostream> //Debug TODO remove

namespace onerut_parser {

    // *************************************************************************
    // *********   ArgPreparator -- helper class   *****************************
    // *************************************************************************    

    template<typename T>
    class ArgPreparator {
    };

    template<>
    struct ArgPreparator<onerut_scalar::ArgInteger> {
        static bool do_match(const CompileResultDeref & arg);
        static std::shared_ptr<onerut_scalar::Integer> extract(const CompileResultDeref & arg);
    };

    template<>
    struct ArgPreparator<onerut_scalar::ArgReal> {
        static bool do_match(const CompileResultDeref & arg);
        static std::shared_ptr<onerut_scalar::Real> extract(const CompileResultDeref & arg);
    };

    template<>
    struct ArgPreparator<onerut_scalar::ArgComplex> {
        static bool do_match(const CompileResultDeref & arg);
        static std::shared_ptr<onerut_scalar::Complex> extract(const CompileResultDeref & arg);
    };

    inline
    bool
    ArgPreparator<onerut_scalar::ArgInteger>::do_match(const CompileResultDeref & arg) {
        return utility::is_integer(arg);
    }

    inline
    std::shared_ptr<onerut_scalar::Integer>
    ArgPreparator<onerut_scalar::ArgInteger>::extract(const CompileResultDeref & arg) {
        return utility::to_integer(arg);
    }

    inline
    bool
    ArgPreparator<onerut_scalar::ArgReal>::do_match(const CompileResultDeref & arg) {
        return utility::is_real_or_integer(arg);
    }

    inline
    std::shared_ptr<onerut_scalar::Real>
    ArgPreparator<onerut_scalar::ArgReal>::extract(const CompileResultDeref & arg) {
        return utility::to_real(arg);
    }

    inline
    bool
    ArgPreparator<onerut_scalar::ArgComplex>::do_match(const CompileResultDeref & arg) {
        return utility::is_real_or_integer_or_complex(arg);
    }

    inline
    std::shared_ptr<onerut_scalar::Complex>
    ArgPreparator<onerut_scalar::ArgComplex>::extract(const CompileResultDeref & arg) {
        return utility::to_complex(arg);
    }

    // *************************************************************************
    // *********   helper functions                             ****************
    // *************************************************************************    

    template<typename Callable, typename... ArgTags>
    std::optional<CompileResult>
    _make_function_or_empty(
            Callable callable,
            typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, CompileResultDeref>::type... arg_compile_results_deref) {
        static_assert(!std::is_same<Callable, std::nullptr_t>::value);
        static_assert(onerut_scalar::utility::static_all_of<typename onerut_scalar::IsArgTag<ArgTags>::type...>::value);
        (assert(arg_compile_results_deref.is_either_value_or_type()), ...);
        if (!(ArgPreparator<ArgTags>::do_match(arg_compile_results_deref) && ... && true))
            return std::nullopt;
        using OnerutScalarFunctionType = typename onerut_scalar::DeduceFunction<Callable, ArgTags...>::DeducedFunction;
        using ReturnOnerutBaseType = typename OnerutScalarFunctionType::ReturnTag::OnerutBaseType;
        return CompileResult::from_value<ReturnOnerutBaseType>(
                std::make_shared<OnerutScalarFunctionType> (callable, ArgPreparator<ArgTags>::extract(arg_compile_results_deref)...));
    }

    template<typename Callable, typename... ArgTags>
    std::optional<CompileResult>
    _make_function_or_empty(
            Callable callable,
            typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, CompileResult>::type... arg_compile_results) {
        static_assert(!std::is_same<Callable, std::nullptr_t>::value);
        static_assert(onerut_scalar::utility::static_all_of<typename onerut_scalar::IsArgTag<ArgTags>::type...>::value);
        return _make_function_or_empty<Callable, ArgTags...>(callable, arg_compile_results.dereference()...);
    }

    // *************************************************************************
    // *********   Low level onerut-scalar-function factories    ***************
    // *********   returning std::optional<CompileResult>        ***************
    // *********   (create a function or nullopt)                ***************    
    // *************************************************************************    

    template<typename Callable, typename... ArgTags>
    struct ScalarFunctionFactory {
        static std::optional<CompileResult> make_function_or_empty(
                Callable callable,
                typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, CompileResult>::type... arg_compile_results);
    };

    template<typename... ArgTags>
    struct ScalarFunctionFactory<std::nullptr_t, ArgTags...> {
        static std::optional<CompileResult> make_function_or_empty(
                std::nullptr_t,
                typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, CompileResult>::type... arg_compile_results);
    };

    template<typename Callable, typename... ArgTags>
    std::optional<CompileResult>
    ScalarFunctionFactory<Callable, ArgTags...>::make_function_or_empty(
            Callable callable,
            typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, CompileResult>::type... arg_compile_results) {
        return _make_function_or_empty<Callable, ArgTags...>(callable, arg_compile_results...);
    }

    template<typename... ArgTags>
    std::optional<CompileResult>
    ScalarFunctionFactory<std::nullptr_t, ArgTags...>::make_function_or_empty(
            std::nullptr_t,
            typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, CompileResult>::type... arg_compile_results) {
        return std::nullopt;
    }

    // *************************************************************************
    // *********   High level onerut-scalar-function factories    **************
    // *********   returning CompileResult                        **************
    // *********   (create a function or an error)                **************
    // *************************************************************************    
    // *********   These factories comply                         **************
    // *********   AbstractAbstracctFactory interface             **************
    // *********   and may be stored in                           **************
    // *********   GlobalFunctionFactories container              **************
    // *************************************************************************

    template<typename CallableReal, typename CallableComplex>
    class OverloadScalarUnaryFunctionFactory : public UnaryFunctionFactory {
    public:
        OverloadScalarUnaryFunctionFactory(
                CallableReal callable_real,
                CallableComplex callable_complex);
        CompileResult make_function_otherwise_make_error(
                CompileResult arg) const override;
    private:
        CallableReal callable_real;
        CallableComplex callable_complex;
    };

    template<typename CallableReal, typename CallableComplex >
    OverloadScalarUnaryFunctionFactory<CallableReal, CallableComplex>::OverloadScalarUnaryFunctionFactory(
            CallableReal callable_real,
            CallableComplex callable_complex) :
    callable_real(callable_real),
    callable_complex(callable_complex) {
    }

    template<typename CallableReal, typename CallableComplex >
    CompileResult OverloadScalarUnaryFunctionFactory<CallableReal, CallableComplex>::make_function_otherwise_make_error(
            CompileResult arg_compile_result) const {
        const auto & arg_compile_result_deref = arg_compile_result.dereference();
        if (!arg_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (const auto & result = ScalarFunctionFactory<CallableReal, onerut_scalar::ArgReal>::make_function_or_empty(callable_real, arg_compile_result))
            return *result;
        if (const auto & result = ScalarFunctionFactory<CallableComplex, onerut_scalar::ArgComplex>::make_function_or_empty(callable_complex, arg_compile_result))
            return *result;
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    template<typename CallableReal, typename CallableComplex>
    class OverloadScalarBinaryFunctionFactory : public BinaryFunctionFactory {
    public:
        OverloadScalarBinaryFunctionFactory(
                CallableReal callable_real,
                CallableComplex callable_complex);
        CompileResult make_function_otherwise_make_error(
                CompileResult first_arg,
                CompileResult second_arg) const override;
    private:
        CallableReal callable_real;
        CallableComplex callable_complex;
    };

    template<typename CallableReal, typename CallableComplex >
    OverloadScalarBinaryFunctionFactory<CallableReal, CallableComplex>::OverloadScalarBinaryFunctionFactory(
            CallableReal callable_real,
            CallableComplex callable_complex) :
    callable_real(callable_real),
    callable_complex(callable_complex) {
    }

    template<typename CallableReal, typename CallableComplex >
    CompileResult OverloadScalarBinaryFunctionFactory<CallableReal, CallableComplex>::make_function_otherwise_make_error(
            CompileResult first_arg_compile_result,
            CompileResult second_arg_compile_result) const {
        const auto & first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const auto & second_arg_compile_result_deref = second_arg_compile_result.dereference();
        if (!first_arg_compile_result_deref.is_either_value_or_type() || !second_arg_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (const auto & result = ScalarFunctionFactory<CallableReal, onerut_scalar::ArgReal, onerut_scalar::ArgReal>::make_function_or_empty(callable_real, first_arg_compile_result, second_arg_compile_result))
            return *result;
        if (const auto & result = ScalarFunctionFactory<CallableComplex, onerut_scalar::ArgComplex, onerut_scalar::ArgComplex>::make_function_or_empty(callable_complex, first_arg_compile_result, second_arg_compile_result))
            return *result;
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }
    // -------------------------------------------------------------------------
    //HELPER:

    template<typename Callable, typename ArgTag, unsigned nary_left_to_add, typename... ArgTags>
    struct NaryScalarFunctionFactoryImpl {
        static_assert(onerut_scalar::IsArgTag<ArgTag>::value);
        using ScalarFunctionFactoryType = typename NaryScalarFunctionFactoryImpl<Callable, ArgTag, nary_left_to_add - 1, ArgTag, ArgTags...>::ScalarFunctionFactoryType;
    };

    template<typename Callable, typename ArgTag, typename... ArgTags>
    struct NaryScalarFunctionFactoryImpl<Callable, ArgTag, 0u, ArgTags...> {
        static_assert(onerut_scalar::IsArgTag<ArgTag>::value);
        using ScalarFunctionFactoryType = ScalarFunctionFactory<Callable, ArgTags...>;
    };

    template<typename Callable, typename ArgTag, unsigned nary>
    struct NaryScalarFunctionFactory {
        static_assert(onerut_scalar::IsArgTag<ArgTag>::value);
        using ScalarFunctionFactoryType = typename NaryScalarFunctionFactoryImpl<Callable, ArgTag, nary>::ScalarFunctionFactoryType;
    };

    // -------------------------------------------------------------------------

    //HELPER:

    template<class ScalarFunctionFactory, unsigned nary, unsigned N>
    struct _NaryMakeFunctionOrEmptyInpl {
        using ArrayT = std::array<CompileResult, nary>;

        template<typename Callable, typename... Args>
        static inline std::optional<CompileResult>
        apply(const Callable & callable, const ArrayT& array, Args&&... args) {
            return _NaryMakeFunctionOrEmptyInpl<ScalarFunctionFactory, nary, N - 1 > ::apply(
                    callable,
                    array,
                    array[N - 1], std::forward<Args>(args)...);
        }
    };

    template<class ScalarFunctionFactory, unsigned nary>
    struct _NaryMakeFunctionOrEmptyInpl<ScalarFunctionFactory, nary, 0> {
        using ArrayT = std::array<CompileResult, nary>;

        template<typename Callable, typename... Args>
        static inline std::optional<CompileResult>
        apply(const Callable & callable, const ArrayT& /*array*/, Args&&... args) {
            return ScalarFunctionFactory::make_function_or_empty(callable, std::forward<Args>(args)...);
            //return std::nullopt;
        }
    };

    // -------------------------------------------------------------------------    
    // -------------------------------------------------------------------------        

    template<class ScalarFunctionFactory, unsigned nary, typename Callable>
    inline
    std::optional<CompileResult>
    _nary_make_function_or_empty(const Callable & callable, const std::array<CompileResult, nary>& array) {
        //    using ArrayT = std::array<CompileResult, nary>;
        return _NaryMakeFunctionOrEmptyInpl<ScalarFunctionFactory, nary, nary>::apply(callable, array);
    }

    // -------------------------------------------------------------------------

    // new style:

    template<unsigned nary, typename CallableReal, typename CallableComplex>
    class OverloadScalarFunctionFactory : public NaryFunctionFactory<nary> {
    public:
        OverloadScalarFunctionFactory(
                CallableReal callable_real,
                CallableComplex callable_complex);
        CompileResult make_function_otherwise_make_error(
                std::array<CompileResult, nary> args) const override;
    private:
        CallableReal callable_real;
        CallableComplex callable_complex;
    };

    template<unsigned nary, typename CallableReal, typename CallableComplex >
    OverloadScalarFunctionFactory<nary, CallableReal, CallableComplex>::OverloadScalarFunctionFactory(
            CallableReal callable_real,
            CallableComplex callable_complex) :
    callable_real(callable_real),
    callable_complex(callable_complex) {
    }

    template<unsigned nary, typename CallableReal, typename CallableComplex>
    CompileResult OverloadScalarFunctionFactory<nary, CallableReal, CallableComplex>::make_function_otherwise_make_error(
            std::array<CompileResult, nary> args_compile_result) const {
        std::array<CompileResultDeref, nary> args_compile_result_deref;
        std::transform(cbegin(args_compile_result), cend(args_compile_result), begin(args_compile_result_deref),
                [](const CompileResult & compile_result)->CompileResultDeref {
                    return compile_result.dereference();
                });
        if (!std::all_of(cbegin(args_compile_result_deref), cend(args_compile_result_deref),
                [](const CompileResultDeref & compile_result_deref) {
                    return compile_result_deref.is_either_value_or_type();
                })) {
        return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
    }

        using RealFunctionFactoryType = typename NaryScalarFunctionFactory<CallableReal, onerut_scalar::ArgReal, nary>::ScalarFunctionFactoryType;
        using ComplexFunctionFactoryType = typename NaryScalarFunctionFactory<CallableComplex, onerut_scalar::ArgComplex, nary>::ScalarFunctionFactoryType;

        if (const auto & result = _nary_make_function_or_empty<RealFunctionFactoryType, nary, CallableReal>(callable_real, args_compile_result))
            return *result;

        if (const auto & result = _nary_make_function_or_empty<ComplexFunctionFactoryType, nary, CallableComplex>(callable_complex, args_compile_result))
            return *result;

        //zxz



        //       
        //        const auto & first_arg_compile_result_deref = first_arg_compile_result.dereference();
        //        const auto & second_arg_compile_result_deref = second_arg_compile_result.dereference();
        //        if (!first_arg_compile_result_deref.is_either_value_or_type() || !second_arg_compile_result_deref.is_either_value_or_type())
        //            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        //        if (const auto & result = ScalarFunctionFactory<CallableReal, onerut_scalar::ArgReal, onerut_scalar::ArgReal>::make_function_or_empty(callable_real, first_arg_compile_result, second_arg_compile_result))
        //            return *result;
        //        if (const auto & result = ScalarFunctionFactory<CallableComplex, onerut_scalar::ArgComplex, onerut_scalar::ArgComplex>::make_function_or_empty(callable_complex, first_arg_compile_result, second_arg_compile_result))
        //            return *result;
        //        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }
}

#endif
