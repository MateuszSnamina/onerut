#include<onerut_parser/compile_result_utility.hpp>
#include<onerut_parser/function_factory_normal_operators.hpp>

#include<onerut_operator/operator.hpp>


namespace onerut_parser {

    CompileResult
    NormalOperatorZerosFunctionFactory::make_function_otherwise_make_error(std::array<CompileResult, 0> args_compile_result) const {
        using AbstractOperatorT = onerut_operator::AbstractOperator<unsigned>;
        using OperatorT = onerut_operator::ZeroOperator<unsigned>;
        return CompileResult::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>());
    }

    CompileResult
    NormalOperatorDiagFunctionFactory::make_function_otherwise_make_error(std::array<CompileResult, 2> args_compile_result) const {
        const auto & arg0_compile_result_deref = args_compile_result[0].dereference();
        const auto & arg1_compile_result_deref = args_compile_result[1].dereference();
        if (!arg0_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!arg1_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::is_real_or_integer(arg0_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_integer(arg1_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto value = utility::to_real(arg0_compile_result_deref);
        const auto site = utility::to_integer(arg1_compile_result_deref);
        using AbstractOperatorT = onerut_operator::AbstractOperator<unsigned>;
        using OperatorT = onerut_operator::DiagOperator<unsigned>;
        return CompileResult::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(value->value_real(), static_cast<unsigned> (site->value_integer())));
    }

    CompileResult
    NormalOperatorHopFunctionFactory::make_function_otherwise_make_error(std::array<CompileResult, 3> args_compile_result) const {
        const auto & arg0_compile_result_deref = args_compile_result[0].dereference();
        const auto & arg1_compile_result_deref = args_compile_result[1].dereference();
        const auto & arg2_compile_result_deref = args_compile_result[2].dereference();
        if (!arg0_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!arg1_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!arg2_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::is_real_or_integer(arg0_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_integer(arg1_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_integer(arg2_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto value = utility::to_real(arg0_compile_result_deref);
        const auto site1 = utility::to_integer(arg1_compile_result_deref);
        const auto site2 = utility::to_integer(arg2_compile_result_deref);
        using AbstractOperatorT = onerut_operator::AbstractOperator<unsigned>;
        using OperatorT = onerut_operator::HopOperator<unsigned>;
        return CompileResult::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(
                value->value_real(),
                static_cast<unsigned> (site1->value_integer()),
                static_cast<unsigned> (site2->value_integer())
                ));
    }

    CompileResult NormalOperatorPrintFactory::make_function_otherwise_make_error(std::array<CompileResult, 2> args_compile_result) const {
        const auto & arg0_compile_result_deref = args_compile_result[0].dereference();
        const auto & arg1_compile_result_deref = args_compile_result[1].dereference();
        if (!arg0_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!arg1_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::is_normal_operator(arg0_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_integer(arg1_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto normal_operator = utility::to_normal_operator(arg0_compile_result_deref);
        const auto dim = utility::to_integer(arg1_compile_result_deref);
        const arma::mat M = onerut_operator::to_mat(*normal_operator, dim->value_integer());
        std::cout << "Normal operator:" << std::endl;
        std::cout << M << std::endl;
        return args_compile_result[0];
    }

}
