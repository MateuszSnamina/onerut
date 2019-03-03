#include<iostream>//debug TODO delete
#include<boost/cast.hpp>

#include<onerut_parser/asset_utility.hpp>
#include<onerut_parser/function_factory_normal_operators.hpp>
#include<onerut_parser/request_imperative.hpp>
#include<onerut_parser/asset_ref_container.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/operator_simple.hpp>
#include<onerut_normal_operator/operator_zero.hpp>
#include<onerut_normal_operator/operator_oscillator.hpp>
#include<onerut_normal_operator/operator_spin.hpp>
#include<onerut_normal_operator/operator_kron.hpp>
#include<onerut_normal_operator/diagonalizator.hpp>

namespace onerut_parser {

    Asset CreateNormalOperatorCustomDomainFunctionFactory::make_function_otherwise_make_error(const std::vector<Asset>& argv) const {
        const auto argc = argv.size();
        // ---------------------------------------------------------------------        
        for (unsigned index = 0; index < argc; ++index)
            if (!utility::is_unset_ref(argv[index]))
                return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        // Take out state names:
        std::vector<std::string> state_names;
        state_names.reserve(argc);
        for (unsigned index = 0; index < argc; ++index)
            state_names.push_back(utility::name_of_unset_ref(argv[index]));
        // Make domain object:
        auto domain = std::make_shared<onerut_normal_operator::CustomDomain>(state_names);
        auto domain_asset = Asset::from_value<onerut_normal_operator::CustomDomain>(domain);
        // Make state-index objects:
        for (unsigned index = 0; index < argc; ++index) {
            const std::string name = domain->state_name(index);
            const auto state_asset_deref = AssetDeref::from_value<onerut_normal_operator::StateIndex>(domain->crate_state(index));
            const auto state_ref = std::make_shared<AssetConstRef>(name, state_asset_deref);
            if (!AssetRefContainer::global_instance().put(state_ref)) {
                return Asset::from_compile_error(std::make_shared<IllegalSecondAssignError>());
            }
        }
        // Return domain compile result.
        return domain_asset;
    }

    Asset
    CreateNormalOperatorDomainStateIndexFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 2> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        // ---------------------------------------------------------------------        
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------        
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        if (!utility::is_normal_operator_domain(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_integer(arg1_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        const auto domain = utility::to_normal_operator_domain(arg0_asset_deref);
        const auto index = utility::to_integer(arg1_asset_deref);
        const auto index_buildin = boost::numeric_cast<unsigned>(index->value_integer());
        // ---------------------------------------------------------------------        
        using AssetT = onerut_normal_operator::StateIndex;
        return Asset::from_value<AssetT>(domain->crate_state(index_buildin));
    }

    Asset
    NormalOperatorZeroFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_normal_operator_domain(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_normal_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::ZeroOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(domain));
    }

    Asset
    NormalOperatorDiagFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 2> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        // ---------------------------------------------------------------------        
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------        
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        if (!utility::is_real_or_integer(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_normal_operator_state_index(arg1_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        const auto value = utility::to_real(arg0_asset_deref);
        const auto site = utility::to_normal_operator_state_index(arg1_asset_deref);
        // ---------------------------------------------------------------------        
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::DiagOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(value, site));
    }

    Asset
    NormalOperatorHopFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 3> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        const auto & arg2_asset_deref = args_asset[2].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (arg2_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!arg2_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_real_or_integer(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_normal_operator_state_index(arg1_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_normal_operator_state_index(arg2_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto value = utility::to_real(arg0_asset_deref);
        const auto site1 = utility::to_normal_operator_state_index(arg1_asset_deref);
        const auto site2 = utility::to_normal_operator_state_index(arg2_asset_deref);
        // ---------------------------------------------------------------------        
        if (!onerut_normal_operator::are_the_same_domains(*site1->domain, *site2->domain))
            return Asset::from_compile_error(std::make_shared<CompileError>("Incompatible state domains."));
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::HopOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(value, site1, site2)
                );
    }

    Asset
    NormalOperatorEyeFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_normal_operator_domain(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_normal_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::EyeOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(domain));
    }

    // *************************************************************************

    Asset
    CreateOscillatorDomainFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_integer(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto dimension = utility::to_integer(arg0_asset_deref);
        const auto dimension_buildin = boost::numeric_cast<unsigned>(dimension->value_integer());
        // ---------------------------------------------------------------------        
        return Asset::from_value<onerut_normal_operator::OscillatorDomain>(
                std::make_shared<onerut_normal_operator::OscillatorDomain>(dimension_buildin)
                );
    }

    Asset
    CreateCreationOperatorFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_oscillator_operator_domain(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_oscillator_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------        
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::CreationOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(domain)
                );
    }

    Asset
    CreateAnihilationOperatorFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_oscillator_operator_domain(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_oscillator_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------        
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::AnihilationOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(domain)
                );
    }

    // *************************************************************************

    Asset
    CreateSpinDomainFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_integer(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto dimension = utility::to_integer(arg0_asset_deref);
        const auto dimension_buildin = boost::numeric_cast<unsigned>(dimension->value_integer());
        // ---------------------------------------------------------------------        
        return Asset::from_value<onerut_normal_operator::SpinDomain>(
                std::make_shared<onerut_normal_operator::SpinDomain>(dimension_buildin)
                );
    }

    Asset
    CreateSpinZetOperatorFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_spin_operator_domain(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_spin_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------        
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::SpinZetOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(domain)
                );
    }

