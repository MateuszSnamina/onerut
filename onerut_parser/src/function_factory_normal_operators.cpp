#include<onerut_parser/compile_result_utility.hpp>
#include<onerut_parser/function_factory_normal_operators.hpp>
#include<onerut_parser/identifier_global.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_zero.hpp>
#include<onerut_normal_operator/to_mat.hpp>

#include<iostream>//debug TODO delete
namespace onerut_parser {

    CompileResult
    NormalOperatorZeroFunctionFactory::make_function_otherwise_make_error(std::array<CompileResult, 1> args_compile_result) const {
        const auto & arg0_compile_result_deref = args_compile_result[0].dereference();
        if (!arg0_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::is_normal_operator_domain(arg0_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto domain = utility::to_normal_operator_domain(arg0_compile_result_deref);       
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::ZeroOperator;
        return CompileResult::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(domain));
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
        if (!utility::is_normal_operator_state_index(arg1_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto value = utility::to_real(arg0_compile_result_deref);
        const auto site = utility::to_normal_operator_state_index(arg1_compile_result_deref);
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::DiagOperator;
        return CompileResult::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(value, site));
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
        if (!utility::is_normal_operator_state_index(arg1_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_normal_operator_state_index(arg2_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto value = utility::to_real(arg0_compile_result_deref);
        const auto site1 = utility::to_normal_operator_state_index(arg1_compile_result_deref);
        const auto site2 = utility::to_normal_operator_state_index(arg2_compile_result_deref);
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::HopOperator;
        return CompileResult::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(value, site1, site2)
                );
    }

    CompileResult CreateNormalDomainFunctionFactory::make_function_otherwise_make_error(const std::vector<CompileResult>& argv) const {
        const auto argc = argv.size();
        for (unsigned index = 0; index < argc; ++index)
            if (!utility::is_identifier_not_found_error(argv[index].dereference()))
                return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        // Take out state names:
        std::vector<std::string> state_names;
        state_names.reserve(argc);
        for (unsigned index = 0; index < argc; ++index)
            state_names.push_back(utility::name_of_identifier_not_found(argv[index].dereference()));
        // Make domain object:
        auto domain = std::make_shared<onerut_normal_operator::Domain>(state_names);
        auto domain_compile_result = CompileResult::from_value<onerut_normal_operator::Domain>(domain);
        // Make state-index objects:
        for (unsigned index = 0; index < argc; ++index) {
            const std::string name = domain->state_names[index];
            const auto state_compile_result_deref = CompileResultDeref::from_value<onerut_normal_operator::StateIndex>(domain->crate_state(index));
            const auto state_ref = std::make_shared<CompileResultConstRef>(name, state_compile_result_deref);
            if (!GlobalIdentifiers::instance().put(name, state_ref)) {
                return CompileResult::from_compile_error(std::make_shared<IllegalSecondAssignError>());
            }
        }
        // Return domain compile result.
        return domain_compile_result;
    }

    CompileResult NormalOperatorPrintFunctionFactory::make_function_otherwise_make_error(std::array<CompileResult, 1> args_compile_result) const {
        const auto & arg0_compile_result_deref = args_compile_result[0].dereference();
        if (!arg0_compile_result_deref.is_either_value_or_type())
            return CompileResult::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (!utility::is_normal_operator(arg0_compile_result_deref))
            return CompileResult::from_compile_error(std::make_shared<ArgumentMismatchError>());
        const auto normal_operator = utility::to_normal_operator(arg0_compile_result_deref);
        const arma::mat M = onerut_normal_operator::to_mat(*normal_operator);
        std::cout << "Normal operator:" << std::endl;
        std::cout << M << std::endl;
        return args_compile_result[0];
    }

}
