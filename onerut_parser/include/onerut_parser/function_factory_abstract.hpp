#ifndef ONERUT_PARSER_FUNCTION_ABSTRACT
#define ONERUT_PARSER_FUNCTION_ABSTRACT

#include<array>
#include<vector>

#include<onerut_parser/asset.hpp>

namespace onerut_parser {

    class AbstractFunctionFactory {
    public:
        virtual Asset make_function_otherwise_make_error(const std::vector<Asset>& argv) const = 0;
        virtual ~AbstractFunctionFactory() = default;
    };
   
    template<unsigned nary>
    class NaryFunctionFactory : public AbstractFunctionFactory {
    public:
        Asset make_function_otherwise_make_error(const std::vector<Asset>& argv) const final;
        virtual Asset make_function_otherwise_make_error(std::array<Asset, nary> args) const = 0;
    };

    // ---------------------------------------------------------------------------
    // -------  template functions implementation  -------------------------------
    // ---------------------------------------------------------------------------

    template<unsigned nary>
    Asset
    NaryFunctionFactory<nary>::make_function_otherwise_make_error(const std::vector<Asset>& argv) const {
        if (argv.size() != nary)
            return Asset::from_compile_error(std::make_shared<WrongNumberOfArgumentsError>());
        std::array<Asset, nary> args_array;
        std::copy(cbegin(argv), cend(argv), begin(args_array));
        return make_function_otherwise_make_error(args_array);
    }

}

#endif
