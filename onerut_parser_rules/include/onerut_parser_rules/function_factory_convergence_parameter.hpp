#ifndef ONERUT_PARSER_RULES_FUNCTION_FACTORY_CONVERGENCE_PARAMETER
#define ONERUT_PARSER_RULES_FUNCTION_FACTORY_CONVERGENCE_PARAMETER

#include<onerut_parser_rules/function_factory_abstract.hpp>

namespace onerut_parser_rules {

    class CreateConvergenceParameterFunctionFactory : public NaryFunctionFactory<1> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 1> argv) const override;
    };

    class ArrowFunctionFactory : public NaryFunctionFactory<2> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> argv) const override;
    };

    class GlueFunctionFactory : public NaryFunctionFactory<2> {
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, 2> argv) const override;
    };

}

#endif