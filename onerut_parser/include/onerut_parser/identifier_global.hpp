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
        bool put(const std::string& name, std::shared_ptr<AbstractCompileResultRef> ref);  //TODO: delete name from a signature, read name from ref object through its std::string get_name() const method
        void force_put(const std::string& name, std::shared_ptr<AbstractCompileResultRef> ref);  //TODO: delete name from a signature, read name from ref object through its std::string get_name() const method
    private:
        std::map<std::string, std::shared_ptr<AbstractCompileResultRef>> identifiers;
    };

}

#endif
