#ifndef ONERUT_PARSER_RULES_COMPILER_RULES_CONCRETE_HPP
#define ONERUT_PARSER_RULES_COMPILER_RULES_CONCRETE_HPP

#include<onerut_parser_exec/compiler_rules.hpp>
#include<onerut_parser_rules/map_with_function_factories.hpp>

namespace onerut_parser_rules {

    class CompilerRulesConcrete : public onerut_parser_exec::CompilerRules {
    public:
        CompilerRulesConcrete();
        onerut_parser_exec::Asset op_plus_minus(onerut_parser_exec::Asset first_arg_asset, std::vector<onerut_parser_exec::Asset> other_argv_asset, std::vector<char> opv) const override;
        onerut_parser_exec::Asset op_prod_div(onerut_parser_exec::Asset first_arg_asset, std::vector<onerut_parser_exec::Asset> other_argv_asset, std::vector<char> opv) const override;
        onerut_parser_exec::Asset op_pow(onerut_parser_exec::Asset first_arg_asset, onerut_parser_exec::Asset second_arg_asset) const override;
        onerut_parser_exec::Asset op_at(onerut_parser_exec::Asset first_arg_asset, onerut_parser_exec::Asset second_arg_asset) const override;
        onerut_parser_exec::Asset op_arrow(onerut_parser_exec::Asset first_arg_asset, onerut_parser_exec::Asset second_arg_asset) const override;
        onerut_parser_exec::Asset op_glue(onerut_parser_exec::Asset first_arg_asset, onerut_parser_exec::Asset second_arg_asset) const override;
        onerut_parser_exec::Asset op_unary_plus_minus(onerut_parser_exec::Asset arg_asset, char op) const override;
        onerut_parser_exec::Asset lit_long(long value) const override;
        onerut_parser_exec::Asset lit_double(double value) const override;
        onerut_parser_exec::Asset lit_pure_complex_double(double value) const override;
        onerut_parser_exec::Asset function(const std::string& name, const std::vector<onerut_parser_exec::Asset>& argv_asset) const override;
    private:
        const MapWithFunctionFactories map_with_function_factories;
    };

}

#endif