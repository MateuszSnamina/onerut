#ifndef ONERUT_PARSER_FUNCTION_GLOBAL
#define ONERUT_PARSER_FUNCTION_GLOBAL


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
    private:
        std::map<std::string, std::shared_ptr<AbstractFunctionFactory>> functions;
    };

}

#endif
