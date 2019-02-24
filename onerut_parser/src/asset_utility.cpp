#include<algorithm>

#include<onerut_parser/asset_utility.hpp>

namespace onerut_parser::utility {

    // -------------------------------------------------------------------------
    // ------------------ COMPILE RESULTS --------------------------------------
    // -------------------------------------------------------------------------

    bool
    is_not_const_ref(const onerut_parser::Asset& asset) {
        if (const auto & reference = asset.reference_or_empty())
            if (std::dynamic_pointer_cast<const onerut_parser::AssetNotConstRef>(*reference))
                return true;
        return false;
    }

    bool
    is_const_ref(const onerut_parser::Asset& asset) {
        if (const auto & reference = asset.reference_or_empty())
            if (std::dynamic_pointer_cast<const onerut_parser::AssetConstRef>(*reference))
                return true;
        return false;
    }

    bool
    is_unset_ref(const onerut_parser::Asset& asset) {
        if (const auto& referencce = asset.reference_or_empty())
            if (std::dynamic_pointer_cast<const onerut_parser::AssetUnsetRef>(*referencce))
                return true;
        return false;
    }

    std::shared_ptr<onerut_parser::AssetNotConstRef>
    to_not_const_ref(const onerut_parser::Asset& asset) {
        assert(is_not_const_ref(asset));
        const auto & reference = asset.reference_or_empty();
        const auto & no_const_reference = std::dynamic_pointer_cast<onerut_parser::AssetNotConstRef>(*reference);
        assert(no_const_reference);
        return no_const_reference;
    }

    std::string
    name_of_unset_ref(const onerut_parser::Asset& asset) {
        const auto& referencce = asset.reference_or_empty();
        assert(referencce);
        const auto& unset_referencce = std::dynamic_pointer_cast<const onerut_parser::AssetUnsetRef>(*referencce);
        assert(unset_referencce);
        return unset_referencce->get_name();
    }

    // -------------------------------------------------------------------------

    std::vector<onerut_parser::AssetDeref>
    many_deref(
            const std::vector<onerut_parser::Asset> asset_argv) {
        std::vector<onerut_parser::AssetDeref> argv_asset_deref;
        argv_asset_deref.reserve(asset_argv.size());
        std::transform(cbegin(asset_argv), cend(asset_argv), back_inserter(argv_asset_deref),
                [](const onerut_parser::Asset & asset) {
                    return asset.deref();
                });
        return argv_asset_deref;
    }

    // -------------------------------------------------------------------------
    // ------------------ COMPILE RESULTS DEREF --------------------------------
    // -------------------------------------------------------------------------    

    bool
    is_integer(const onerut_parser::AssetDeref& arg) {
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<onerut_scalar::Integer>();
    }

    bool
    is_real_or_integer(const onerut_parser::AssetDeref& arg) {
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<onerut_scalar::Integer>() ||
                arg.is_given_type<onerut_scalar::Real>();
    }

    bool
    is_real_or_integer_or_complex(const onerut_parser::AssetDeref& arg) {
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<onerut_scalar::Integer>() ||
                arg.is_given_type<onerut_scalar::Real>() ||
                arg.is_given_type<onerut_scalar::Complex>();
    }

    bool
    is_normal_operator_domain(const onerut_parser::AssetDeref& arg) {
        using OperatorT = onerut_normal_operator::Domain;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<OperatorT>();
    }

    bool
    is_normal_operator_state_index(const onerut_parser::AssetDeref& arg) {
        using OperatorT = onerut_normal_operator::StateIndex;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<OperatorT>();
    }

    bool
    is_normal_operator(const onerut_parser::AssetDeref& arg) {
        using OperatorT = onerut_normal_operator::AbstractOperator;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<OperatorT>();
    }

    // -------------------------------------------------------------------------

    std::shared_ptr< const onerut_scalar::Integer>
    to_integer(const onerut_parser::AssetDeref& arg) {
        assert(is_integer(arg));
        const auto& arg_integer = *arg.typed_value_or_empty<onerut_scalar::Integer>();
        assert(arg_integer);
        return arg_integer;
    }

