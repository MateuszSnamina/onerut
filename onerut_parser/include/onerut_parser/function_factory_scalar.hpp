#ifndef ONERUT_PARSER_TEMPLATES
#define ONERUT_PARSER_TEMPLATES

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
    // *********   basic onerut-scalar-function factory         ****************
    // *************************************************************************    
    
    //TODO delete _2 suffix
    template<typename Callable, typename... ArgTags>
    std::optional<CompileResult>
    _make_function_or_empty_2(Callable callable, typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, CompileResultDeref>::type... arg_compile_results_deref) {
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
    _make_function_or_empty(Callable callable, typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, CompileResult>::type... arg_compile_results) {
        static_assert(!std::is_same<Callable, std::nullptr_t>::value);
        static_assert(onerut_scalar::utility::static_all_of<typename onerut_scalar::IsArgTag<ArgTags>::type...>::value);
        return _make_function_or_empty_2<Callable, ArgTags...>(callable, arg_compile_results.dereference()...);
    }

    // *************************************************************************
    // *********   Low level onerut-scalar-function factories    ***************
    // *********   returning std::optional<CompileResult>        ***************
    // *********   (create a function or nullopt)                ***************    
    // *************************************************************************    
    
    
    template<typename Callable, typename... ArgTags>
    struct ScalarFunctionFactory {

        static std::optional<CompileResult> make_function_or_empty(Callable callable, typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, CompileResult>::type... arg_compile_results) {
            return _make_function_or_empty<Callable, ArgTags...>(callable, arg_compile_results...);
        }
    };

    template<typename... ArgTags>
    struct ScalarFunctionFactory<std::nullptr_t, ArgTags...> {

        static std::optional<CompileResult> make_function_or_empty(std::nullptr_t, typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, CompileResult>::type... arg_compile_results) {
            return std::nullopt;
        };
    };

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
    class UnaryRealComplexFunctionFactory : public UnaryFunctionFactory {
    public:
        UnaryRealComplexFunctionFactory(CallableReal callable_real, CallableComplex callable_complex);
        CompileResult make_function_otherwise_make_error(CompileResult arg) const override;
    private:
        CallableReal callable_real;
        CallableComplex callable_complex;
    };

    template<typename CallableReal, typename CallableComplex >
    UnaryRealComplexFunctionFactory<CallableReal, CallableComplex>::UnaryRealComplexFunctionFactory(CallableReal callable_real, CallableComplex callable_complex) :
    callable_real(callable_real),
    callable_complex(callable_complex) {
    }

    template<typename CallableReal, typename CallableComplex >
    CompileResult UnaryRealComplexFunctionFactory<CallableReal, CallableComplex>::make_function_otherwise_make_error(CompileResult arg_compile_result) const {
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
    class BinaryRealComplexFunctionFactory : public BinaryFunctionFactory {
    public:
        BinaryRealComplexFunctionFactory(CallableReal callable_real, CallableComplex callable_complex);
        CompileResult make_function_otherwise_make_error(CompileResult first_arg, CompileResult second_arg) const override;
    private:
        CallableReal callable_real;
        CallableComplex callable_complex;
    };

    template<typename CallableReal, typename CallableComplex >
    BinaryRealComplexFunctionFactory<CallableReal, CallableComplex>::BinaryRealComplexFunctionFactory(CallableReal callable_real, CallableComplex callable_complex) :
    callable_real(callable_real),
    callable_complex(callable_complex) {
    }

    template<typename CallableReal, typename CallableComplex >
    CompileResult BinaryRealComplexFunctionFactory<CallableReal, CallableComplex>::make_function_otherwise_make_error(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
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

}

#endif
