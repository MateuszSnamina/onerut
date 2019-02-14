#include<cmath>
#include<complex>
#include<onerut_parser/function_global.hpp>
#include<onerut_parser/function_scalar_function_wrapper.hpp>

// *****************************************************************************
// *************   Macros that help to add real functions   ********************
// *****************************************************************************
#define CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(ONERUT_NAME, CPPSTD_NAME)           \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared<                                                          \
      UnaryRealComplexFunction<UnaryRealFunPtrT, std::nullptr_t>               \
    >(                                                                         \
      static_cast<UnaryRealFunPtrT> (&std::CPPSTD_NAME),                       \
      nullptr                                                                  \
    )                                                                          \
  )

#define PUT_STD_UNARY_REAL_FUNCTION(NAME)                                      \
  CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(NAME, NAME)

// -----------

#define CUSTOM_PUT_STD_UNARY_COMPLEX_RETURNS_REAL_FUNCTION(ONERUT_NAME, CPPSTD_NAME) \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared<                                                          \
      UnaryRealComplexFunction<std::nullptr_t, UnaryComplexReturnsRealFunPtrT >\
    >(                                                                         \
      nullptr,                                                                 \
      static_cast<UnaryComplexReturnsRealFunPtrT> (&std::CPPSTD_NAME)          \
    )                                                                          \
  )

#define PUT_STD_UNARY_COMPLEX_RETURNS_REAL_FUNCTION(NAME)                      \
  CUSTOM_PUT_STD_UNARY_COMPLEX_RETURNS_REAL_FUNCTION(NAME, NAME)

// -----------

#define CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(ONERUT_NAME, CPPSTD_NAME)          \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared<                                                          \
      BinaryRealFunction<BinaryRealFunPtrT>                                    \
    >(                                                                         \
      static_cast<BinaryRealFunPtrT> (&std::CPPSTD_NAME)                       \
    )                                                                          \
  )

#define PUT_STD_BINARY_REAL_FUNCTION(NAME)                                     \
  CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(NAME, NAME)

// *****************************************************************************
// *************   Macros that help to add complex functions   *****************
// *****************************************************************************
#define CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME)        \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared <                                                         \
      UnaryRealComplexFunction<std::nullptr_t, UnaryComplexFunPtrT>            \
    >(                                                                         \
      nullptr,                                                                 \
      static_cast<UnaryComplexFunPtrT> (&std::CPPSTD_NAME)                     \
     )                                                                         \
  )

#define PUT_STD_UNARY_COMPLEX_FUNCTION(NAME)                                   \
  CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(NAME, NAME)

#define CUSTOM_PUT_STD_BINARY_COMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME)       \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared<                                                          \
      BinaryComplexFunction<BinaryComplexFunPtrT>                              \
    >(                                                                         \
      static_cast<BinaryComplexFunPtrT> (&std::CPPSTD_NAME)                    \
    )                                                                          \
  )

#define PUT_STD_BINARY_COMPLEX_FUNCTION(NAME)                                  \
  CUSTOM_PUT_STD_BINARY_COMPLEX_FUNCTION(NAME, NAME)

// *****************************************************************************
// *************   Macros that help overload real-complex functions   **********
// *****************************************************************************
#define CUSTOM_PUT_STD_UNARY_REALCOMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME)    \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared<                                                          \
      UnaryRealComplexFunction<UnaryRealFunPtrT, UnaryComplexFunPtrT>          \
    >(                                                                         \
      static_cast<UnaryRealFunPtrT> (&std::CPPSTD_NAME),                       \
      static_cast<UnaryComplexFunPtrT> (&std::CPPSTD_NAME)                     \
    )                                                                          \
  )

#define PUT_STD_UNARY_REALCOMPLEX_FUNCTION(NAME)                               \
  CUSTOM_PUT_STD_UNARY_REALCOMPLEX_FUNCTION(NAME, NAME)

#define CUSTOM_PUT_STD_BINARY_REALCOMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME)   \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared<                                                          \
      BinaryRealComplexFunction<BinaryRealFunPtrT, BinaryComplexFunPtrT >      \
    >(                                                                         \
      static_cast<BinaryRealFunPtrT> (&std::CPPSTD_NAME),                      \
      static_cast<BinaryComplexFunPtrT> (&std::CPPSTD_NAME)                    \
    )                                                                          \
  )

#define PUT_STD_BINARY_REALCOMPLEX_FUNCTION(NAME)                              \
  CUSTOM_PUT_STD_BINARY_REALCOMPLEX_FUNCTION(NAME, NAME)

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
        using cx_double = std::complex<double>;
        using UnaryComplexFunPtrT = cx_double(*)(const cx_double&);
        using UnaryComplexReturnsRealFunPtrT = double(*)(const cx_double&);
        using BinaryComplexFunPtrT = cx_double(*)(const cx_double&, const cx_double&);
        // ******************************************************
        // **** Functions for both real and complex numbers: ****
        // ******************************************************
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_cos, cos);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_cos, cos);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(cos);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_sin, sin);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sin, sin);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sin);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_tan, tan);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_tan, tan);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(tan);
        // ------------------------------------------------------
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_acos, acos);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_acos, acos);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(acos);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_asin, asin);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_asin, asin);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(asin);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_atan, atan);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_atan, atan);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(atan);
        // ------------------------------------------------------
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_cosh, cosh);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_cosh, cosh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(cosh);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_sinh, sinh);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sinh, sinh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sinh);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_tanh, tanh);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_tanh, tanh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(tanh);
        // ------------------------------------------------------
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_acosh, acosh);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_acosh, acosh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(acosh);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_asinh, asinh);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_asinh, asinh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(asinh);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_atanh, atanh);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_atanh, atanh);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(atanh);
        // ------------------------------------------------------        
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_exp, exp);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_exp, exp);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(exp);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_log, log);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_log, log);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(log);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_log10, log10);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_log10, log10);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(log10);
        // ------------------------------------------------------
        CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(re_pow, pow);
        CUSTOM_PUT_STD_BINARY_COMPLEX_FUNCTION(cx_pow, pow);
        PUT_STD_BINARY_REALCOMPLEX_FUNCTION(pow);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_sqrt, sqrt);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sqrt, sqrt);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sqrt);
        // ******************************************************
        // ****  Functions for real numbers: ********************
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
        CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(dim, fdim);
        CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(max, fmax);
        CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(min, fmin);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_abs, fabs);
        // ******************************************************
        // **** Functions for complex numbers *******************
        // ******************************************************
        PUT_STD_UNARY_COMPLEX_FUNCTION(conj);
        PUT_STD_UNARY_COMPLEX_RETURNS_REAL_FUNCTION(real);
        PUT_STD_UNARY_COMPLEX_RETURNS_REAL_FUNCTION(imag);
        PUT_STD_UNARY_COMPLEX_RETURNS_REAL_FUNCTION(arg);
        PUT_STD_UNARY_COMPLEX_RETURNS_REAL_FUNCTION(norm);
        CUSTOM_PUT_STD_UNARY_COMPLEX_RETURNS_REAL_FUNCTION(cx_abs, abs);
    }
}


