#ifndef ONERUT_PARSER_TEMPLATES
#define ONERUT_PARSER_TEMPLATES

#include<vector>

#include<onerut_parser/function_abstract.hpp>
#include<onerut_parser/compile_result_utility.hpp>
#include<onerut_scalar/function.hpp>

//#include<iostream> //Debug TODO remove

namespace onerut_parser {

    template<typename Callable>
    std::optional<CompileResult>
    _unary_real_function(Callable callable, CompileResult arg_compile_result) {
        const auto & arg_compile_result_deref = arg_compile_result.dereference();
        assert(arg_compile_result_deref.is_either_value_or_type());
        if (utility::is_real_or_integer(arg_compile_result_deref)) {
            const auto & arg_real = utility::to_real(arg_compile_result_deref);
            using FunctionType = typename onerut_scalar::DeduceFunction<Callable, onerut_scalar::ArgReal>::DeducedFunction;
            using ReturnOnerutBaseType = typename FunctionType::ReturnTag::OnerutBaseType;
            return CompileResult::from_value<ReturnOnerutBaseType>(std::make_shared<FunctionType>(callable, arg_real));
        }
        return std::nullopt;
    }

    template<typename Callable>
    std::optional<CompileResult>
    _binary_real_function(Callable callable, CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) {
        const auto & first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const auto & second_arg_compile_result_deref = second_arg_compile_result.dereference();
        assert(first_arg_compile_result_deref.is_either_value_or_type() && second_arg_compile_result_deref.is_either_value_or_type());
        if (utility::is_real_or_integer(first_arg_compile_result_deref) &&
                utility::is_real_or_integer(second_arg_compile_result_deref)) {
            const auto & first_arg_real = utility::to_real(first_arg_compile_result_deref);
            const auto & second_arg_real = utility::to_real(second_arg_compile_result_deref);
            using FunctionType = typename onerut_scalar::DeduceFunction<Callable, onerut_scalar::ArgReal, onerut_scalar::ArgReal>::DeducedFunction;
            using ReturnOnerutBaseType = typename FunctionType::ReturnTag::OnerutBaseType;
            return CompileResult::from_value<ReturnOnerutBaseType>(std::make_shared<FunctionType> (callable, first_arg_real, second_arg_real));
        }
        return std::nullopt;
    }

    template<typename Callable>
    std::optional<CompileResult>
    _unary_complex_function(Callable callable, CompileResult arg_compile_result) {
        const auto & arg_compile_result_deref = arg_compile_result.dereference();
        if (arg_compile_result_deref.is_either_value_or_type());
        if (utility::is_real_or_integer_or_complex(arg_compile_result_deref)) {
            const auto & arg_complex = utility::to_complex(arg_compile_result_deref);
            using FunctionType = typename onerut_scalar::DeduceFunction<Callable, onerut_scalar::ArgComplex>::DeducedFunction;
            using ReturnOnerutBaseType = typename FunctionType::ReturnTag::OnerutBaseType;
            return CompileResult::from_value<ReturnOnerutBaseType>(std::make_shared<FunctionType> (callable, arg_complex));
        }
        return std::nullopt;
    }

