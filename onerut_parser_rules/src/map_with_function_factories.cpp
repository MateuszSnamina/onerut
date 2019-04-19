#include<cmath>
#include<complex>

#include<onerut_parser_rules/function_factory_constant.hpp>
#include<onerut_parser_rules/function_factory_scalar.hpp>
#include<onerut_parser_rules/function_factory_normal_operators.hpp>
#include<onerut_parser_rules/function_factory_imperative_request.hpp>
#include<onerut_parser_rules/function_factory_print_value_request.hpp>
#include<onerut_parser_rules/map_with_function_factories.hpp>

using cx_double = std::complex<double>;
using namespace std::complex_literals;
const double pi = 3.14159265358979323846;
const double e = 2.71828182845904523536;

// *****************************************************************************
// *************   New Macros that help to add real functions   ****************
// *****************************************************************************

#define UNIVERSAL_PUT(NARY, ONERUT_NAME, CALLABLE_REAL, CALLABLE_COMPLEX) \
    force_put( \
        #ONERUT_NAME, \
        std::make_unique< \
        OverloadScalarFunctionFactory<NARY, decltype(CALLABLE_REAL), decltype(CALLABLE_COMPLEX)> \
        >(CALLABLE_REAL, CALLABLE_COMPLEX) \
    );

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#define CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(ONERUT_NAME, CPPSTD_NAME, RETURN_TYPE) \
    UNIVERSAL_PUT(                                                             \
        1,                                                                     \
        ONERUT_NAME,                                                           \
        static_cast<RETURN_TYPE(*)(double)>(&std::CPPSTD_NAME),                \
        nullptr                                                                \
    )

#define PUT_STD_UNARY_REAL_FUNCTION(NAME, RETURN_TYPE) \
  CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(NAME, NAME, RETURN_TYPE)

//------------------------------------------------------------------------------

#define CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(ONERUT_NAME, CPPSTD_NAME, RETURN_TYPE) \
    UNIVERSAL_PUT(                                                             \
        2,                                                                     \
        ONERUT_NAME,                                                           \
        static_cast<RETURN_TYPE(*)(double, double)>(&std::CPPSTD_NAME),        \
        nullptr                                                                \
    )

#define PUT_STD_BINARY_REAL_FUNCTION(NAME, RETURN_TYPE) \
  CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(NAME, NAME, RETURN_TYPE)

//******************************************************************************

#define CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME, RETURN_TYPE) \
    UNIVERSAL_PUT(                                                             \
        1,                                                                     \
        ONERUT_NAME,                                                           \
        nullptr,                                                               \
        static_cast<RETURN_TYPE(*)(const cx_double&)>(&std::CPPSTD_NAME)       \
    )

#define PUT_STD_UNARY_COMPLEX_FUNCTION(NAME, RETURN_TYPE) \
  CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(NAME, NAME, RETURN_TYPE)

//------------------------------------------------------------------------------

#define CUSTOM_PUT_STD_BINARY_COMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME, RETURN_TYPE) \
    UNIVERSAL_PUT(                                                             \
        2,                                                                     \
        ONERUT_NAME,                                                           \
        nullptr,                                                               \
        static_cast<RETURN_TYPE(*)(const cx_double&, const cx_double&)>(&std::CPPSTD_NAME) \
    )

#define PUT_STD_BINARY_COMPLEX_FUNCTION(NAME, RETURN_TYPE) \
  CUSTOM_PUT_STD_BINARY_COMPLEX_FUNCTION(NAME, NAME, RETURN_TYPE)

//******************************************************************************

#define CUSTOM_PUT_STD_UNARY_REALCOMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME_REAL, CPPSTD_NAME_COMPLEX, RETURN_TYPE_REAL, RETURN_TYPE_COMPLEX) \
    UNIVERSAL_PUT(                                                             \
        1,                                                                     \
        ONERUT_NAME,                                                           \
        static_cast<RETURN_TYPE_REAL(*)(double)>(&std::CPPSTD_NAME_REAL),      \
        static_cast<RETURN_TYPE_COMPLEX(*)(const cx_double&)>(&std::CPPSTD_NAME_COMPLEX) \
    )

#define PUT_STD_UNARY_REALCOMPLEX_FUNCTION(NAME) \
  CUSTOM_PUT_STD_UNARY_REALCOMPLEX_FUNCTION(NAME, NAME, NAME, double, cx_double)

//------------------------------------------------------------------------------

