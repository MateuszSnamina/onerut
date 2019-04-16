#include<algorithm>

#include<onerut_parser_exec/asset_utility.hpp>

namespace onerut_parser::utility {

    // -------------------------------------------------------------------------
    // ------------------ ASSET ------------------------------------------------
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

    bool
    any_of_is_compile_error(
            std::vector<onerut_parser::AssetDeref> argv_asset) {
        return
        std::any_of(argv_asset.cbegin(), argv_asset.cend(),
                [](const onerut_parser::AssetDeref & asset) {
                    return asset.is_compile_error();
                });
    }

    bool
    any_of_is_compile_error(
            onerut_parser::AssetDeref first_arg_asset,
            std::vector<onerut_parser::AssetDeref> other_argv_asset) {
        return first_arg_asset.is_compile_error() ||
                std::any_of(other_argv_asset.cbegin(), other_argv_asset.cend(),
                [](const onerut_parser::AssetDeref & asset) {
                    return asset.is_compile_error();
                });
    }

    bool
    all_of_is_either_value_or_type(
            std::vector<onerut_parser::AssetDeref> argv_asset) {
        return
        std::all_of(argv_asset.cbegin(), argv_asset.cend(),
                [](const onerut_parser::AssetDeref & asset) {
                    return asset.is_either_value_or_type();
                });
    }

    bool
    all_of_is_either_value_or_type(
            onerut_parser::AssetDeref first_arg_asset,
            std::vector<onerut_parser::AssetDeref> other_argv_asset) {
        return first_arg_asset.is_either_value_or_type() &&
                std::all_of(other_argv_asset.cbegin(), other_argv_asset.cend(),
                [](const onerut_parser::AssetDeref & asset) {
                    return asset.is_either_value_or_type();
                });
    }

    // -------------------------------------------------------------------------

}