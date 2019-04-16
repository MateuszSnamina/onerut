#include<algorithm>

#include<onerut_parser_rules/asset_utility_concrete.hpp>

namespace onerut_parser_rules::utility {

    // -------------------------------------------------------------------------
    // ------------------ ASSET DEREF ------------------------------------------
    // -------------------------------------------------------------------------    

    bool
    is_integer(const onerut_parser_exec::AssetDeref& arg) {
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<onerut_scalar::Integer>();
    }

    bool
    is_real_or_integer(const onerut_parser_exec::AssetDeref& arg) {
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<onerut_scalar::Integer>() ||
                arg.is_given_type<onerut_scalar::Real>() ||
                arg.is_given_type<onerut_normal_operator::Mean>();
    }

    bool
    is_real_or_integer_or_complex(const onerut_parser_exec::AssetDeref& arg) {
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<onerut_scalar::Integer>() ||
                arg.is_given_type<onerut_scalar::Real>() ||
                arg.is_given_type<onerut_scalar::Complex>() ||
                arg.is_given_type<onerut_normal_operator::Mean>();
    }

    bool
    is_normal_operator_domain(const onerut_parser_exec::AssetDeref& arg) {
        using CustomDomainT = onerut_normal_operator::CustomDomain;
        using OscillatorDomainT = onerut_normal_operator::OscillatorDomain;
        using SpinDomainT = onerut_normal_operator::SpinDomain;
        using KronDomainT = onerut_normal_operator::KronDomain;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<CustomDomainT>() ||
                arg.is_given_type<OscillatorDomainT>() ||
                arg.is_given_type<SpinDomainT>() ||
                arg.is_given_type<KronDomainT>();
    }

    bool
    is_oscillator_operator_domain(const onerut_parser_exec::AssetDeref& arg) {
        using DomainT = onerut_normal_operator::OscillatorDomain;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<DomainT>();
    }

    bool
    is_spin_operator_domain(const onerut_parser_exec::AssetDeref& arg) {
        using DomainT = onerut_normal_operator::SpinDomain;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<DomainT>();
    }

    bool
    is_kron_operator_domain(const onerut_parser_exec::AssetDeref& arg) {
        using DomainT = onerut_normal_operator::KronDomain;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<DomainT>();
    }

    bool
    is_normal_operator_state_index(const onerut_parser_exec::AssetDeref& arg) {
        using StateT = onerut_normal_operator::StateIndex;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<StateT>();
    }

    bool
    is_kron_operator_domain_placeholder(const onerut_parser_exec::AssetDeref& arg) {
        using PlaceholderT = onerut_normal_operator::KronPlaceholder;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<PlaceholderT>();
    }

    bool
    is_normal_operator(const onerut_parser_exec::AssetDeref& arg) {
        using OperatorT = onerut_normal_operator::AbstractRealOperator;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<OperatorT>();
    }

    bool
    is_normal_operator_eig(const onerut_parser_exec::AssetDeref& arg) {
        using EigT = onerut_normal_operator::Eig;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<EigT>();
    }

    bool
    is_normal_operator_mean(const onerut_parser_exec::AssetDeref& arg) {
        using MeanT = onerut_normal_operator::Mean;
        assert(!arg.is_empty());
        assert(!arg.is_compile_error());
        return arg.is_given_type<MeanT>();
    }

    // -------------------------------------------------------------------------

    std::shared_ptr< const onerut_scalar::Integer>
    to_integer(const onerut_parser_exec::AssetDeref& arg) {
        assert(is_integer(arg));
        const auto& arg_integer = *arg.typed_value_or_empty<onerut_scalar::Integer>();
        assert(arg_integer);
        return arg_integer;
    }

    std::shared_ptr< const onerut_scalar::Real>
    to_real(const onerut_parser_exec::AssetDeref& arg) {
        assert(is_real_or_integer(arg));
        std::shared_ptr<onerut_scalar::Real> arg_real;
        if (auto temp = arg.typed_value_or_empty<onerut_scalar::Integer>()) {
            arg_real = *temp;
        } else if (auto temp = arg.typed_value_or_empty<onerut_scalar::Real>()) {
            arg_real = *temp;
        } else {
            arg_real = *arg.typed_value_or_empty<onerut_normal_operator::Mean>();
        }
        assert(arg_real);
        return arg_real;
    }

