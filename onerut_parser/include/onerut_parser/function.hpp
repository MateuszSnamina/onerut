#ifndef ONERUT_PARSER_FUNCTION
#define ONERUT_PARSER_FUNCTION

#include<vector>

#include<onerut_parser/compile_result.hpp>
#include<onerut_parser/compile_result_utility.hpp>
#include<onerut_scalar/scalar.hpp> // TODO move template classes to another header. Then remove this header

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
    class UnaryDoubleFunction : public UnaryFunction {
    public:
        UnaryDoubleFunction(Callable callable);
        UnaryDoubleFunction() = default;
        CompileResult get_compile_result(CompileResult arg) const override;
    private:
        Callable callable;
    };

    template<typename Callable>
    UnaryDoubleFunction<Callable>::UnaryDoubleFunction(Callable callable) :
    callable(callable) {
    }

    template<typename Callable>
    CompileResult UnaryDoubleFunction<Callable>::get_compile_result(CompileResult arg_compile_result) const {
        const auto & arg_compile_result_deref = arg_compile_result.dereference();
        if (!arg_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::is_real(arg_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto & arg_double = utility::to_double(arg_compile_result_deref);
        return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::UnaryDoubleFunction < Callable >> (callable, arg_double));
    }

    // -------------------------------------------------------------------------

    template<typename Callable>
    class BinaryDoubleFunction : public BinaryFunction {
    public:
        BinaryDoubleFunction(Callable callable);
        CompileResult get_compile_result(CompileResult first_arg, CompileResult second_arg) const override;
    private:
        Callable callable;
    };

    template<typename Callable>
    BinaryDoubleFunction<Callable>::BinaryDoubleFunction(Callable callable) :
    callable(callable) {
    }

    template<typename Callable>
    CompileResult BinaryDoubleFunction<Callable>::get_compile_result(CompileResult first_arg_compile_result, CompileResult second_arg_compile_result) const {
        const auto & first_arg_compile_result_deref = first_arg_compile_result.dereference();
        const auto & second_arg_compile_result_deref = second_arg_compile_result.dereference();
        if (!first_arg_compile_result_deref.is_either_value_or_type() || !second_arg_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::is_real(first_arg_compile_result_deref) || !utility::is_real(second_arg_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto & first_arg_double = utility::to_double(first_arg_compile_result_deref);
        const auto & second_arg_double = utility::to_double(second_arg_compile_result_deref);
        return CompileResult::from_value<onerut_scalar::Double>(std::make_shared<onerut_scalar::BinaryDoubleFunction < Callable >> (callable, first_arg_double, second_arg_double));
    }

}

#endif
