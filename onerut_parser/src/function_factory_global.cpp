#include<cmath>
#include<complex>
#include<onerut_parser/function_factory_global.hpp>
#include<onerut_parser/function_factory_scalar.hpp>


// *****************************************************************************
// *************   New Macros that help to add real functions   ****************
// *****************************************************************************

#define NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(ONERUT_NAME, CPPSTD_NAME, RETURN_TYPE)    \
  put_unary_real_function_factory(                                             \
    #ONERUT_NAME,                                                              \
    static_cast<RETURN_TYPE(*)(double)> (&std::CPPSTD_NAME)                    \
  );

#define NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(NAME, RETURN_TYPE)    \
  NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(NAME, NAME, RETURN_TYPE)

//-----------------------------------

#define NEEEEW_CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(ONERUT_NAME, CPPSTD_NAME, RETURN_TYPE)    \
  put_binary_real_function_factory(                                                 \
    #ONERUT_NAME,                                                              \
    static_cast<RETURN_TYPE(*)(double, double)> (&std::CPPSTD_NAME)            \
  );

#define NEEEEW_PUT_STD_BINARY_REAL_FUNCTION(NAME, RETURN_TYPE)                 \
  NEEEEW_CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(NAME, NAME, RETURN_TYPE)

/////////////////////////////////////////////////////////////////////////////////

#define NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME, RETURN_TYPE)    \
  put_unary_complex_function_factory(                                                   \
    #ONERUT_NAME,                                                              \
    static_cast<RETURN_TYPE(*)(const cx_double&)> (&std::CPPSTD_NAME)                    \
  );

#define NEEEEW_PUT_STD_UNARY_COMPLEX_FUNCTION(NAME, RETURN_TYPE)    \
  NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(NAME, NAME, RETURN_TYPE)

//-----------------------------------

#define NEEEEW_CUSTOM_PUT_STD_BINARY_COMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME, RETURN_TYPE)    \
  put_binary_complex_function_factory(                                                   \
    #ONERUT_NAME,                                                              \
    static_cast<RETURN_TYPE(*)(const cx_double&, const cx_double&)> (&std::CPPSTD_NAME)            \
  );

#define NEEEEW_PUT_STD_BINARY_COMPLEX_FUNCTION(NAME, RETURN_TYPE)                 \
  NEEEEW_CUSTOM_PUT_STD_BINARY_COMPLEX_FUNCTION(NAME, NAME, RETURN_TYPE)