    std::shared_ptr< const onerut_scalar::Complex>
    to_complex(const onerut_parser_exec::AssetDeref& arg) {
        assert(is_real_or_integer_or_complex(arg));
        std::shared_ptr<const onerut_scalar::Complex> arg_complex;
        if (const auto temp = arg.typed_value_or_empty<onerut_scalar::Integer>()) {
            arg_complex = *temp;
        } else if (const auto temp = arg.typed_value_or_empty<onerut_scalar::Real>()) {
            arg_complex = *temp;
        } else if (auto temp = arg.typed_value_or_empty<onerut_scalar::Complex>()) {
            arg_complex = *temp;
        } else {
            arg_complex = *arg.typed_value_or_empty<onerut_normal_operator::Mean>();
        }
        assert(arg_complex);
        return arg_complex;
    }

    std::shared_ptr < const onerut_normal_operator::Domain >
    to_normal_operator_domain(const onerut_parser_exec::AssetDeref& arg) {
        using CustomDomainT = onerut_normal_operator::CustomDomain;
        using OscillatorDomainT = onerut_normal_operator::OscillatorDomain;
        using SpinDomainT = onerut_normal_operator::SpinDomain;
        using KronDomainT = onerut_normal_operator::KronDomain;        
        assert(is_normal_operator_domain(arg));
        std::shared_ptr<const onerut_normal_operator::Domain> arg_domain;
        if (const auto temp = arg.typed_value_or_empty<CustomDomainT>()) {
            arg_domain = *temp;
        } else if (const auto temp = arg.typed_value_or_empty<OscillatorDomainT>()) {
            arg_domain = *temp;
        } else if (const auto temp = arg.typed_value_or_empty<SpinDomainT>()) {
            arg_domain = *temp;
        } else {
            arg_domain = *arg.typed_value_or_empty<KronDomainT>();
        }
        assert(arg_domain);
        return arg_domain;
    }

    std::shared_ptr < const onerut_normal_operator::OscillatorDomain >
    to_oscillator_operator_domain(const onerut_parser_exec::AssetDeref& arg) {
        using DomainT = onerut_normal_operator::OscillatorDomain;                
        assert(is_oscillator_operator_domain(arg));
        const auto& arg_typed = *arg.typed_value_or_empty<DomainT>();
        assert(arg_typed);
        return arg_typed;
    }

    std::shared_ptr < const onerut_normal_operator::SpinDomain >
    to_spin_operator_domain(const onerut_parser_exec::AssetDeref& arg) {
        using DomainT = onerut_normal_operator::SpinDomain;                
        assert(is_spin_operator_domain(arg));
        const auto& arg_typed = *arg.typed_value_or_empty<DomainT>();
        assert(arg_typed);
        return arg_typed;
    }

    std::shared_ptr < const onerut_normal_operator::KronDomain >
    to_kron_operator_domain(const onerut_parser_exec::AssetDeref& arg) {
        using DomainT = onerut_normal_operator::KronDomain;        
        assert(is_kron_operator_domain(arg));
        const auto& arg_typed = *arg.typed_value_or_empty<DomainT>();
        assert(arg_typed);
        return arg_typed;
    }

    std::shared_ptr < const onerut_normal_operator::StateIndex >
    to_normal_operator_state_index(const onerut_parser_exec::AssetDeref& arg) {
        using StateT = onerut_normal_operator::StateIndex;
        assert(is_normal_operator_state_index(arg));
        const auto& arg_typed = *arg.typed_value_or_empty<StateT>();
        assert(arg_typed);
        return arg_typed;
    }

    std::shared_ptr < const onerut_normal_operator::KronPlaceholder >
    to_kron_operator_domain_placeholder(const onerut_parser_exec::AssetDeref& arg) {
        using PlaceholderT = onerut_normal_operator::KronPlaceholder;
        assert(is_kron_operator_domain_placeholder(arg));
        const auto& arg_typed = *arg.typed_value_or_empty<PlaceholderT>();
        assert(arg_typed);
        return arg_typed;
    }

