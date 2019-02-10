#ifndef ONERUT_PARSER_FUNCTION_GLOBAL
#define ONERUT_PARSER_FUNCTION_GLOBAL


#include<optional>
#include<string>
#include<map>
#include<onerut_parser/function_abstract.hpp>

namespace onerut_parser {

    class GlobalFunctions {
    public:
        static GlobalFunctions& instance();
        std::optional<std::shared_ptr<AbstractFunction>> get_or_empty(const std::string& name) const;
        bool put(const std::string& name, std::shared_ptr<AbstractFunction> function);
        void force_put(const std::string& name, std::shared_ptr<AbstractFunction> function);
        void put_cmath();
    private:
        std::map<std::string, std::shared_ptr<AbstractFunction>> functions;
    };

}

#endif
