#ifndef ONERUT_PARSER_EXEC_COMILER_RULES_HPP
#define ONERUT_PARSER_EXEC_COMILER_RULES_HPP

#include<vector>
#include<string>
#include<onerut_parser_exec/asset.hpp>

namespace onerut_parser_exec {

    class CompilerRules {
    public:
        virtual Asset op_plus_minus(Asset first_arg_asset, std::vector<Asset> other_argv_asset, std::vector<char> opv) const;
        virtual Asset op_prod_div(Asset first_arg_asset, std::vector<Asset> other_argv_asset, std::vector<char> opv) const;
        virtual Asset op_pow(Asset first_arg_asset, Asset second_arg_asset) const;
        virtual Asset op_at(Asset first_arg_asset, Asset second_arg_asset) const;
        virtual Asset op_arrow(Asset first_arg_asset, Asset second_arg_asset) const;
        virtual Asset op_glue(Asset first_arg_asset, Asset second_arg_asset) const;
        virtual Asset op_unary_plus_minus(Asset arg_asset, char op) const;
        virtual Asset lit_long(long value) const;
        virtual Asset lit_double(double value) const;
        virtual Asset lit_pure_complex_double(double value) const;
        virtual Asset function(const std::string & name, const std::vector<Asset> & argv_asset) const;
    };

}

#endif