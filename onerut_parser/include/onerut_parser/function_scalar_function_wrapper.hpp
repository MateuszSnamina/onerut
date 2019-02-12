#ifndef ONERUT_PARSER_TEMPLATES
#define ONERUT_PARSER_TEMPLATES

#include<vector>

#include<onerut_parser/function_abstract.hpp>
#include<onerut_parser/compile_result_utility.hpp>
#include<onerut_scalar/function.hpp>

//#include<iostream> //Debug TODO remove

namespace onerut_parser {

    template<typename T>
    class ArgPreparator {
    };

    template<>
    struct ArgPreparator<onerut_scalar::ArgInteger> {
        bool do_match(const CompileResultDeref & arg) const;
        std::shared_ptr<onerut_scalar::Integer> extract(const CompileResultDeref & arg) const;
    };

    template<>
    struct ArgPreparator<onerut_scalar::ArgReal> {
        bool do_match(const CompileResultDeref & arg) const;
        std::shared_ptr<onerut_scalar::Real> extract(const CompileResultDeref & arg) const;
    };

    template<>
    struct ArgPreparator<onerut_scalar::ArgComplex> {
        bool do_match(const CompileResultDeref & arg) const;
        std::shared_ptr<onerut_scalar::Complex> extract(const CompileResultDeref & arg) const;
    };

    bool
    ArgPreparator<onerut_scalar::ArgInteger>::do_match(const CompileResultDeref & arg) const {
        return utility::is_integer(arg);
    }

    std::shared_ptr<onerut_scalar::Integer>
    ArgPreparator<onerut_scalar::ArgInteger>::extract(const CompileResultDeref & arg) const {
        return utility::to_integer(arg);
    }

    bool
    ArgPreparator<onerut_scalar::ArgReal>::do_match(const CompileResultDeref & arg) const {
        return utility::is_real_or_integer(arg);
    }

    std::shared_ptr<onerut_scalar::Real>
    ArgPreparator<onerut_scalar::ArgReal>::extract(const CompileResultDeref & arg) const {
        return utility::to_real(arg);
    }

    bool
    ArgPreparator<onerut_scalar::ArgComplex>::do_match(const CompileResultDeref & arg) const {
        return utility::is_real_or_integer_or_complex(arg);
    }

    std::shared_ptr<onerut_scalar::Complex>
    ArgPreparator<onerut_scalar::ArgComplex>::extract(const CompileResultDeref & arg) const {
        return utility::to_complex(arg);
    }

    // TODO insert into future function: static_assert(onerut_scalar::IsArg<Arg1>::value);

    // AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

    template<typename Callable >
    std::optional<CompileResult>
    _unary_real_function(Callable callable, CompileResult arg_compile_result) {
        using Arg = onerut_scalar::ArgReal;
        const auto & arg_compile_result_deref = arg_compile_result.dereference();
        assert(arg_compile_result_deref.is_either_value_or_type());
        if (ArgPreparator<Arg>().do_match(arg_compile_result_deref)) {
            const auto & arg_real = ArgPreparator<Arg>().extract(arg_compile_result_deref);
            using OnerutScalarFunctionType = typename onerut_scalar::DeduceFunction<Callable, Arg>::DeducedFunction;
            using ReturnOnerutBaseType = typename OnerutScalarFunctionType::ReturnTag::OnerutBaseType;
            return CompileResult::from_value<ReturnOnerutBaseType>(std::make_shared<OnerutScalarFunctionType>(callable, arg_real));
        }
        return std::nullopt;
    }

    template<typename Callable>
    std::optional<CompileResult>
    _binary_real_function(Callable callable, CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) {
        using Arg1 = onerut_scalar::ArgReal;
        using Arg2 = onerut_scalar::ArgReal;
        const auto & first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const auto & second_arg_compile_result_deref = second_arg_compile_result.dereference();
        assert(first_arg_compile_result_deref.is_either_value_or_type() &&
                second_arg_compile_result_deref.is_either_value_or_type());
        if (ArgPreparator<Arg1>().do_match(first_arg_compile_result_deref) &&
                ArgPreparator<Arg2>().do_match(second_arg_compile_result_deref)) {
            const auto & first_arg_real = ArgPreparator<Arg1>().extract(first_arg_compile_result_deref);
            const auto & second_arg_real = ArgPreparator<Arg2>().extract(second_arg_compile_result_deref);
            using OnerutScalarFunctionType = typename onerut_scalar::DeduceFunction<Callable, Arg1, Arg2>::DeducedFunction;
            using ReturnOnerutBaseType = typename OnerutScalarFunctionType::ReturnTag::OnerutBaseType;
            return CompileResult::from_value<ReturnOnerutBaseType>(std::make_shared<OnerutScalarFunctionType> (callable, first_arg_real, second_arg_real));
        }
        return std::nullopt;
    }

