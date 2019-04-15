#ifndef ONERUT_PARSER_FUNCTION_FACTORY_PRINT_VALUE_REQUEST
#define ONERUT_PARSER_FUNCTION_FACTORY_PRINT_VALUE_REQUEST

#include<onerut_parser_concrete/function_factory_abstract.hpp>

namespace onerut_parser {

    class PrintValueRequestFunctionFactory : public NaryFunctionFactory<1> {
        Asset make_function_otherwise_make_error(std::array<Asset, 1> args_asset) const override;
    };

}

#endif
