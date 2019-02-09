#include<cmath>
#include<onerut_parser/function_global.hpp>
#include<onerut_scalar/scalar.hpp>

#define FULL_CUSTOMIZED_PUT_STD_UNARY_FUNCTION(TYPE, ONERUT_NAME, CPPSTD_NAME) force_put(#ONERUT_NAME, std::make_shared <UnaryRealFunction < TYPE >> (static_cast<TYPE> (&std::CPPSTD_NAME)))
#define CUSTOMIZED_PUT_STD_UNARY_FUNCTION(ONERUT_NAME, CPPSTD_NAME) FULL_CUSTOMIZED_PUT_STD_UNARY_FUNCTION(FunPtrType1, ONERUT_NAME, CPPSTD_NAME)
#define PUT_STD_UNARY_FUNCTION(NAME) CUSTOMIZED_PUT_STD_UNARY_FUNCTION(NAME, NAME)

#define FULL_CUSTOMIZED_PUT_STD_BINARY_FUNCTION(TYPE, ONERUT_NAME, CPPSTD_NAME) force_put(#ONERUT_NAME, std::make_shared <BinaryRealFunction < TYPE >> (static_cast<TYPE> (&std::CPPSTD_NAME)))
#define CUSTOMIZED_PUT_STD_BINARY_FUNCTION(ONERUT_NAME, CPPSTD_NAME) FULL_CUSTOMIZED_PUT_STD_BINARY_FUNCTION(FunPtrType2, ONERUT_NAME, CPPSTD_NAME)
#define PUT_STD_BINARY_FUNCTION(NAME) CUSTOMIZED_PUT_STD_BINARY_FUNCTION(NAME, NAME)

namespace onerut_parser {

    // #########################################################################
    // #################### GLOBAL DATABASE ####################################
    // #########################################################################

    GlobalFunctions& GlobalFunctions::instance() {
        static GlobalFunctions _instance;
        return _instance;
    }

    std::optional<std::shared_ptr<AbstractFunction>> GlobalFunctions::get_or_empty(const std::string& name) const {
        try {
            return functions.at(name);
        } catch (std::out_of_range&) {
            return std::optional<std::shared_ptr < AbstractFunction >> ();
        }
    }

    bool GlobalFunctions::put(const std::string& name, std::shared_ptr<AbstractFunction> function) {
        if (functions.count(name))
            return false;
        functions[name] = function;
        return true;
    }

    void GlobalFunctions::force_put(const std::string& name, std::shared_ptr<AbstractFunction> function) {
        functions[name] = function;
    }

    void GlobalFunctions::put_cmath() {
        using FunPtrType1 = double(*)(double);
        using FunPtrType2 = double(*)(double, double);
        PUT_STD_UNARY_FUNCTION(cos);
        PUT_STD_UNARY_FUNCTION(sin);
        PUT_STD_UNARY_FUNCTION(tan);
        PUT_STD_UNARY_FUNCTION(acos);
        PUT_STD_UNARY_FUNCTION(asin);
        PUT_STD_UNARY_FUNCTION(atan);
        PUT_STD_BINARY_FUNCTION(atan2);
        PUT_STD_UNARY_FUNCTION(cosh);
        PUT_STD_UNARY_FUNCTION(sinh);
        PUT_STD_UNARY_FUNCTION(tanh);
        PUT_STD_UNARY_FUNCTION(acosh);
        PUT_STD_UNARY_FUNCTION(asinh);
        PUT_STD_UNARY_FUNCTION(atanh);
        PUT_STD_UNARY_FUNCTION(exp);
        PUT_STD_UNARY_FUNCTION(log);
        PUT_STD_UNARY_FUNCTION(log10);
        PUT_STD_UNARY_FUNCTION(exp2);
        PUT_STD_UNARY_FUNCTION(expm1);
        PUT_STD_UNARY_FUNCTION(log1p);
        PUT_STD_UNARY_FUNCTION(log2);
        PUT_STD_BINARY_FUNCTION(pow);
        PUT_STD_UNARY_FUNCTION(sqrt);
        PUT_STD_UNARY_FUNCTION(cbrt);
        PUT_STD_BINARY_FUNCTION(hypot);
        PUT_STD_UNARY_FUNCTION(erf);
        PUT_STD_UNARY_FUNCTION(erfc);
        PUT_STD_UNARY_FUNCTION(tgamma);
        PUT_STD_UNARY_FUNCTION(lgamma);
        PUT_STD_UNARY_FUNCTION(ceil);
        PUT_STD_UNARY_FUNCTION(floor);
        PUT_STD_BINARY_FUNCTION(fmod);
        PUT_STD_UNARY_FUNCTION(trunc);
        PUT_STD_UNARY_FUNCTION(round);
        PUT_STD_BINARY_FUNCTION(remainder);
        PUT_STD_BINARY_FUNCTION(copysign);
        CUSTOMIZED_PUT_STD_BINARY_FUNCTION(dim, fdim);
        CUSTOMIZED_PUT_STD_BINARY_FUNCTION(max, fmax);
        CUSTOMIZED_PUT_STD_BINARY_FUNCTION(min, fmin);
        CUSTOMIZED_PUT_STD_UNARY_FUNCTION(abs, fabs);
    }
}

