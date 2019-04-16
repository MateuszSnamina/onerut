#include<iostream>//debug TODO delete
#include<boost/cast.hpp>

#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_zero.hpp>
#include<onerut_normal_operator/operator_oscillator.hpp>
#include<onerut_normal_operator/operator_spin.hpp>
#include<onerut_normal_operator/operator_kron.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>
#include<onerut_parser_exec/asset_ref_container.hpp>
#include<onerut_parser_exec/asset_utility.hpp>
#include<onerut_parser_rules/asset_utility_concrete.hpp>
#include<onerut_parser_rules/function_factory_normal_operators.hpp>

namespace onerut_parser_rules {

    onerut_parser_exec::Asset CreateNormalOperatorCustomDomainFunctionFactory::make_function_otherwise_make_error(const std::vector<onerut_parser_exec::Asset>& argv) const {
        const auto argc = argv.size();
        // ---------------------------------------------------------------------
        for (uint32_t index = 0; index < argc; ++index)
            if (!onerut_parser_exec::utility::is_unset_ref(argv[index]))
                return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        // Take out state names:
        std::vector<std::string> state_names;
        state_names.reserve(argc);
        for (uint32_t index = 0; index < argc; ++index)
            state_names.push_back(onerut_parser_exec::utility::name_of_unset_ref(argv[index]));
        // Make domain object:
        auto domain = std::make_shared<onerut_normal_operator::CustomDomain>(state_names);
        auto domain_asset = onerut_parser_exec::Asset::from_value<onerut_normal_operator::CustomDomain>(domain);
        // Make state-index objects:
        for (uint32_t index = 0; index < argc; ++index) {
            const std::string name = domain->state_name(index);
            const auto state_asset_deref = onerut_parser_exec::AssetDeref::from_value<onerut_normal_operator::StateIndex>(domain->crate_state(index));
            const auto state_ref = std::make_shared<onerut_parser_exec::AssetConstRef>(name, state_asset_deref);
            if (!onerut_parser_exec::AssetRefContainer::global_instance().put(state_ref)) {
                return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::IllegalSecondAssignError>());
            }
        }
        // Return domain compile result.
        return domain_asset;
    }

    onerut_parser_exec::Asset
    CreateNormalOperatorDomainStateIndexFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_normal_operator_domain(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_integer(arg1_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_normal_operator_domain(arg0_asset_deref);
        const auto index = utility::to_integer(arg1_asset_deref);
        const auto index_buildin = index->value_integer();
        // ---------------------------------------------------------------------
        if (index_buildin < 0)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The state index number must not be a negative integer."));
        if (index_buildin >= domain->size())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The state index number must not exceed (or be equal to) the domain size."));
        const auto index_buildin_casted = boost::numeric_cast<uint32_t>(index_buildin);
        // ---------------------------------------------------------------------
        using AssetT = onerut_normal_operator::StateIndex;
        return onerut_parser_exec::Asset::from_value<AssetT>(domain->crate_state(index_buildin_casted));
    }

    onerut_parser_exec::Asset
    NormalOperatorZeroFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_normal_operator_domain(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_normal_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------
        using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
        using OperatorT = onerut_normal_operator::ZeroOperator;
        return onerut_parser_exec::Asset::from_value<AbstractRealOperatorT>(
                std::make_shared<OperatorT>(domain));
    }

    onerut_parser_exec::Asset
    NormalOperatorDiagFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_real_or_integer(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_normal_operator_state_index(arg1_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto value = utility::to_real(arg0_asset_deref);
        const auto site = utility::to_normal_operator_state_index(arg1_asset_deref);
        // ---------------------------------------------------------------------
        using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
        using OperatorT = onerut_normal_operator::DiagOperator;
        return onerut_parser_exec::Asset::from_value<AbstractRealOperatorT>(
                std::make_shared<OperatorT>(value, site));
    }

    onerut_parser_exec::Asset
    NormalOperatorHopFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 3> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        const auto & arg2_asset_deref = args_asset[2].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg2_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg2_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_real_or_integer(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_normal_operator_state_index(arg1_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_normal_operator_state_index(arg2_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto value = utility::to_real(arg0_asset_deref);
        const auto site1 = utility::to_normal_operator_state_index(arg1_asset_deref);
        const auto site2 = utility::to_normal_operator_state_index(arg2_asset_deref);
        // ---------------------------------------------------------------------
        if (!onerut_normal_operator::are_the_same_domains(*site1->domain, *site2->domain))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("Incompatible state domains."));
        // ---------------------------------------------------------------------
        if (site1->index == site2->index)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("Hopping must take place between two different states."));
        // ---------------------------------------------------------------------
        using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
        using OperatorT = onerut_normal_operator::HopOperator;
        return onerut_parser_exec::Asset::from_value<AbstractRealOperatorT>(
                std::make_shared<OperatorT>(value, site1, site2)
                );
    }

    onerut_parser_exec::Asset
    NormalOperatorEyeFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_normal_operator_domain(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_normal_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------
        using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
        using OperatorT = onerut_normal_operator::EyeOperator;
        return onerut_parser_exec::Asset::from_value<AbstractRealOperatorT>(
                std::make_shared<OperatorT>(domain));
    }

    // *************************************************************************

    onerut_parser_exec::Asset
    CreateOscillatorDomainFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_integer(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto dimension = utility::to_integer(arg0_asset_deref);
        // ---------------------------------------------------------------------
        const auto dimension_buildin = dimension->value_integer();
        if (dimension_buildin < 0)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The requested space dimension must not be a negative integer."));
        if (dimension_buildin == 0)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The requested space dimension must not be equal to zero."));
        const auto dimension_buildin_casted = boost::numeric_cast<uint32_t>(dimension_buildin);
        // ---------------------------------------------------------------------
        return onerut_parser_exec::Asset::from_value<onerut_normal_operator::OscillatorDomain>(
                std::make_shared<onerut_normal_operator::OscillatorDomain>(dimension_buildin_casted)
                );
    }

    onerut_parser_exec::Asset
    CreateCreationOperatorFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_oscillator_operator_domain(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_oscillator_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------
        using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
        using OperatorT = onerut_normal_operator::CreationOperator;
        return onerut_parser_exec::Asset::from_value<AbstractRealOperatorT>(
                std::make_shared<OperatorT>(domain)
                );
    }

    onerut_parser_exec::Asset
    CreateAnihilationOperatorFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_oscillator_operator_domain(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_oscillator_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------
        using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
        using OperatorT = onerut_normal_operator::AnihilationOperator;
        return onerut_parser_exec::Asset::from_value<AbstractRealOperatorT>(
                std::make_shared<OperatorT>(domain)
                );
    }

    // *************************************************************************

    onerut_parser_exec::Asset
    CreateSpinDomainFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_integer(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto dimension = utility::to_integer(arg0_asset_deref);
        // ---------------------------------------------------------------------
        const auto dimension_buildin = dimension->value_integer();
        if (dimension_buildin < 0)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The requested space dimension must not be a negative integer."));
        if (dimension_buildin == 0)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The requested space dimension must not be equal to zero."));
        const auto dimension_buildin_casted = boost::numeric_cast<uint32_t>(dimension_buildin);
        // ---------------------------------------------------------------------
        return onerut_parser_exec::Asset::from_value<onerut_normal_operator::SpinDomain>(
                std::make_shared<onerut_normal_operator::SpinDomain>(dimension_buildin_casted)
                );
    }

    onerut_parser_exec::Asset
    CreateSpinZetOperatorFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_spin_operator_domain(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_spin_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------
        using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
        using OperatorT = onerut_normal_operator::SpinZetOperator;
        return onerut_parser_exec::Asset::from_value<AbstractRealOperatorT>(
                std::make_shared<OperatorT>(domain)
                );
    }

    onerut_parser_exec::Asset
    CreateSpinPlusOperatorFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_spin_operator_domain(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_spin_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------
        using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
        using OperatorT = onerut_normal_operator::SpinPlusOperator;
        return onerut_parser_exec::Asset::from_value<AbstractRealOperatorT>(
                std::make_shared<OperatorT>(domain)
                );
    }

    onerut_parser_exec::Asset
    CreateSpinMinusOperatorFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_spin_operator_domain(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_spin_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------
        using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
        using OperatorT = onerut_normal_operator::SpinMinusOperator;
        return onerut_parser_exec::Asset::from_value<AbstractRealOperatorT>(
                std::make_shared<OperatorT>(domain)
                );
    }

    // *************************************************************************

    onerut_parser_exec::Asset CreateKronDomainFunctionFactory::make_function_otherwise_make_error(const std::vector<onerut_parser_exec::Asset>& argv) const {
        const auto & argv_asset_deref = onerut_parser_exec::utility::many_deref(argv);
        // ---------------------------------------------------------------------
        if (onerut_parser_exec::utility::any_of_is_compile_error(argv_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!onerut_parser_exec::utility::all_of_is_either_value_or_type(argv_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!std::all_of(cbegin(argv_asset_deref), cend(argv_asset_deref), utility::is_normal_operator_domain)) {
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        }
        // ---------------------------------------------------------------------
        const auto & argv_domains = utility::many_to_normal_operator_domain(argv_asset_deref);
        using DomainT = onerut_normal_operator::KronDomain;
        return onerut_parser_exec::Asset::from_value<DomainT>(
                std::make_shared<DomainT>(argv_domains)
                );
    }

    onerut_parser_exec::Asset CreateNormalOperatorKronPlaceholdersFunctionFactory::make_function_otherwise_make_error(const std::vector<onerut_parser_exec::Asset>& argv) const {
        const auto argc = argv.size();
        const auto & argv_asset_deref = onerut_parser_exec::utility::many_deref(argv);
        // ---------------------------------------------------------------------
        if (argc == 0)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::WrongNumberOfArgumentsError>());
        // ---------------------------------------------------------------------
        const auto arg0_asset_deref = argv_asset_deref[0];
        // ---------------------------------------------------------------------
        if (onerut_parser_exec::utility::any_of_is_compile_error(argv_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_kron_operator_domain(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!std::all_of(cbegin(argv) + 1, cend(argv), onerut_parser_exec::utility::is_unset_ref)) // TODO zrobic podobnie w create custom domain.(bez+1 przy begin)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto kron_domain = utility::to_kron_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------
        if (argc != 1 + kron_domain->subdomains.size())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::WrongNumberOfArgumentsError>());
        // ---------------------------------------------------------------------
        // Take out placeholder names:
        std::vector<std::string> reference_names; // TODO zrobic podobnie w create custom domain.(bez+1 przy begin)
        reference_names.reserve(argc - 1);
        std::transform(
                cbegin(argv) + 1, cend(argv),
                std::back_inserter(reference_names),
                [](const onerut_parser_exec::Asset & asset) {
                    return onerut_parser_exec::utility::name_of_unset_ref(asset);
                }
        );
        // Make placeholder objects:
        for (unsigned place = 0; place < argc - 1; ++place) {
            const auto placeholder_asset_deref = onerut_parser_exec::AssetDeref::from_value<onerut_normal_operator::KronPlaceholder>(kron_domain->crate_placeholder(place));
            const auto placeholder_ref = std::make_shared<onerut_parser_exec::AssetConstRef>(reference_names[place], placeholder_asset_deref);
            if (!onerut_parser_exec::AssetRefContainer::global_instance().put(placeholder_ref)) {
                return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::IllegalSecondAssignError>());
            }
        }
        // Return -- forward kron-domain:
        return argv[0];
    }

    onerut_parser_exec::Asset CreateNormalOperatorAtOperatorFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_normal_operator(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_kron_operator_domain_placeholder(arg1_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto normal_op = utility::to_normal_operator(arg0_asset_deref);
        const auto placeholder = utility::to_kron_operator_domain_placeholder(arg1_asset_deref);
        // ---------------------------------------------------------------------
        const auto domain_operator = normal_op->get_domain();
        const auto domain_placeholder = placeholder->fetch_subdomain();
        if (!onerut_normal_operator::are_the_same_domains(*domain_operator, *domain_placeholder))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("Incompatible state domains."));
        // ---------------------------------------------------------------------
        using AbstractRealOperatorT = onerut_normal_operator::AbstractRealOperator;
        using OperatorT = onerut_normal_operator::KronAtOperator;
        return onerut_parser_exec::Asset::from_value<AbstractRealOperatorT>(
                std::make_shared<OperatorT>(normal_op, placeholder));
    }

    // *************************************************************************

    onerut_parser_exec::Asset NormalOperatorEigDenseFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_normal_operator(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto normal_operator = utility::to_normal_operator(arg0_asset_deref);
        // ---------------------------------------------------------------------
        return onerut_parser_exec::Asset::from_value<onerut_normal_operator::Eig>(
                std::make_shared<onerut_normal_operator::EigDense>(normal_operator)
                );
    }

    onerut_parser_exec::Asset NormalOperatorEigSparseFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_normal_operator(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_integer(arg1_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto normal_operator = utility::to_normal_operator(arg0_asset_deref);
        const auto numer_of_states_to_calculate = utility::to_integer(arg1_asset_deref);
        // ---------------------------------------------------------------------
        const auto numer_of_states_to_calculate_buildin = numer_of_states_to_calculate->value_integer();
        if (numer_of_states_to_calculate_buildin < 0)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The number of requested states must not be a negative integer."));
        if (numer_of_states_to_calculate_buildin == 0)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The number of requested states must not be equal to zero."));
        if (numer_of_states_to_calculate_buildin >= normal_operator->get_domain()->size())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The number of requested states must not exceed (or be equal to) the operator domain size."));
        const auto numer_of_states_to_calculate_buildin_casted = boost::numeric_cast<uint32_t>(numer_of_states_to_calculate_buildin);
        // ---------------------------------------------------------------------
        return onerut_parser_exec::Asset::from_value<onerut_normal_operator::Eig>(
                std::make_shared<onerut_normal_operator::EigSparse>(normal_operator, numer_of_states_to_calculate_buildin_casted)
                );
        return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompilerNotImplementedError>());
    }

    onerut_parser_exec::Asset NormalOperatorMeanInEigenStateFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 3> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        const auto & arg2_asset_deref = args_asset[2].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg2_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg2_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_normal_operator(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_normal_operator_eig(arg1_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_integer(arg2_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto normal_operator = utility::to_normal_operator(arg0_asset_deref);
        const auto normal_operator_eig = utility::to_normal_operator_eig(arg1_asset_deref);
        const auto state = utility::to_integer(arg2_asset_deref);
        const auto state_buildin = state->value_integer();
        // ---------------------------------------------------------------------
        if (!onerut_normal_operator::are_the_same_domains(*normal_operator->get_domain(), *normal_operator_eig->hamiltonian->get_domain()))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The eigen states and the operator are defined in different domains."));
        if (state_buildin < 0)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The eigen state number must not be a negative integer."));
        if (state_buildin >= normal_operator->get_domain()->size())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The eigen state number must not exceed (or be equal to) the operator domain size."));
        if (const auto eig_sp = std::dynamic_pointer_cast<onerut_normal_operator::EigSparse>(normal_operator_eig))
            if (state_buildin >= eig_sp->numer_of_states_to_calculate)
                return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The eigen state number must not exceed (or be equal to) the requested number of states to calculate."));
        const auto state_buildin_casted = boost::numeric_cast<uint32_t>(state_buildin);
        // ---------------------------------------------------------------------
        return onerut_parser_exec::Asset::from_value<onerut_normal_operator::Mean>(
                std::make_shared<onerut_normal_operator::MeanInEigenState>(normal_operator, normal_operator_eig, state_buildin_casted)
                );
    }

    onerut_parser_exec::Asset NormalOperatorMeanThermalFunctionFactory::make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 3> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        const auto & arg2_asset_deref = args_asset[2].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        if (arg2_asset_deref.is_compile_error())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!arg2_asset_deref.is_either_value_or_type())
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_normal_operator(arg0_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_normal_operator_eig(arg1_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        if (!utility::is_real_or_integer(arg2_asset_deref))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto normal_operator = utility::to_normal_operator(arg0_asset_deref);
        const auto normal_operator_eig = utility::to_normal_operator_eig(arg1_asset_deref);
        const auto temperature = utility::to_real(arg2_asset_deref);
        const auto temperature_buildin = temperature->value_real();
        // ---------------------------------------------------------------------
        if (!onerut_normal_operator::are_the_same_domains(*normal_operator->get_domain(), *normal_operator_eig->hamiltonian->get_domain()))
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentDomainError>("The eigen states and the operator are defined in different domains."));
        // ---------------------------------------------------------------------
        return onerut_parser_exec::Asset::from_value<onerut_normal_operator::Mean>(
                std::make_shared<onerut_normal_operator::MeanThermal>(normal_operator, normal_operator_eig, temperature_buildin)
                );
    }

}