// *****************************************************************************
// *************   Macros that help to add real functions   ********************
// *****************************************************************************
#define CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(ONERUT_NAME, CPPSTD_NAME)           \
  force_put(                                                                   \
    #ONERUT_NAME,                                                              \
    std::make_shared<                                                          \
      OverloadScalarUnaryFunctionFactory<UnaryRealFunPtrT, std::nullptr_t>               \
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
      OverloadScalarUnaryFunctionFactory<std::nullptr_t, UnaryComplexReturnsRealFunPtrT >\
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
      OverloadScalarBinaryFunctionFactory<BinaryRealFunPtrT, std::nullptr_t>   \
    >(                                                                         \
      static_cast<BinaryRealFunPtrT> (&std::CPPSTD_NAME),                      \
      nullptr                                                                  \
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
      OverloadScalarUnaryFunctionFactory<std::nullptr_t, UnaryComplexFunPtrT>            \
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
      OverloadScalarBinaryFunctionFactory<nullptr_t, BinaryComplexFunPtrT>     \
    >(                                                                         \
      nullptr,                                                                 \
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
      OverloadScalarUnaryFunctionFactory<UnaryRealFunPtrT, UnaryComplexFunPtrT>          \
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
      OverloadScalarBinaryFunctionFactory<BinaryRealFunPtrT, BinaryComplexFunPtrT >      \
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

    GlobalFunctionFactories& GlobalFunctionFactories::instance() {
        static GlobalFunctionFactories _instance;

        return _instance;
    }

    std::optional<std::shared_ptr<AbstractFunctionFactory>> GlobalFunctionFactories::get_or_empty(const std::string& name) const {
        try {
            return functions.at(name);
        } catch (std::out_of_range&) {

            return std::optional<std::shared_ptr < AbstractFunctionFactory >> ();
        }
    }

    bool GlobalFunctionFactories::put(const std::string& name, std::shared_ptr<AbstractFunctionFactory> function) {
        if (functions.count(name))
            return false;
        functions[name] = function;

        return true;
    }

    void GlobalFunctionFactories::force_put(const std::string& name, std::shared_ptr<AbstractFunctionFactory> function) {

        functions[name] = function;
    }

    void GlobalFunctionFactories::put_cmath() {
        using UnaryRealFunPtrT = double(*)(double);
        using BinaryRealFunPtrT = double(*)(double, double);
        using cx_double = std::complex<double>;
        using UnaryComplexFunPtrT = cx_double(*)(const cx_double&);
        //using UnaryComplexReturnsRealFunPtrT = double(*)(const cx_double&);
        using BinaryComplexFunPtrT = cx_double(*)(const cx_double&, const cx_double&);
        // ******************************************************
        // **** Functions for both real and complex numbers: ****
        // ******************************************************

        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_cos, cos, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_cos, cos, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(cos);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_sin, sin, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sin, sin, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sin);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_tan, tan, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_tan, tan, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(tan);
        // ------------------------------------------------------
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_acos, acos, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_acos, acos, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(acos);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_asin, asin, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_asin, asin, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(asin);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_atan, atan, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_atan, atan, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(atan);
        // ------------------------------------------------------
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_cosh, cosh, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_cosh, cosh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(cosh);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_sinh, sinh, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sinh, sinh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sinh);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_tanh, tanh, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_tanh, tanh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(tanh);
        // ------------------------------------------------------
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_acosh, acosh, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_acosh, acosh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(acosh);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_asinh, asinh, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_asinh, asinh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(asinh);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_atanh, atanh, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_atanh, atanh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(atanh);
        // ------------------------------------------------------        
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_exp, exp, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_exp, exp, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(exp);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_log, log, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_log, log, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(log);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_log10, log10, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_log10, log10, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(log10);
        // ------------------------------------------------------
        NEEEEW_CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(re_pow, pow, double);
        NEEEEW_CUSTOM_PUT_STD_BINARY_COMPLEX_FUNCTION(cx_pow, pow, cx_double);
        PUT_STD_BINARY_REALCOMPLEX_FUNCTION(pow);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_sqrt, sqrt, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sqrt, sqrt, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sqrt);
        // ******************************************************
        // ****  Functions for real numbers: ********************
        // ******************************************************
        NEEEEW_PUT_STD_BINARY_REAL_FUNCTION(atan2, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(exp2, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(expm1, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(log1p, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(log2, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(cbrt, double);
        NEEEEW_PUT_STD_BINARY_REAL_FUNCTION(hypot, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(erf, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(erfc, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(tgamma, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(lgamma, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(ceil, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(floor, double);
        NEEEEW_PUT_STD_BINARY_REAL_FUNCTION(fmod, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(trunc, double);
        NEEEEW_PUT_STD_UNARY_REAL_FUNCTION(round, double);
        NEEEEW_PUT_STD_BINARY_REAL_FUNCTION(remainder, double);
        NEEEEW_PUT_STD_BINARY_REAL_FUNCTION(copysign, double);
        NEEEEW_CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(dim, fdim, double);
        NEEEEW_CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(max, fmax, double);
        NEEEEW_CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(min, fmin, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_abs, fabs, double);
        // ******************************************************
        // **** Functions for complex numbers *******************
        // ******************************************************
        NEEEEW_PUT_STD_UNARY_COMPLEX_FUNCTION(conj, cx_double);
        NEEEEW_PUT_STD_UNARY_COMPLEX_FUNCTION(real, double);
        NEEEEW_PUT_STD_UNARY_COMPLEX_FUNCTION(imag, double);
        NEEEEW_PUT_STD_UNARY_COMPLEX_FUNCTION(arg, double);
        NEEEEW_PUT_STD_UNARY_COMPLEX_FUNCTION(norm, double);
        NEEEEW_CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_abs, abs, double);
    }
}


