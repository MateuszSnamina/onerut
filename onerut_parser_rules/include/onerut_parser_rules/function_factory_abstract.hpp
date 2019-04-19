#ifndef ONERUT_PARSER_RULES_FUNCTION_ABSTRACT
#define ONERUT_PARSER_RULES_FUNCTION_ABSTRACT

#include<array>
#include<vector>

#include<onerut_parser_exec/asset.hpp>

namespace onerut_parser_rules {

    class AbstractFunctionFactory {
    public:
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(const std::vector<onerut_parser_exec::Asset>& argv) const = 0;
        virtual ~AbstractFunctionFactory() = default;
    };
   
    template<unsigned nary>
    class NaryFunctionFactory : public AbstractFunctionFactory {
    public:
        onerut_parser_exec::Asset make_function_otherwise_make_error(const std::vector<onerut_parser_exec::Asset>& argv) const final;
        virtual onerut_parser_exec::Asset make_function_otherwise_make_error(std::array<onerut_parser_exec::Asset, nary> args) const = 0;
    };

    // ---------------------------------------------------------------------------
    // -------  template functions implementation  -------------------------------
    // ---------------------------------------------------------------------------

    template<unsigned nary>
    onerut_parser_exec::Asset
    NaryFunctionFactory<nary>::make_function_otherwise_make_error(const std::vector<onerut_parser_exec::Asset>& argv) const {
        if (argv.size() != nary)
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::WrongNumberOfArgumentsError>());
        std::array<onerut_parser_exec::Asset, nary> args_array;
        std::copy(cbegin(argv), cend(argv), begin(args_array));
        return make_function_otherwise_make_error(args_array);
    }

}

#endif