    Asset
    CreateSpinPlusOperatorFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_spin_operator_domain(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_spin_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------        
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::SpinPlusOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(domain)
                );
    }

    Asset
    CreateSpinMinusOperatorFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        if (!utility::is_spin_operator_domain(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------
        const auto domain = utility::to_spin_operator_domain(arg0_asset_deref);
        // ---------------------------------------------------------------------        
        using AbstractOperatorT = onerut_normal_operator::AbstractOperator;
        using OperatorT = onerut_normal_operator::SpinMinusOperator;
        return Asset::from_value<AbstractOperatorT>(
                std::make_shared<OperatorT>(domain)
                );
    }

    // *************************************************************************

    Asset CreateKronDomainFunctionFactory::make_function_otherwise_make_error(const std::vector<Asset>& argv) const {
        const auto & argv_asset_deref = utility::many_deref(argv);
        // --------------------------------------------------------------------- 
        if (utility::any_of_is_compile_error(argv_asset_deref))
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // --------------------------------------------------------------------- 
        if (!utility::all_of_is_either_value_or_type(argv_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // --------------------------------------------------------------------- 
        if (!std::all_of(cbegin(argv_asset_deref), cend(argv_asset_deref), utility::is_normal_operator_domain)) {
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        }
        // --------------------------------------------------------------------- 
        const auto & argv_domains = utility::many_to_normal_operator_domain(argv_asset_deref);
        using DomainT = onerut_normal_operator::KronDomain;
        return Asset::from_value<DomainT>(
                std::make_shared<DomainT>(argv_domains)
                );
    }

    Asset CreateNormalOperatorKronPlaceholdersFunctionFactory::make_function_otherwise_make_error(const std::vector<Asset>& argv) const {
        const auto argc = argv.size();
        const auto & argv_asset_deref = utility::many_deref(argv);
        // --------------------------------------------------------------------- 
        if (argc == 0)
            return Asset::from_compile_error(std::make_shared<WrongNumberOfArgumentsError>());
        // --------------------------------------------------------------------- 
        const auto & arg0_asset_deref = argv_asset_deref[0];
        // --------------------------------------------------------------------- 
        if (utility::any_of_is_compile_error(argv_asset_deref))
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // --------------------------------------------------------------------- 
        if (!utility::is_kron_operator_domain(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!std::all_of(cbegin(argv) + 1, cend(argv), utility::is_unset_ref))//TODO zrobic podobnie w create custom domain.(bez+1 przy begin)
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // --------------------------------------------------------------------- 
        const auto kron_domain = utility::to_kron_operator_domain(arg0_asset_deref);
        // --------------------------------------------------------------------- 
        if (argc != 1 + kron_domain->domains.size())
            return Asset::from_compile_error(std::make_shared<WrongNumberOfArgumentsError>());
        // --------------------------------------------------------------------- 
        // Take out placeholder names:
        std::vector<std::string> reference_names; //TODO zrobic podobnie w create custom domain.(bez+1 przy begin)
        reference_names.reserve(argc - 1);
        std::transform(
                cbegin(argv) + 1, cend(argv),
                std::back_inserter(reference_names),
                [](const Asset & asset) {
                    return utility::name_of_unset_ref(asset);
                }
        );
        // Make placeholder objects:
        for (unsigned place = 0; place < argc - 1; ++place) {
            const auto placeholder_asset_deref = AssetDeref::from_value<onerut_normal_operator::KronPlaceholder>(kron_domain->crate_placeholder(place));
            const auto placeholder_ref = std::make_shared<AssetConstRef>(reference_names[place], placeholder_asset_deref);
            if (!AssetRefContainer::global_instance().put(placeholder_ref)) {
                return Asset::from_compile_error(std::make_shared<IllegalSecondAssignError>());
            }
        }
        // Return kron_domain compile result.
        return argv[0];
    }

    Asset CreateNormalOperatorAtOperatorFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 2> args_asset) const {
        assert(0);//TODO implement
    }

    // *************************************************************************

    Asset NormalOperatorEigsFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        // ---------------------------------------------------------------------        
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------        
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        if (!utility::is_normal_operator(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        const auto normal_operator = utility::to_normal_operator(arg0_asset_deref);
        // ---------------------------------------------------------------------        

        return Asset::from_value<onerut_normal_operator::Eigs>(
                std::make_shared<onerut_normal_operator::Eigs>(normal_operator)
                );
    }

    Asset NormalOperatorMeanFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 3> args_asset) const {
        const auto & arg0_asset_deref = args_asset[0].deref();
        const auto & arg1_asset_deref = args_asset[1].deref();
        const auto & arg2_asset_deref = args_asset[2].deref();
        // ---------------------------------------------------------------------        
        if (arg0_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (arg1_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        if (arg2_asset_deref.is_compile_error())
            return Asset::from_compile_error(std::make_shared<CompileArgumentsError>());
        // ---------------------------------------------------------------------        
        if (!arg0_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!arg1_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!arg2_asset_deref.is_either_value_or_type())
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        if (!utility::is_normal_operator_eigs(arg0_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_normal_operator(arg1_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        if (!utility::is_integer(arg2_asset_deref))
            return Asset::from_compile_error(std::make_shared<ArgumentMismatchError>());
        // ---------------------------------------------------------------------        
        const auto normal_operator_eigs = utility::to_normal_operator_eigs(arg0_asset_deref);
        const auto normal_operator = utility::to_normal_operator(arg1_asset_deref);
        const auto state = utility::to_integer(arg2_asset_deref);
        // ---------------------------------------------------------------------                

        return Asset::from_value<onerut_normal_operator::Mean>(
                std::make_shared<onerut_normal_operator::Mean>(normal_operator_eigs, normal_operator, state)
                );
    }

    Asset NormalOperatorThermalMeanFunctionFactory::make_function_otherwise_make_error(std::array<Asset, 4> args_asset) const {
        assert(0); //TODO implement
    }



}
