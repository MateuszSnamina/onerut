#include<onerut_parser_exec/compiler_rules.hpp>
#include<onerut_parser_rules/function_factory_container.hpp>

#ifndef ONERUT_PARSER_COMPILER_RULES_CONCRETE_HPP
#define ONERUT_PARSER_COMPILER_RULES_CONCRETE_HPP

namespace onerut_parser {

    class CompilerRulesConcrete : public CompilerRules {
    public:
        CompilerRulesConcrete();
        Asset op_plus_minus(Asset first_arg_asset, std::vector<Asset> other_argv_asset, std::vector<char> opv) const override;
        Asset op_prod_div(Asset first_arg_asset, std::vector<Asset> other_argv_asset, std::vector<char> opv) const override;
        Asset op_pow(Asset first_arg_asset, Asset second_arg_asset) const override;
        Asset op_at(Asset first_arg_asset, Asset second_arg_asset) const override;
        Asset op_arrow(Asset first_arg_asset, Asset second_arg_asset) const override;
        Asset op_glue(Asset first_arg_asset, Asset second_arg_asset) const override;
        Asset op_unary_plus_minus(Asset arg_asset, char op) const override;
        Asset lit_long(long value) const override;
        Asset lit_double(double value) const override;
        Asset lit_pure_complex_double(double value) const override;
        Asset function(const std::string& name, const std::vector<Asset>& argv_asset) const override;
    private:
        FunctionFactoryContainer function_factory_container;//TODO make it const...
    };

}

#endif