    template<typename Callable>
    std::optional<CompileResult>
    _unary_complex_function(Callable callable, CompileResult arg_compile_result) {
        using Arg = onerut_scalar::ArgComplex;
        const auto & arg_compile_result_deref = arg_compile_result.dereference();
        assert(arg_compile_result_deref.is_either_value_or_type());
        if (ArgPreparator<Arg>().do_match(arg_compile_result_deref)) {
            const auto & arg_complex = ArgPreparator<Arg>().extract(arg_compile_result_deref);
            using OnerutScalarFunctionType = typename onerut_scalar::DeduceFunction<Callable, Arg>::DeducedFunction;
            using ReturnOnerutBaseType = typename OnerutScalarFunctionType::ReturnTag::OnerutBaseType;
            return CompileResult::from_value<ReturnOnerutBaseType>(std::make_shared<OnerutScalarFunctionType> (callable, arg_complex));
        }
        return std::nullopt;
    }

    template<typename Callable>
    std::optional<CompileResult>
    _binary_complex_function(Callable callable, CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) {
        using Arg1 = onerut_scalar::ArgComplex;
        using Arg2 = onerut_scalar::ArgComplex;
        const auto & first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const auto & second_arg_compile_result_deref = second_arg_compile_result.dereference();
        assert(first_arg_compile_result_deref.is_either_value_or_type() &&
                second_arg_compile_result_deref.is_either_value_or_type());
        if (ArgPreparator<Arg1>().do_match(first_arg_compile_result_deref) &&
                ArgPreparator<Arg2>().do_match(second_arg_compile_result_deref)) {
            const auto & first_arg_complex = ArgPreparator<Arg1>().extract(first_arg_compile_result_deref);
            const auto & second_arg_complex = ArgPreparator<Arg2>().extract(second_arg_compile_result_deref);
            using OnerutScalarFunctionType = typename onerut_scalar::DeduceFunction<Callable, Arg1, Arg2>::DeducedFunction;
            using ReturnOnerutBaseType = typename OnerutScalarFunctionType::ReturnTag::OnerutBaseType;
            return CompileResult::from_value<ReturnOnerutBaseType>(std::make_shared<OnerutScalarFunctionType> (callable, first_arg_complex, second_arg_complex));
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

    template<typename Callable >
    UnaryRealFunction<Callable>::UnaryRealFunction(Callable callable) :
    callable(callable) {
    }

    template<typename Callable >
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

    template<typename Callable >
    BinaryRealFunction<Callable>::BinaryRealFunction(Callable callable) :
    callable(callable) {
    }

    template<typename Callable >
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

    template<typename Callable >
    UnaryComplexFunction<Callable>::UnaryComplexFunction(Callable callable) :
    callable(callable) {
    }

    template<typename Callable >
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

    template<typename Callable >
    BinaryComplexFunction<Callable>::BinaryComplexFunction(Callable callable) :
    callable(callable) {
    }

    template<typename Callable >
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

    template<typename CallableReal, typename CallableComplex >
    UnaryRealComplexFunction<CallableReal, CallableComplex>::UnaryRealComplexFunction(CallableReal callable_real, CallableComplex callable_complex) :
    callable_real(callable_real),
    callable_complex(callable_complex) {
    }

    template<typename CallableReal, typename CallableComplex >
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

    template<typename CallableReal, typename CallableComplex >
    BinaryRealComplexFunction<CallableReal, CallableComplex>::BinaryRealComplexFunction(CallableReal callable_real, CallableComplex callable_complex) :
    callable_real(callable_real),
    callable_complex(callable_complex) {
    }

    template<typename CallableReal, typename CallableComplex >
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
