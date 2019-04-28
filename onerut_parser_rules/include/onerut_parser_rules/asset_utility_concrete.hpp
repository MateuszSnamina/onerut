#ifndef ONERUT_PARSER_RULES_ASSET_UTILITY_CONCRETE
#define ONERUT_PARSER_RULES_ASSET_UTILITY_CONCRETE

#include<vector>

#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_env/env.hpp>
#include<onerut_convergence_parameter/convergence_parameter.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/domain_oscillator.hpp>
#include<onerut_normal_operator/domain_spin.hpp>
#include<onerut_normal_operator/domain_eg.hpp>
#include<onerut_normal_operator/domain_kron.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>
#include<onerut_parser_exec/asset.hpp>

namespace onerut_parser_rules::utility {

    // -------------------------------------------------------------------------
    // ------------------ ASSET DEREF ------------------------------------------
    // -------------------------------------------------------------------------

    bool
    is_integer(const onerut_parser_exec::AssetDeref&);

    bool
    is_real_or_integer(const onerut_parser_exec::AssetDeref&);

    bool
    is_real_or_integer_or_complex(const onerut_parser_exec::AssetDeref&);

    bool
    is_env(const onerut_parser_exec::AssetDeref&);

    bool
    is_convergence_parameter(const onerut_parser_exec::AssetDeref&);

    bool
    is_normal_operator_domain(const onerut_parser_exec::AssetDeref&);

    bool
    is_oscillator_operator_domain(const onerut_parser_exec::AssetDeref&);

    bool
    is_spin_operator_domain(const onerut_parser_exec::AssetDeref&);

    bool
    is_eg_operator_domain(const onerut_parser_exec::AssetDeref&);

    bool
    is_kron_operator_domain(const onerut_parser_exec::AssetDeref&);

    bool
    is_normal_operator_state_index(const onerut_parser_exec::AssetDeref&);

    bool
    is_kron_operator_domain_placeholder(const onerut_parser_exec::AssetDeref&);

    bool
    is_normal_operator(const onerut_parser_exec::AssetDeref&);

    //bool
    //is_fermion_operator(const onerut_parser_exec::AssetDeref&);

    //bool
    //is_boson_operator(const onerut_parser_exec::AssetDeref&);

    bool
    is_normal_operator_eig(const onerut_parser_exec::AssetDeref&);

    bool
    is_normal_operator_mean(const onerut_parser_exec::AssetDeref&);

    // -------------------------------------------------------------------------

    std::shared_ptr< const onerut_scalar::Integer>
    to_integer(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr< const onerut_scalar::Real>
    to_real(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr< const onerut_scalar::Complex>
    to_complex(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr<onerut_env::Env>
    to_env(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr<onerut_convergence_parameter::ConvergenceParameter>
    to_convergence_parameter(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr < const onerut_normal_operator::Domain >
    to_normal_operator_domain(const onerut_parser_exec::AssetDeref&); // includes spin and oscillator.

    std::shared_ptr < const onerut_normal_operator::OscillatorDomain >
    to_oscillator_operator_domain(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr < const onerut_normal_operator::SpinDomain >
    to_spin_operator_domain(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr < const onerut_normal_operator::EgDomain >
    to_eg_operator_domain(const onerut_parser_exec::AssetDeref&);
    
    std::shared_ptr < const onerut_normal_operator::KronDomain >
    to_kron_operator_domain(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr < const onerut_normal_operator::StateIndex >
    to_normal_operator_state_index(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr < const onerut_normal_operator::KronPlaceholder >
    to_kron_operator_domain_placeholder(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr < const onerut_normal_operator::AbstractRealOperator >
    to_normal_operator(const onerut_parser_exec::AssetDeref&);

    //    std::shared_ptr<onerut_operator::AbstractRealOperator<FERMION_KET_T> >
    //    to_fermion_operator(const onerut_parser_exec::AssetDeref&);

    //    std::shared_ptr<onerut_operator::AbstractRealOperator<BOSON_KET_T> >
    //    to_boson_operator(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr < onerut_normal_operator::Eig >
    to_normal_operator_eig(const onerut_parser_exec::AssetDeref&);

    std::shared_ptr < onerut_normal_operator::Mean >
    to_normal_operator_mean(const onerut_parser_exec::AssetDeref&);

    // -------------------------------------------------------------------------

    std::vector<std::shared_ptr <const onerut_scalar::Integer > >
    many_to_integer(std::vector<onerut_parser_exec::AssetDeref>);

    std::vector<std::shared_ptr <const onerut_scalar::Real > >
    many_to_real(std::vector<onerut_parser_exec::AssetDeref>);

    std::vector<std::shared_ptr <const onerut_scalar::Complex > >
    many_to_complex(std::vector<onerut_parser_exec::AssetDeref>);

    std::vector<std::shared_ptr < const onerut_normal_operator::AbstractRealOperator > >
    many_to_normal_operator(std::vector<onerut_parser_exec::AssetDeref>);

    //    std::vector<std::shared_ptr < onerut_operator::AbstractRealOperator<FERMION_KET_T> > >
    //    many_to_fermion_operator(std::vector<onerut_parser_exec::AssetDeref> argv_asset_deref);

    //    std::vector<std::shared_ptr < onerut_operator::AbstractRealOperator<BOSON_KET_T> > >
    //    many_to_bozon_operator(std::vector<onerut_parser_exec::AssetDeref> argv_asset_deref);

    std::vector<std::shared_ptr < const onerut_normal_operator::Domain > >
    many_to_normal_operator_domain(std::vector<onerut_parser_exec::AssetDeref>);

}

#endif