    template<typename Callable>
    std::optional<CompileResult>
    _binary_complex_function(Callable callable, CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) {
        const auto & first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const auto & second_arg_compile_result_deref = second_arg_compile_result.dereference();
        if (!first_arg_compile_result_deref.is_either_value_or_type() || !second_arg_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (utility::is_real_or_integer_or_complex(first_arg_compile_result_deref) &&
                utility::is_real_or_integer_or_complex(second_arg_compile_result_deref)) {
            const auto & first_arg_complex = utility::to_complex(first_arg_compile_result_deref);
            const auto & second_arg_complex = utility::to_complex(second_arg_compile_result_deref);
            using FunctionType = typename onerut_scalar::DeduceFunction<Callable, onerut_scalar::ArgComplex, onerut_scalar::ArgComplex>::DeducedFunction;
            using ReturnOnerutBaseType = typename FunctionType::ReturnTag::OnerutBaseType;
            return CompileResult::from_value<ReturnOnerutBaseType>(std::make_shared<FunctionType> (callable, first_arg_complex, second_arg_complex));
        }
        return std::nullopt;
    }

    // WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
    // ---------------------------------------------------------------------------        

    template<typename Callable>
    class UnaryRealFunction : public UnaryFunction {
    public:
        // Callable obj should support: obj(double) -> [long, double or cx_double]        
        UnaryRealFunction(Callable callable);
        CompileResult get_compile_result(CompileResult arg) const override;
    private:
        Callable callable;
    };

    template<typename Callable>
    UnaryRealFunction<Callable>::UnaryRealFunction(Callable callable) :
    callable(callable) {
    }

    template<typename Callable>
    CompileResult UnaryRealFunction<Callable>::get_compile_result(CompileResult arg_compile_result) const {
        const auto & arg_compile_result_deref = arg_compile_result.dereference();
        if (!arg_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (const auto & result = _unary_real_function(callable, arg_compile_result))
            return *result;
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    template<typename Callable>
    class BinaryRealFunction : public BinaryFunction {
    public:
        // Callable obj should support: obj(double, double) -> [long, double or cx_double]                
        BinaryRealFunction(Callable callable);
        CompileResult get_compile_result(CompileResult first_arg, CompileResult second_arg) const override;
    private:
        Callable callable;
    };

    template<typename Callable>
    BinaryRealFunction<Callable>::BinaryRealFunction(Callable callable) :
    callable(callable) {
    }

    template<typename Callable>
    CompileResult BinaryRealFunction<Callable>::get_compile_result(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        const auto & first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const auto & second_arg_compile_result_deref = second_arg_compile_result.dereference();
        if (!first_arg_compile_result_deref.is_either_value_or_type() || !second_arg_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (const auto & result = _binary_real_function(callable, first_arg_compile_result, second_arg_compile_result))
            return *result;
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // ---------------------------------------------------------------------------        

    template<typename Callable>
    class UnaryComplexFunction : public UnaryFunction {
    public:
        // Callable obj should support: obj(cx_double) -> [long, double or cx_double]
        UnaryComplexFunction(Callable callable);
        CompileResult get_compile_result(CompileResult arg) const override;
    private:
        Callable callable;
    };

    template<typename Callable>
    UnaryComplexFunction<Callable>::UnaryComplexFunction(Callable callable) :
    callable(callable) {
    }

    template<typename Callable>
    CompileResult UnaryComplexFunction<Callable>::get_compile_result(CompileResult arg_compile_result) const {
        const auto & arg_compile_result_deref = arg_compile_result.dereference();
        if (!arg_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (const auto & result = _unary_complex_function(callable, arg_compile_result))
            return *result;
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    template<typename Callable>
    class BinaryComplexFunction : public BinaryFunction {
    public:
        // Callable obj should support: obj(cx_double, cx_double) -> [long, double or cx_double]
        BinaryComplexFunction(Callable callable);
        CompileResult get_compile_result(CompileResult first_arg, CompileResult second_arg) const override;
    private:
        Callable callable;
    };

    template<typename Callable>
    BinaryComplexFunction<Callable>::BinaryComplexFunction(Callable callable) :
    callable(callable) {
    }

    template<typename Callable>
    CompileResult BinaryComplexFunction<Callable>::get_compile_result(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        const auto & first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const auto & second_arg_compile_result_deref = second_arg_compile_result.dereference();
        if (!first_arg_compile_result_deref.is_either_value_or_type() || !second_arg_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (const auto & result = _binary_complex_function(callable, first_arg_compile_result, second_arg_compile_result))
            return *result;
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    template<typename CallableReal, typename CallableComplex>
    class UnaryRealComplexFunction : public UnaryFunction {
    public:
        UnaryRealComplexFunction(CallableReal callable_real, CallableComplex callable_complex);
        CompileResult get_compile_result(CompileResult arg) const override;
    private:
        CallableReal callable_real;
        CallableComplex callable_complex;
    };

    template<typename CallableReal, typename CallableComplex>
    UnaryRealComplexFunction<CallableReal, CallableComplex>::UnaryRealComplexFunction(CallableReal callable_real, CallableComplex callable_complex) :
    callable_real(callable_real),
    callable_complex(callable_complex) {
    }

    template<typename CallableReal, typename CallableComplex>
    CompileResult UnaryRealComplexFunction<CallableReal, CallableComplex>::get_compile_result(CompileResult arg_compile_result) const {
        const auto & arg_compile_result_deref = arg_compile_result.dereference();
        if (!arg_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (const auto & result = _unary_real_function(callable_real, arg_compile_result))
            return *result;
        if (const auto & result = _unary_complex_function(callable_complex, arg_compile_result))
            return *result;
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

    // -------------------------------------------------------------------------

    template<typename CallableReal, typename CallableComplex>
    class BinaryRealComplexFunction : public BinaryFunction {
    public:
        BinaryRealComplexFunction(CallableReal callable_real, CallableComplex callable_complex);
        CompileResult get_compile_result(CompileResult first_arg, CompileResult second_arg) const override;
    private:
        CallableReal callable_real;
        CallableComplex callable_complex;
    };

    template<typename CallableReal, typename CallableComplex>
    BinaryRealComplexFunction<CallableReal, CallableComplex>::BinaryRealComplexFunction(CallableReal callable_real, CallableComplex callable_complex) :
    callable_real(callable_real),
    callable_complex(callable_complex) {
    }

    template<typename CallableReal, typename CallableComplex>
    CompileResult BinaryRealComplexFunction<CallableReal, CallableComplex>::get_compile_result(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        const auto & first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const auto & second_arg_compile_result_deref = second_arg_compile_result.dereference();
        if (!first_arg_compile_result_deref.is_either_value_or_type() || !second_arg_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (const auto & result = _binary_real_function(callable_real, first_arg_compile_result, second_arg_compile_result))
            return *result;
        if (const auto & result = _binary_complex_function(callable_complex, first_arg_compile_result, second_arg_compile_result))
            return *result;
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

}

#endif
