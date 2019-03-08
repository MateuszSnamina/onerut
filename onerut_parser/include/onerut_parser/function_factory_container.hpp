#ifndef ONERUT_PARSER_FUNCTION_FACTORY_CONTAINER
#define ONERUT_PARSER_FUNCTION_FACTORY_CONTAINER

#include<optional>
#include<string>
#include<map>
#include<onerut_parser/function_factory_abstract.hpp>

namespace onerut_parser {

    class FunctionFactoryContainer {
    public:
        static FunctionFactoryContainer& global_instance();
        std::optional<std::shared_ptr<AbstractFunctionFactory>> get_or_empty(const std::string& name) const;
        bool put(const std::string& name, std::shared_ptr<AbstractFunctionFactory> function);
        void force_put(const std::string& name, std::shared_ptr<AbstractFunctionFactory> function);
        void put_cmath();
        void put_onerut_functions();
        void put_imparative_request_functions();
        void put_all();
        void clear();
    private:
        std::map<std::string, std::shared_ptr<AbstractFunctionFactory>> functions;
    };

}

#endif
