#include<onerut_parser/function_global.hpp>
#include<cmath> // TODO in future: move this header to the place where functions will be created.
#include<onerut_scalar/scalar.hpp>// TODO in future: move this header to the place where functions will be created.
namespace onerut_parser {

    // #########################################################################
    // #################### GLOBAL DATABASE ####################################
    // #########################################################################

    GlobalFunctions& GlobalFunctions::instance() {
        static GlobalFunctions _instance;
        return _instance;
    }

    std::optional<std::shared_ptr<AbstractFunction>> GlobalFunctions::get_or_empty(const std::u32string& name) const {
        try {
            return functions.at(name);
        } catch (std::out_of_range&) {
            return std::optional<std::shared_ptr < AbstractFunction >> ();
        }
    }

    bool GlobalFunctions::put(const std::u32string& name, std::shared_ptr<AbstractFunction> function) {
        if (functions.count(name))
            return false;
        functions[name] = function;
        return true;
    }

    void GlobalFunctions::force_put(const std::u32string& name, std::shared_ptr<AbstractFunction> function) {
        functions[name] = function;
    }

    bool GlobalFunctions::put_sqrt() {
        using FunPtrType = double(*)(double);
        std::shared_ptr<AbstractFunction> function = std::make_shared <UnaryDoubleFunction < FunPtrType >> (static_cast<FunPtrType> (&std::sqrt));
        return put(U"sqrt", function);
    }

    bool GlobalFunctions::put_pow() {
        using FunPtrType = double(*)(double, double);
        std::shared_ptr<AbstractFunction> function = std::make_shared <BinaryDoubleFunction < FunPtrType >> (static_cast<FunPtrType> (&std::pow));
        return put(U"pow", function);
    }
}