    std::shared_ptr < const onerut_normal_operator::AbstractRealOperator >
    to_normal_operator(const onerut_parser_exec::AssetDeref& arg) {
        using OperatorT = onerut_normal_operator::AbstractRealOperator;
        assert(is_normal_operator(arg));
        const auto& arg_normal_operator = *arg.typed_value_or_empty<OperatorT>();
        assert(arg_normal_operator);
        return arg_normal_operator;
    }

    std::shared_ptr < onerut_normal_operator::Eig >
    to_normal_operator_eig(const onerut_parser_exec::AssetDeref& arg) {
        using EigT = onerut_normal_operator::Eig;
        assert(is_normal_operator_eig(arg));
        const auto& arg_normal_operator = *arg.typed_value_or_empty<EigT>();
        assert(arg_normal_operator);
        return arg_normal_operator;
    }

    std::shared_ptr < onerut_normal_operator::Mean >
    to_normal_operator_mean(const onerut_parser_exec::AssetDeref& arg) {
        using MeanT = onerut_normal_operator::Mean;
        assert(is_normal_operator_mean(arg));
        const auto& arg_normal_operator = *arg.typed_value_or_empty<MeanT>();
        assert(arg_normal_operator);
        return arg_normal_operator;
    }

    // -------------------------------------------------------------------------

    std::vector<std::shared_ptr < const onerut_scalar::Integer > >
    many_to_integer(std::vector<onerut_parser_exec::AssetDeref> argv_asset_deref) {
        std::vector<std::shared_ptr < const onerut_scalar::Integer > > argv_integer;
        argv_integer.reserve(argv_asset_deref.size());
        std::transform(argv_asset_deref.cbegin(), argv_asset_deref.cend(),
                std::back_inserter(argv_integer), to_integer);
        return argv_integer;
    }

    std::vector<std::shared_ptr < const onerut_scalar::Real > >
    many_to_real(std::vector<onerut_parser_exec::AssetDeref> argv_asset_deref) {
        std::vector<std::shared_ptr < const onerut_scalar::Real > > argv_real;
        argv_real.reserve(argv_asset_deref.size());
        std::transform(argv_asset_deref.cbegin(), argv_asset_deref.cend(),
                std::back_inserter(argv_real), to_real);
        return argv_real;
    }

    std::vector<std::shared_ptr < const onerut_scalar::Complex > >
    many_to_complex(std::vector<onerut_parser_exec::AssetDeref> argv_asset_deref) {
        std::vector<std::shared_ptr < const onerut_scalar::Complex > > argv_complex;
        argv_complex.reserve(argv_asset_deref.size());
        std::transform(argv_asset_deref.cbegin(), argv_asset_deref.cend(),
                std::back_inserter(argv_complex), to_complex);
        return argv_complex;
    }

    std::vector<std::shared_ptr < const onerut_normal_operator::AbstractRealOperator > >
    many_to_normal_operator(std::vector<onerut_parser_exec::AssetDeref> argv_asset_deref) {
        std::vector< std::shared_ptr < const onerut_normal_operator::AbstractRealOperator > > argv_operator;
        argv_operator.reserve(argv_asset_deref.size());
        std::transform(argv_asset_deref.cbegin(), argv_asset_deref.cend(),
                std::back_inserter(argv_operator), to_normal_operator);
        return argv_operator;
    }

    std::vector<std::shared_ptr < const onerut_normal_operator::Domain > >
    many_to_normal_operator_domain(std::vector<onerut_parser_exec::AssetDeref> argv_asset_deref) {
        std::vector< std::shared_ptr < const onerut_normal_operator::Domain > > argv_operator;
        argv_operator.reserve(argv_asset_deref.size());
        std::transform(argv_asset_deref.cbegin(), argv_asset_deref.cend(),
                std::back_inserter(argv_operator), to_normal_operator_domain);
        return argv_operator;
    }

}