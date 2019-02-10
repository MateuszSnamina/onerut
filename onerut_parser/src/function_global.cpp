#include<cmath>
#include<complex>
#include<onerut_parser/function_global.hpp>
#include<onerut_scalar/function_real.hpp>//TODO remove
#include<onerut_scalar/function_complex.hpp>//TODO remove

// *************************************************************************************************************
// For real functions:
// *************************************************************************************************************
#define FULL_CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(TYPE, ONERUT_NAME, CPPSTD_NAME) \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared <UnaryRealFunction < TYPE >> (                            \
      static_cast<TYPE> (&std::CPPSTD_NAME)                                    \
  ))

#define CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(ONERUT_NAME, CPPSTD_NAME) \
  FULL_CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(UnaryRealFunPtrT, ONERUT_NAME, CPPSTD_NAME)

#define PUT_STD_UNARY_REAL_FUNCTION(NAME) \
  CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(NAME, NAME)

#define FULL_CUSTOMIZED_PUT_STD_BINARY_REAL_FUNCTION(TYPE, ONERUT_NAME, CPPSTD_NAME) \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared <BinaryRealFunction < TYPE >> (                           \
            static_cast<TYPE> (&std::CPPSTD_NAME)                              \
  ))

#define CUSTOMIZED_PUT_STD_BINARY_REAL_FUNCTION(ONERUT_NAME, CPPSTD_NAME) \
  FULL_CUSTOMIZED_PUT_STD_BINARY_REAL_FUNCTION(BinaryRealFunPtrT, ONERUT_NAME, CPPSTD_NAME)

#define PUT_STD_BINARY_REAL_FUNCTION(NAME) \
  CUSTOMIZED_PUT_STD_BINARY_REAL_FUNCTION(NAME, NAME)

// *************************************************************************************************************
// For complex functions:
// *************************************************************************************************************
#define FULL_CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(TYPE, ONERUT_NAME, CPPSTD_NAME) \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared <UnaryComplexFunction < TYPE >> (                         \
      static_cast<TYPE> (&std::CPPSTD_NAME)                                    \
  ))

#define CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME)    \
  FULL_CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(UnaryComplexFunPtrT, ONERUT_NAME, CPPSTD_NAME)

#define PUT_STD_UNARY_COMPLEX_FUNCTION(NAME) \
  CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(NAME, NAME)

#define FULL_CUSTOMIZED_PUT_STD_BINARY_COMPLEX_FUNCTION(TYPE, ONERUT_NAME, CPPSTD_NAME) \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared <BinaryComplexFunction < TYPE >> (                        \
      static_cast<TYPE> (&std::CPPSTD_NAME)                                    \
 ))

#define CUSTOMIZED_PUT_STD_BINARY_COMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME) \
  FULL_CUSTOMIZED_PUT_STD_BINARY_COMPLEX_FUNCTION(BinaryComplexFunPtrT, ONERUT_NAME, CPPSTD_NAME)

#define PUT_STD_BINARY_COMPLEX_FUNCTION(NAME) \
  CUSTOMIZED_PUT_STD_BINARY_COMPLEX_FUNCTION(NAME, NAME)

// *************************************************************************************************************
// For overload real-complex functions:
// *************************************************************************************************************
#define FULL_CUSTOMIZED_PUT_STD_UNARY_REALCOMPLEX_FUNCTION(TYPE_REAL, TYPE_COMPLEX, ONERUT_NAME, CPPSTD_NAME) \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared <UnaryRealComplexFunction < TYPE_REAL, TYPE_COMPLEX >> (  \
      static_cast<TYPE_REAL> (&std::CPPSTD_NAME),                              \
      static_cast<TYPE_COMPLEX> (&std::CPPSTD_NAME)                            \
  ))

#define CUSTOMIZED_PUT_STD_UNARY_REALCOMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME) \
  FULL_CUSTOMIZED_PUT_STD_UNARY_REALCOMPLEX_FUNCTION(UnaryRealFunPtrT, UnaryComplexFunPtrT, ONERUT_NAME, CPPSTD_NAME)

#define PUT_STD_UNARY_REALCOMPLEX_FUNCTION(NAME) \
  CUSTOMIZED_PUT_STD_UNARY_REALCOMPLEX_FUNCTION(NAME, NAME)

#define FULL_CUSTOMIZED_PUT_STD_BINARY_REALCOMPLEX_FUNCTION(TYPE_REAL, TYPE_COMPLEX, ONERUT_NAME, CPPSTD_NAME) \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared <BinaryRealComplexFunction < TYPE_REAL, TYPE_COMPLEX >> ( \
      static_cast<TYPE_REAL> (&std::CPPSTD_NAME),                              \
      static_cast<TYPE_COMPLEX> (&std::CPPSTD_NAME)                            \
  ))

