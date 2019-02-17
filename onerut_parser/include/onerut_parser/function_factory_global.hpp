#ifndef ONERUT_PARSER_FUNCTION_FACTORY_GLOBAL
#define ONERUT_PARSER_FUNCTION_FACTORY_GLOBAL

#include<optional>
#include<string>
#include<map>
#include<onerut_parser/function_factory_abstract.hpp>

namespace onerut_parser {

    class GlobalFunctionFactories {
    public:
        static GlobalFunctionFactories& instance();
        std::optional<std::shared_ptr<AbstractFunctionFactory>> get_or_empty(const std::string& name) const;
        bool put(const std::string& name, std::shared_ptr<AbstractFunctionFactory> function);
        void force_put(const std::string& name, std::shared_ptr<AbstractFunctionFactory> function);
        void put_cmath();
        void put_onerut_functions();
    private:
        // helper functions:
        template<unsigned nary, typename CallableReal, typename CallableComplex>
        void put_nary_scalar_function_factory(
                std::string onerut_name,
                CallableReal callable_real,
                CallableComplex callable_complex);
        // the container:        
        std::map<std::string, std::shared_ptr<AbstractFunctionFactory>> functions;
    };

}

#endif
