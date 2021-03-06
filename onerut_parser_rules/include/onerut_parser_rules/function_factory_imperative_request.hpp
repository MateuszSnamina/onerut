#ifndef ONERUT_PARSER_RULES_FUNCTION_FACTORY_IMPERATIVE_REQUEST
#define ONERUT_PARSER_RULES_FUNCTION_FACTORY_IMPERATIVE_REQUEST

#include<onerut_parser_rules/function_factory_abstract.hpp>

namespace onerut_parser_rules {

    class LatchRequestFunctionFactory : public NaryFunctionFactory<1> {
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };

    class ResetRequestFunctionFactory : public NaryFunctionFactory<1> {
        onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> args_asset) const override;
    };
}

#endif
