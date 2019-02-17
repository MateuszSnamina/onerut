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
        std::optional<std::shared_ptr<AbstractCompileResultRef>> get_or_empty(const std::string& name) const;
        bool put(const std::string& name, std::shared_ptr<AbstractCompileResultRef> holder);
        void force_put(const std::string& name, std::shared_ptr<AbstractCompileResultRef> holder);
    private:
        std::map<std::string, std::shared_ptr<AbstractCompileResultRef>> identifiers;
    };

}

#endif