#define CUSTOM_PUT_STD_BINARY_REALCOMPLEX_FUNCTION(ONERUT_NAME, CPPSTD_NAME_REAL, CPPSTD_NAME_COMPLEX, RETURN_TYPE_REAL, RETURN_TYPE_COMPLEX) \
    UNIVERSAL_PUT(                                                             \
        2,                                                                     \
        ONERUT_NAME,                                                           \
        static_cast<RETURN_TYPE_REAL(*)(double, double)>(&std::CPPSTD_NAME_REAL),  \
        static_cast<RETURN_TYPE_COMPLEX(*)(const cx_double&, const cx_double&)>(&std::CPPSTD_NAME_COMPLEX) \
    )

#define PUT_STD_BINARY_REALCOMPLEX_FUNCTION(NAME) \
  CUSTOM_PUT_STD_BINARY_REALCOMPLEX_FUNCTION(NAME, NAME, NAME, double, cx_double)

//******************************************************************************

namespace onerut_parser_rules {

    std::optional<std::shared_ptr<AbstractFunctionFactory>> MapWithFunctionFactories::get_or_empty(const std::string& name) const {
        if (functions.count(name) == 1) {
            return functions.at(name);
        } else {
            return std::nullopt;
        }
    }

    bool MapWithFunctionFactories::put(const std::string& name, std::shared_ptr<AbstractFunctionFactory> function) {
        if (functions.count(name))
            return false;
        functions[name] = function;
        return true;
    }

    void MapWithFunctionFactories::force_put(const std::string& name, std::shared_ptr<AbstractFunctionFactory> function) {
        functions[name] = function;
    }