    std::shared_ptr< const onerut_scalar::Real>
    to_real(const onerut_parser::AssetDeref& arg) {
        assert(is_real_or_integer(arg));
        std::shared_ptr<onerut_scalar::Real> arg_real;
        if (auto temp = arg.typed_value_or_empty<onerut_scalar::Integer>()) {
            arg_real = *temp;
        } else {
            arg_real = *arg.typed_value_or_empty<onerut_scalar::Real>();
        }
        assert(arg_real);
        return arg_real;
    }

    std::shared_ptr< const onerut_scalar::Complex>
    to_complex(const onerut_parser::AssetDeref& arg) {
        assert(is_real_or_integer_or_complex(arg));
        std::shared_ptr<onerut_scalar::Complex> arg_complex;
        if (auto temp = arg.typed_value_or_empty<onerut_scalar::Integer>()) {
            arg_complex = *temp;
        } else if (auto temp = arg.typed_value_or_empty<onerut_scalar::Real>()) {
            arg_complex = *temp;
        } else {
            arg_complex = *arg.typed_value_or_empty<onerut_scalar::Complex>();
        }
        assert(arg_complex);
        return arg_complex;
    }

    std::shared_ptr < const onerut_normal_operator::Domain >
    to_normal_operator_domain(const onerut_parser::AssetDeref& arg) {
        assert(is_normal_operator_domain(arg));
        const auto& arg_typed = *arg.typed_value_or_empty<onerut_normal_operator::Domain>();
        assert(arg_typed);
        return arg_typed;
    }

    std::shared_ptr < const onerut_normal_operator::StateIndex >
    to_normal_operator_state_index(const onerut_parser::AssetDeref& arg) {
        assert(is_normal_operator_state_index(arg));
        const auto& arg_typed = *arg.typed_value_or_empty<onerut_normal_operator::StateIndex>();
        assert(arg_typed);
        return arg_typed;
    }

    std::shared_ptr < const onerut_normal_operator::AbstractOperator >
    to_normal_operator(const onerut_parser::AssetDeref& arg) {
        using OperatorT = onerut_normal_operator::AbstractOperator;
        assert(is_normal_operator(arg));
        const auto& arg_normal_operator = *arg.typed_value_or_empty<OperatorT>();
        assert(arg_normal_operator);
        return arg_normal_operator;
    }

    // -------------------------------------------------------------------------

    std::vector<std::shared_ptr < const onerut_scalar::Integer > >
    many_to_integer(std::vector<onerut_parser::AssetDeref> argv_asset_deref) {
        std::vector<std::shared_ptr < const onerut_scalar::Integer > > argv_integer;
        argv_integer.reserve(argv_asset_deref.size());
        std::transform(argv_asset_deref.cbegin(), argv_asset_deref.cend(),
                std::back_inserter(argv_integer), to_integer);
        return argv_integer;
    }

    std::vector<std::shared_ptr < const onerut_scalar::Real > >
    many_to_real(std::vector<onerut_parser::AssetDeref> argv_asset_deref) {
        std::vector<std::shared_ptr < const onerut_scalar::Real > > argv_real;
        argv_real.reserve(argv_asset_deref.size());
        std::transform(argv_asset_deref.cbegin(), argv_asset_deref.cend(),
                std::back_inserter(argv_real), to_real);
        return argv_real;
    }

    std::vector<std::shared_ptr < const onerut_scalar::Complex > >
    many_to_complex(std::vector<onerut_parser::AssetDeref> argv_asset_deref) {
        std::vector<std::shared_ptr < const onerut_scalar::Complex > > argv_complex;
        argv_complex.reserve(argv_asset_deref.size());
        std::transform(argv_asset_deref.cbegin(), argv_asset_deref.cend(),
                std::back_inserter(argv_complex), to_complex);
        return argv_complex;
    }

    std::vector<std::shared_ptr < const onerut_normal_operator::AbstractOperator > >
    many_to_normal_operator(std::vector<onerut_parser::AssetDeref> argv_asset_deref) {
        std::vector< std::shared_ptr < const onerut_normal_operator::AbstractOperator > > argv_operator;
        argv_operator.reserve(argv_asset_deref.size());
        std::transform(argv_asset_deref.cbegin(), argv_asset_deref.cend(),
                std::back_inserter(argv_operator), to_normal_operator);
        return argv_operator;
    }
    
}