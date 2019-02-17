#include<onerut_parser/identifier_global.hpp>

namespace onerut_parser {

    // #########################################################################
    // #################### SOME CONSTANTS  ####################################
    // #########################################################################

    const double pi = 3.14159265358979323846;
    const double e = 2.71828182845904523536;

    // #########################################################################
    // #################### GLOBAL DATABASE ####################################
    // #########################################################################

    GlobalIdentifiers& GlobalIdentifiers::instance() {
        static GlobalIdentifiers _instance;
        return _instance;
    }

    std::optional<std::shared_ptr<AbstractCompileResultRef>> GlobalIdentifiers::get_or_empty(const std::string& name) const {
        try {
            return identifiers.at(name);
        } catch (std::out_of_range&) {
            return std::optional<std::shared_ptr < AbstractCompileResultRef >> ();
        }
    }

    bool GlobalIdentifiers::put(const std::string& name, std::shared_ptr<AbstractCompileResultRef> holder) {
        if (identifiers.count(name))
            return false;
        identifiers[name] = holder;
        return true;
    }

    void GlobalIdentifiers::force_put(const std::string& name, std::shared_ptr<AbstractCompileResultRef> holder) {
        identifiers[name] = holder;
    }

}