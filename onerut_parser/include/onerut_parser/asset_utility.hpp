#ifndef ONERUT_PARSER_ASSET_UTILITY
#define ONERUT_PARSER_ASSET_UTILITY

#include<vector>

#include<onerut_parser/asset.hpp>
#include<onerut_scalar/scalar_abstract.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/domain_custom.hpp>
#include<onerut_normal_operator/domain_oscillator.hpp>
#include<onerut_normal_operator/domain_spin.hpp>
#include<onerut_normal_operator/domain_kron.hpp>
#include<onerut_normal_operator/eig.hpp>
#include<onerut_normal_operator/mean.hpp>

namespace onerut_parser::utility {

    // -------------------------------------------------------------------------
    // ------------------ ASSET ------------------------------------------------
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

    bool
    any_of_is_compile_error(
            std::vector<onerut_parser::AssetDeref>);
    bool
    any_of_is_compile_error(
            onerut_parser::AssetDeref,
            std::vector<onerut_parser::AssetDeref>);

    bool
    all_of_is_either_value_or_type(
            std::vector<onerut_parser::AssetDeref>);

    bool
    all_of_is_either_value_or_type(
            onerut_parser::AssetDeref,
            std::vector<onerut_parser::AssetDeref>);

    // -------------------------------------------------------------------------
    
}

#endif