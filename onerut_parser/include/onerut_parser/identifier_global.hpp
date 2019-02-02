#ifndef ONERUT_PARSER_IDENTIFIER_GLOBAL
#define ONERUT_PARSER_IDENTIFIER_GLOBAL

#include<optional>
#include<string>
#include<map>
#include<onerut_parser/identifier.hpp>

namespace onerut_parser {

    class GlobalIdentifiers {
    public:
        static GlobalIdentifiers& instance();
        std::optional<std::shared_ptr<AbstractCompileResultHolder>> get_or_empty(const std::u32string& name) const;
        bool put(const std::u32string& name, std::shared_ptr<AbstractCompileResultHolder> holder);
        void force_put(const std::u32string& name, std::shared_ptr<AbstractCompileResultHolder> holder);
        bool put_e();
        bool put_pi();
    private:
        std::map<std::u32string, std::shared_ptr<AbstractCompileResultHolder>> identifiers;
    };

}

#endif
