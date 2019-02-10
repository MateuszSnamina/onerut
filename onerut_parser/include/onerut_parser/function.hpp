#ifndef ONERUT_PARSER_FUNCTION
#define ONERUT_PARSER_FUNCTION

#include<vector>

#include<onerut_parser/compile_result.hpp>
#include<onerut_parser/compile_result_utility.hpp>
#include<onerut_scalar/function_real.hpp> // TODO move template classes to another header. Then remove this header
#include<onerut_scalar/function_complex.hpp> // TODO move template classes to another header. Then remove this header

namespace onerut_parser {

    class AbstractFunction {
    public:
        virtual CompileResult get_compile_result(std::vector<CompileResult> argv) const = 0;
        virtual ~AbstractFunction() = default;
    };


    // ---------------------------------------------------------------------------

    class UnaryFunction : public AbstractFunction {
    public:
        CompileResult get_compile_result(std::vector<CompileResult> argv) const final;
        virtual CompileResult get_compile_result(CompileResult arg) const = 0;
    };

    class BinaryFunction : public AbstractFunction {
    public:
        CompileResult get_compile_result(std::vector<CompileResult> argv) const final;
        virtual CompileResult get_compile_result(CompileResult first_arg, CompileResult second_arg) const = 0;
    };

    // ---------------------------------------------------------------------------        

    template<typename Callable>
    class UnaryRealFunction : public UnaryFunction {
    public:
        UnaryRealFunction(Callable callable);
        UnaryRealFunction() = default; // TODO REMOVE?
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
        if (!utility::is_real_or_integer(arg_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto & arg_real = utility::to_real(arg_compile_result_deref);
        return CompileResult::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::UnaryRealFunction < Callable >> (callable, arg_real));
    }

    // -------------------------------------------------------------------------

    template<typename Callable>
    class BinaryRealFunction : public BinaryFunction {
    public:
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
        if (!utility::is_real_or_integer(first_arg_compile_result_deref) || !utility::is_real_or_integer(second_arg_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto & first_arg_real = utility::to_real(first_arg_compile_result_deref);
        const auto & second_arg_real = utility::to_real(second_arg_compile_result_deref);
        return CompileResult::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::BinaryRealFunction < Callable >> (callable, first_arg_real, second_arg_real));
    }

    // ---------------------------------------------------------------------------        

    template<typename Callable>
    class UnaryComplexFunction : public UnaryFunction {
    public:
        UnaryComplexFunction(Callable callable);
        UnaryComplexFunction() = default; // TODO REMOVE?
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
        if (!utility::is_real_or_integer_or_complex(arg_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto & arg_complex = utility::to_complex(arg_compile_result_deref);
        return CompileResult::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::UnaryComplexFunction < Callable >> (callable, arg_complex));
    }

    // -------------------------------------------------------------------------

    template<typename Callable>
    class BinaryComplexFunction : public BinaryFunction {
    public:
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
        if (!utility::is_real_or_integer_or_complex(first_arg_compile_result_deref) ||
                !utility::is_real_or_integer_or_complex(second_arg_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto & first_arg_complex = utility::to_complex(first_arg_compile_result_deref);
        const auto & second_arg_complex = utility::to_complex(second_arg_compile_result_deref);
        return CompileResult::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::BinaryComplexFunction < Callable >> (callable, first_arg_complex, second_arg_complex));
    }

    // -------------------------------------------------------------------------

    template<typename CallableReal, typename CallableComplex>
    class UnaryRealComplexFunction : public UnaryFunction {
    public:
        UnaryRealComplexFunction(CallableReal callable_real, CallableComplex callable_complex);
        UnaryRealComplexFunction() = default; // TODO REMOVE?
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
        if (utility::is_real_or_integer(arg_compile_result_deref)) {
            const auto & arg_real = utility::to_real(arg_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::UnaryRealFunction < CallableReal >> (callable_real, arg_real));
        }
        if (utility::is_real_or_integer_or_complex(arg_compile_result_deref)) {
            const auto & arg_complex = utility::to_complex(arg_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::UnaryComplexFunction < CallableComplex >> (callable_complex, arg_complex));
        }
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
        if (utility::is_real_or_integer(first_arg_compile_result_deref) &&
                utility::is_real_or_integer(second_arg_compile_result_deref)) {
            const auto & first_arg_real = utility::to_real(first_arg_compile_result_deref);
            const auto & second_arg_real = utility::to_real(second_arg_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Real>(std::make_shared<onerut_scalar::BinaryRealFunction < CallableReal >> (callable_real, first_arg_real, second_arg_real));
        }
        if (utility::is_real_or_integer_or_complex(first_arg_compile_result_deref) &&
                utility::is_real_or_integer_or_complex(second_arg_compile_result_deref)) {
            const auto & first_arg_complex = utility::to_complex(first_arg_compile_result_deref);
            const auto & second_arg_complex = utility::to_complex(second_arg_compile_result_deref);
            return CompileResult::from_value<onerut_scalar::Complex>(std::make_shared<onerut_scalar::BinaryComplexFunction < CallableComplex >> (callable_complex, first_arg_complex, second_arg_complex));
        }
        return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
    }

}

#endif
