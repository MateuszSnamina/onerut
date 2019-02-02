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

    std::optional<std::shared_ptr<AbstractCompileResultHolder>> GlobalIdentifiers::get_or_empty(const std::u32string& name) const {
        try {
            return identifiers.at(name);
        } catch (std::out_of_range&) {
            return std::optional<std::shared_ptr < AbstractCompileResultHolder >> ();
        }
    }

    bool GlobalIdentifiers::put(const std::u32string& name, std::shared_ptr<AbstractCompileResultHolder> builder) {
        if (identifiers.count(name))
            return false;
        identifiers[name] = builder;
        return true;
    }

    bool GlobalIdentifiers::put_e() {
        const auto e_holder = std::make_shared<ConstDoubleHolder>(e);
        return GlobalIdentifiers::instance().put(U"e", e_holder);
    }

    bool GlobalIdentifiers::put_pi() {
        const auto pi_holder = std::make_shared<ConstDoubleHolder>(pi);
        return GlobalIdentifiers::instance().put(U"pi", pi_holder);
    }

}