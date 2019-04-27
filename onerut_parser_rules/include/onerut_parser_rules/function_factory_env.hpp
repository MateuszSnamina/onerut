#ifndef ONERUT_PARSER_RULES_FUNCTION_FACTORY_ENV
#define ONERUT_PARSER_RULES_FUNCTION_FACTORY_ENV

#include<onerut_parser_rules/function_factory_abstract.hpp>

namespace onerut_parser_rules {

    class BindToEnvFunctionFactory : public NaryFunctionFactory<2> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> argv) const override;
    };

}

#endif