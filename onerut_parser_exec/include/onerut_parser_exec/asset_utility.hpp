#ifndef ONERUT_PARSER_ASSET_UTILITY
#define ONERUT_PARSER_ASSET_UTILITY

#include<vector>

#include<onerut_parser_exec/asset.hpp>

namespace onerut_parser_exec::utility {

    // -------------------------------------------------------------------------
    // ------------------ ASSET ------------------------------------------------
    // -------------------------------------------------------------------------

    bool
    is_not_const_ref(const Asset&);

    bool
    is_const_ref(const Asset&);

    bool
    is_unset_ref(const Asset&);

    std::shared_ptr<AssetNotConstRef>
    to_not_const_ref(const Asset&);

    std::string
    name_of_unset_ref(const Asset&);

    // -------------------------------------------------------------------------

    std::vector<AssetDeref>
    many_deref(const std::vector<Asset>);

    // -------------------------------------------------------------------------

    bool
    any_of_is_compile_error(
            std::vector<AssetDeref>);
    bool
    any_of_is_compile_error(
            AssetDeref,
            std::vector<AssetDeref>);

    bool
    all_of_is_either_value_or_type(
            std::vector<AssetDeref>);

    bool
    all_of_is_either_value_or_type(
            AssetDeref,
            std::vector<AssetDeref>);

    // -------------------------------------------------------------------------
    
}

#endif