#define CUSTOMIZED_PUT_STD_BINARY_REALCOMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME) \
  FULL_CUSTOMIZED_PUT_STD_BINARY_REALCOMPLEX_FUNCTION(BinaryRealFunPtrT, BinaryComplexFunPtrT, ONERUT_NAME, CPPSTD_NAME)

#define PUT_STD_BINARY_REALCOMPLEX_FUNCTION(NAME) \
  CUSTOMIZED_PUT_STD_BINARY_REALCOMPLEX_FUNCTION(NAME, NAME)


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
        using UnaryRealFunPtrT = double(*)(double);
        using BinaryRealFunPtrT = double(*)(double, double);
        using cx_couble = std::complex<double>;
        using UnaryComplexFunPtrT = cx_couble(*)(const cx_couble&);
        using BinaryComplexFunPtrT = cx_couble(*)(const cx_couble&, const cx_couble&);
        // ******************************************************
        // Functions for real and complex numbers:
        // ******************************************************
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_cos, cos);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_cos, cos);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(cos);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_sin, sin);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sin, sin);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sin);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_tan, tan);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_tan, tan);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(tan);
        // ------------------------------------------------------
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_acos, acos);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_acos, acos);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(acos);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_asin, asin);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_asin, asin);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(asin);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_atan, atan);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_atan, atan);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(atan);
        // ------------------------------------------------------
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_cosh, cosh);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_cosh, cosh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(cosh);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_sinh, sinh);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sinh, sinh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sinh);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_tanh, tanh);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_tanh, tanh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(tanh);
        // ------------------------------------------------------
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_acosh, acosh);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_acosh, acosh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(acosh);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_asinh, asinh);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_asinh, asinh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(asinh);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_atanh, atanh);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_atanh, atanh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(atanh);
        // ------------------------------------------------------        
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_exp, exp);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_exp, exp);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(exp);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_log, log);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_log, log);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(log);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_log10, log10);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_log10, log10);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(log10);
        // ------------------------------------------------------
        CUSTOMIZED_PUT_STD_BINARY_REAL_FUNCTION(re_pow, pow);
        CUSTOMIZED_PUT_STD_BINARY_COMPLEX_FUNCTION(cx_pow, pow);
        PUT_STD_BINARY_REALCOMPLEX_FUNCTION(pow);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(re_sqrt, sqrt);
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sqrt, sqrt);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sqrt);
        // ******************************************************
        // Functions for real numbers:
        // ******************************************************
        PUT_STD_BINARY_REAL_FUNCTION(atan2);
        PUT_STD_UNARY_REAL_FUNCTION(exp2);
        PUT_STD_UNARY_REAL_FUNCTION(expm1);
        PUT_STD_UNARY_REAL_FUNCTION(log1p);
        PUT_STD_UNARY_REAL_FUNCTION(log2);
        PUT_STD_UNARY_REAL_FUNCTION(cbrt);
        PUT_STD_BINARY_REAL_FUNCTION(hypot);
        PUT_STD_UNARY_REAL_FUNCTION(erf);
        PUT_STD_UNARY_REAL_FUNCTION(erfc);
        PUT_STD_UNARY_REAL_FUNCTION(tgamma);
        PUT_STD_UNARY_REAL_FUNCTION(lgamma);
        PUT_STD_UNARY_REAL_FUNCTION(ceil);
        PUT_STD_UNARY_REAL_FUNCTION(floor);
        PUT_STD_BINARY_REAL_FUNCTION(fmod);
        PUT_STD_UNARY_REAL_FUNCTION(trunc);
        PUT_STD_UNARY_REAL_FUNCTION(round);
        PUT_STD_BINARY_REAL_FUNCTION(remainder);
        PUT_STD_BINARY_REAL_FUNCTION(copysign);
        CUSTOMIZED_PUT_STD_BINARY_REAL_FUNCTION(dim, fdim);
        CUSTOMIZED_PUT_STD_BINARY_REAL_FUNCTION(max, fmax);
        CUSTOMIZED_PUT_STD_BINARY_REAL_FUNCTION(min, fmin);
        CUSTOMIZED_PUT_STD_UNARY_REAL_FUNCTION(abs, fabs);
        // ******************************************************
        // Functions for complex numbers:
        // ******************************************************
        CUSTOMIZED_PUT_STD_UNARY_COMPLEX_FUNCTION(conj, conj);
        // real
        // imag
        // abs
        // arg
        // norm
        // polar


    }
}