    void MapWithFunctionFactories::put_cmath() {
        // ******************************************************
        // **** Functions for both real and complex numbers: ****
        // ******************************************************
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_cos, cos, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_cos, cos, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(cos);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_sin, sin, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sin, sin, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sin);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_tan, tan, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_tan, tan, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(tan);
        // ------------------------------------------------------
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_acos, acos, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_acos, acos, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(acos);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_asin, asin, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_asin, asin, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(asin);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_atan, atan, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_atan, atan, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(atan);
        // ------------------------------------------------------
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_cosh, cosh, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_cosh, cosh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(cosh);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_sinh, sinh, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sinh, sinh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sinh);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_tanh, tanh, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_tanh, tanh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(tanh);
        // ------------------------------------------------------
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_acosh, acosh, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_acosh, acosh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(acosh);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_asinh, asinh, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_asinh, asinh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(asinh);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_atanh, atanh, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_atanh, atanh, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(atanh);
        // ------------------------------------------------------        
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_exp, exp, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_exp, exp, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(exp);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_log, log, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_log, log, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(log);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_log10, log10, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_log10, log10, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(log10);
        // ------------------------------------------------------
        CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(re_pow, pow, double);
        CUSTOM_PUT_STD_BINARY_COMPLEX_FUNCTION(cx_pow, pow, cx_double);
        PUT_STD_BINARY_REALCOMPLEX_FUNCTION(pow);
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_sqrt, sqrt, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_sqrt, sqrt, cx_double);
        PUT_STD_UNARY_REALCOMPLEX_FUNCTION(sqrt);
        // ------------------------------------------------------
        CUSTOM_PUT_STD_UNARY_REAL_FUNCTION(re_abs, fabs, double);
        CUSTOM_PUT_STD_UNARY_COMPLEX_FUNCTION(cx_abs, abs, double);
        CUSTOM_PUT_STD_UNARY_REALCOMPLEX_FUNCTION(abs, fabs, abs, double, double)
        // ******************************************************
        // ****  Functions for real numbers: ********************
        // ******************************************************
        PUT_STD_BINARY_REAL_FUNCTION(atan2, double);
        PUT_STD_UNARY_REAL_FUNCTION(exp2, double);
        PUT_STD_UNARY_REAL_FUNCTION(expm1, double);
        PUT_STD_UNARY_REAL_FUNCTION(log1p, double);
        PUT_STD_UNARY_REAL_FUNCTION(log2, double);
        PUT_STD_UNARY_REAL_FUNCTION(cbrt, double);
        PUT_STD_BINARY_REAL_FUNCTION(hypot, double);
        PUT_STD_UNARY_REAL_FUNCTION(erf, double);
        PUT_STD_UNARY_REAL_FUNCTION(erfc, double);
        PUT_STD_UNARY_REAL_FUNCTION(tgamma, double);
        PUT_STD_UNARY_REAL_FUNCTION(lgamma, double);
        PUT_STD_UNARY_REAL_FUNCTION(ceil, double);
        PUT_STD_UNARY_REAL_FUNCTION(floor, double);
        PUT_STD_BINARY_REAL_FUNCTION(fmod, double);
        PUT_STD_UNARY_REAL_FUNCTION(trunc, double);
        PUT_STD_UNARY_REAL_FUNCTION(round, double);
        PUT_STD_BINARY_REAL_FUNCTION(remainder, double);
        PUT_STD_BINARY_REAL_FUNCTION(copysign, double);
        CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(dim, fdim, double);
        CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(max, fmax, double);
        CUSTOM_PUT_STD_BINARY_REAL_FUNCTION(min, fmin, double);
        // ******************************************************
        // **** Functions for complex numbers *******************
        // ******************************************************
        PUT_STD_UNARY_COMPLEX_FUNCTION(conj, cx_double);
        PUT_STD_UNARY_COMPLEX_FUNCTION(real, double);
        PUT_STD_UNARY_COMPLEX_FUNCTION(imag, double);
        PUT_STD_UNARY_COMPLEX_FUNCTION(arg, double);
        PUT_STD_UNARY_COMPLEX_FUNCTION(norm, double);
        // ******************************************************
        // **** Constants                     *******************
        // ******************************************************
        force_put("pi", std::make_unique<RealConstantFunctionFactory>(pi));
        force_put("e", std::make_unique<RealConstantFunctionFactory>(e));
        force_put("i", std::make_unique<ComplexConstantFunctionFactory>(1i));
    }

    void MapWithFunctionFactories::put_onerut_functions() {
        // Basic normal operator functions:
        force_put("custom_domain", std::make_unique<CreateNormalOperatorCustomDomainFunctionFactory>());
        force_put("state_index", std::make_unique<CreateNormalOperatorDomainStateIndexFunctionFactory>());
        force_put("zero", std::make_unique<NormalOperatorZeroFunctionFactory>());
        force_put("diag", std::make_unique<NormalOperatorDiagFunctionFactory>());
        force_put("hop", std::make_unique<NormalOperatorHopFunctionFactory>());
        force_put("eye", std::make_unique<NormalOperatorEyeFunctionFactory>());
        // Normal operator for oscillator algebra functions:
        force_put("oscillator_domain", std::make_unique<CreateOscillatorDomainFunctionFactory>());
        force_put("cr", std::make_unique<CreateCreationOperatorFunctionFactory>());
        force_put("an", std::make_unique<CreateAnihilationOperatorFunctionFactory>());
        // Normal operator for spin algebra functions:
        force_put("spin_domain", std::make_unique<CreateSpinDomainFunctionFactory>());
        force_put("Sz", std::make_unique<CreateSpinZetOperatorFunctionFactory>());
        force_put("Sp", std::make_unique<CreateSpinPlusOperatorFunctionFactory>());
        force_put("Sm", std::make_unique<CreateSpinMinusOperatorFunctionFactory>());
        // Normal operator for kron algebra functions:
        force_put("kron_domain", std::make_unique<CreateKronDomainFunctionFactory>());
        force_put("kron_placeholders", std::make_unique<CreateNormalOperatorKronPlaceholdersFunctionFactory>());
        force_put("at", std::make_unique<CreateNormalOperatorAtOperatorFunctionFactory>());
        // Calculation functions:        
        force_put("eigd", std::make_unique<NormalOperatorEigDenseFunctionFactory>());
        force_put("eigs", std::make_unique<NormalOperatorEigSparseFunctionFactory>());
        force_put("mean_in_eigenstate", std::make_unique<NormalOperatorMeanInEigenStateFunctionFactory>());
        force_put("thermal_mean", std::make_unique<NormalOperatorMeanThermalFunctionFactory>());
    }

    void MapWithFunctionFactories::put_imparative_request_functions() {
        force_put("LATCH", std::make_unique<LatchRequestFunctionFactory>());
        force_put("RESET", std::make_unique<ResetRequestFunctionFactory>());
        force_put("VALUE", std::make_unique<PrintValueRequestFunctionFactory>());
    }

    void MapWithFunctionFactories::put_all() {
        put_cmath();
        put_onerut_functions();
        put_imparative_request_functions();
    }

    void MapWithFunctionFactories::clear() {
        functions.clear();
    }

}