#ifndef ONERUT_PARSER_BUILD_RESULT_UTILITY
#define ONERUT_PARSER_BUILD_RESULT_UTILITY

#include<vector>

#include<onerut_parser/asset.hpp>
#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/operator_oscillator.hpp>
#include<onerut_normal_operator/operator_spin.hpp>
#include<onerut_normal_operator/diagonalizator.hpp>

namespace onerut_parser::utility {

    // -------------------------------------------------------------------------
    // ------------------ COMPILE RESULTS --------------------------------------
    // -------------------------------------------------------------------------

    bool
    is_not_const_ref(const onerut_parser::Asset&);

    bool
    is_const_ref(const onerut_parser::Asset&);

    bool
    is_unset_ref(const onerut_parser::Asset&);

    std::shared_ptr<onerut_parser::AssetNotConstRef>
    to_not_const_ref(const onerut_parser::Asset&);

    std::string
    name_of_unset_ref(const onerut_parser::Asset&);

    // -------------------------------------------------------------------------

    std::vector<onerut_parser::AssetDeref>
    many_deref(const std::vector<onerut_parser::Asset>);

    // -------------------------------------------------------------------------
    // ------------------ COMPILE RESULTS DEREF --------------------------------
    // -------------------------------------------------------------------------

    bool
    is_integer(const onerut_parser::AssetDeref&);

    bool
    is_real_or_integer(const onerut_parser::AssetDeref&);

    bool
    is_real_or_integer_or_complex(const onerut_parser::AssetDeref&);

    bool
    is_normal_operator_domain(const onerut_parser::AssetDeref&);

    bool
    is_oscillator_operator_domain(const onerut_parser::AssetDeref&);

    bool
    is_spin_operator_domain(const onerut_parser::AssetDeref&);

    bool
    is_normal_operator_state_index(const onerut_parser::AssetDeref&);

    bool
    is_normal_operator(const onerut_parser::AssetDeref&);

    //bool
    //is_fermion_operator(const onerut_parser::AssetDeref&);

    //bool
    //is_boson_operator(const onerut_parser::AssetDeref&);

    bool
    is_normal_operator_eigs(const onerut_parser::AssetDeref&);

    // -------------------------------------------------------------------------

    std::shared_ptr< const onerut_scalar::Integer>
    to_integer(const onerut_parser::AssetDeref&);

    std::shared_ptr< const onerut_scalar::Real>
    to_real(const onerut_parser::AssetDeref&);

    std::shared_ptr< const onerut_scalar::Complex>
    to_complex(const onerut_parser::AssetDeref&);

    std::shared_ptr < const onerut_normal_operator::Domain >
    to_normal_operator_domain(const onerut_parser::AssetDeref&); // includes spin and oscillator.

    std::shared_ptr < const onerut_normal_operator::OscillatorDomain >
    to_oscillator_operator_domain(const onerut_parser::AssetDeref&);

    std::shared_ptr < const onerut_normal_operator::SpinDomain >
    to_spin_operator_domain(const onerut_parser::AssetDeref&);

    std::shared_ptr < const onerut_normal_operator::StateIndex >
    to_normal_operator_state_index(const onerut_parser::AssetDeref&);

    std::shared_ptr < const onerut_normal_operator::AbstractOperator >
    to_normal_operator(const onerut_parser::AssetDeref&);

    //    std::shared_ptr<onerut_operator::AbstractOperator<FERMION_KET_T> >
    //    to_fermion_operator(const onerut_parser::AssetDeref&);

    //    std::shared_ptr<onerut_operator::AbstractOperator<BOSON_KET_T> >
    //    to_boson_operator(const onerut_parser::AssetDeref&);

    std::shared_ptr < onerut_normal_operator::Eigs >
    to_normal_operator_eigs(const onerut_parser::AssetDeref&);

    // -------------------------------------------------------------------------

    std::vector<std::shared_ptr <const onerut_scalar::Integer > >
    many_to_integer(std::vector<onerut_parser::AssetDeref>);

    std::vector<std::shared_ptr <const onerut_scalar::Real > >
    many_to_real(std::vector<onerut_parser::AssetDeref>);

    std::vector<std::shared_ptr <const onerut_scalar::Complex > >
    many_to_complex(std::vector<onerut_parser::AssetDeref>);

    std::vector<std::shared_ptr < const onerut_normal_operator::AbstractOperator > >
    many_to_normal_operator(std::vector<onerut_parser::AssetDeref> argv_asset_deref);

    //    std::vector<std::shared_ptr < onerut_operator::AbstractOperator<FERMION_KET_T> > >
    //    many_to_fermion_operator(std::vector<onerut_parser::AssetDeref> argv_asset_deref);

    //    std::vector<std::shared_ptr < onerut_operator::AbstractOperator<BOSON_KET_T> > >
    //    many_to_bozon_operator(std::vector<onerut_parser::AssetDeref> argv_asset_deref);

}

#endif