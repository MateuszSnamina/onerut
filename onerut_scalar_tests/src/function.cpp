#include<gtest/gtest.h>

#include<onerut_scalar/scalar.hpp>
#include<onerut_scalar/function_2.hpp>

using cx_double = std::complex<double>;

// -----------------------------------------------------------------------------
// --------------------  test cases  -------------------------------------------
// -----------------------------------------------------------------------------

long f(double a, double b) {
    return 2 * a + b;
}

TEST(buildin_function_explicite_api, test0) {
    const auto r1 = std::make_shared<onerut_scalar::LitReal>(6.4);
    const auto r2 = std::make_shared<onerut_scalar::LitReal>(7.4);
    // create FunctionType using AutomaticApi (here automatic is return type deduction).
    long(*fp)(double, double) = &f;
    using FunctionType = onerut_scalar::Function<decltype(fp), onerut_scalar::ReturnInteger, onerut_scalar::ArgReal, onerut_scalar::ArgReal>;
    using ReturnTag = typename FunctionType::ReturnTag;
    static_assert(std::is_same<ReturnTag, onerut_scalar::ReturnInteger>::value);
    // Test the Function type:    
    using ReturnOnerutBaseType = typename FunctionType::ReturnTag::OnerutBaseType;
    static_assert(std::is_same<ReturnOnerutBaseType, onerut_scalar::Integer>::value);
    // Test the Function object:    
    const std::shared_ptr<ReturnOnerutBaseType> r = std::make_shared<FunctionType>(f, r1, r2);
    const long expect = static_cast<long> (2 * 6.4 + 7.4);
    ASSERT_EQ(static_cast<long> (expect), r->value_integer());
    ASSERT_EQ(static_cast<double> (expect), r->value_real());
    ASSERT_EQ(static_cast<cx_double> (expect), r->value_complex());
}

TEST(buildin_function_automatic_api, test0) {
    const auto r1 = std::make_shared<onerut_scalar::LitReal>(6.4);
    const auto r2 = std::make_shared<onerut_scalar::LitReal>(7.4);
    // create FunctionType using AutomaticApi (here automatic is return type deduction).
    long(*fp)(double, double) = &f;
    using FunctionTypeAutomaticApi = typename onerut_scalar::DeduceFunction<decltype(fp), onerut_scalar::ArgReal, onerut_scalar::ArgReal>::DeducedFunction;
    // create FunctionType using ExpliciteApi (with explicit return type specification)-- just for the sake of comparison 
    using FunctionTypeExpliciteApi = onerut_scalar::Function<decltype(fp), onerut_scalar::ReturnInteger, onerut_scalar::ArgReal, onerut_scalar::ArgReal>;
    // Test the Function type:
    static_assert(std::is_same<FunctionTypeAutomaticApi, FunctionTypeExpliciteApi>::value);
    using FunctionType = FunctionTypeAutomaticApi;
    using ReturnTag = typename FunctionType::ReturnTag;
    static_assert(std::is_same<ReturnTag, onerut_scalar::ReturnInteger>::value);
    using ReturnOnerutBaseType = typename FunctionType::ReturnTag::OnerutBaseType;
    static_assert(std::is_same<ReturnOnerutBaseType, onerut_scalar::Integer>::value);
    // Test the Function object:
    const std::shared_ptr<ReturnOnerutBaseType> r = std::make_shared<FunctionType>(f, r1, r2);
    const long expect = static_cast<long> (2 * 6.4 + 7.4);
    ASSERT_EQ(static_cast<long> (expect), r->value_integer());
    ASSERT_EQ(static_cast<double> (expect), r->value_real());
    ASSERT_EQ(static_cast<cx_double> (expect), r->value_complex());
}

struct F {

    long operator()(double a, double b) const {
        return 3 * a + b;
    }

    double operator()(double a, long b) const {
        return 4 * a + 2 * b;
    }

};

TEST(function_object_explicite_api, test0) {
    const auto r1 = std::make_shared<onerut_scalar::LitReal>(6.4);
    const auto r2 = std::make_shared<onerut_scalar::LitReal>(7.5);
    // create FunctionType using AutomaticApi (here automatic is return type deduction).
    F function_object = F();
    using FunctionType = onerut_scalar::Function<F, onerut_scalar::ReturnInteger, onerut_scalar::ArgReal, onerut_scalar::ArgReal>;
    using ReturnTag = typename FunctionType::ReturnTag;
    static_assert(std::is_same<ReturnTag, onerut_scalar::ReturnInteger>::value);
    // Test the Function type:    
    using ReturnOnerutBaseType = typename FunctionType::ReturnTag::OnerutBaseType;
    static_assert(std::is_same<ReturnOnerutBaseType, onerut_scalar::Integer>::value);
    // Test the Function object:    
    const std::shared_ptr<ReturnOnerutBaseType> r = std::make_shared<FunctionType>(function_object, r1, r2);
    const long expect = static_cast<long> (3 * 6.4 + 7.5);
    ASSERT_EQ(static_cast<long> (expect), r->value_integer());
    ASSERT_EQ(static_cast<double> (expect), r->value_real());
    ASSERT_EQ(static_cast<cx_double> (expect), r->value_complex());
}

TEST(function_object_automatic_api, test0) {
    const auto r1 = std::make_shared<onerut_scalar::LitReal>(6.4);
    const auto r2 = std::make_shared<onerut_scalar::LitReal>(7.5);
    // create FunctionType using AutomaticApi (here automatic is return type deduction).
    F function_object = F();
    using FunctionTypeAutomaticApi = typename onerut_scalar::DeduceFunction<F, onerut_scalar::ArgReal, onerut_scalar::ArgReal>::DeducedFunction;
    // create FunctionType using ExpliciteApi (with explicit return type specification)-- just for the sake of comparison 
    using FunctionTypeExpliciteApi = onerut_scalar::Function<F, onerut_scalar::ReturnInteger, onerut_scalar::ArgReal, onerut_scalar::ArgReal>;
    // Test the Function type:
    static_assert(std::is_same<FunctionTypeAutomaticApi, FunctionTypeExpliciteApi>::value);
    using FunctionType = FunctionTypeAutomaticApi;
    using ReturnTag = typename FunctionType::ReturnTag;
    static_assert(std::is_same<ReturnTag, onerut_scalar::ReturnInteger>::value);
    using ReturnOnerutBaseType = typename FunctionType::ReturnTag::OnerutBaseType;
    static_assert(std::is_same<ReturnOnerutBaseType, onerut_scalar::Integer>::value);
    // Test the Function object:
    const std::shared_ptr<ReturnOnerutBaseType> r = std::make_shared<FunctionType>(function_object, r1, r2);
    const long expect = static_cast<long> (3 * 6.4 + 7.5);
    ASSERT_EQ(static_cast<long> (expect), r->value_integer());
    ASSERT_EQ(static_cast<double> (expect), r->value_real());
    ASSERT_EQ(static_cast<cx_double> (expect), r->value_complex());
}


//xzxzxzxzx

TEST(function_object_explicite_api, test1) {
    const auto r1 = std::make_shared<onerut_scalar::LitReal>(6.4);
    const auto r2 = std::make_shared<onerut_scalar::LitInteger>(7);
    // create FunctionType using AutomaticApi (here automatic is return type deduction).
    F function_object = F();
    using FunctionType = onerut_scalar::Function<F, onerut_scalar::ReturnReal, onerut_scalar::ArgReal, onerut_scalar::ArgInteger>;
    using ReturnTag = typename FunctionType::ReturnTag;
    static_assert(std::is_same<ReturnTag, onerut_scalar::ReturnReal>::value);
    // Test the Function type:    
    using ReturnOnerutBaseType = typename FunctionType::ReturnTag::OnerutBaseType;
    static_assert(std::is_same<ReturnOnerutBaseType, onerut_scalar::Real>::value);
    // Test the Function object:    
    const std::shared_ptr<ReturnOnerutBaseType> r = std::make_shared<FunctionType>(function_object, r1, r2);
    const double expect = static_cast<double> (4 * 6.4 + 2 * 7);
    ASSERT_EQ(static_cast<double> (expect), r->value_real());
    ASSERT_EQ(static_cast<cx_double> (expect), r->value_complex());
}

TEST(function_object_automatic_api, test1) {
    const auto r1 = std::make_shared<onerut_scalar::LitReal>(6.4);
    const auto r2 = std::make_shared<onerut_scalar::LitInteger>(7);
    // create FunctionType using AutomaticApi (here automatic is return type deduction).
    F function_object = F();
    using FunctionTypeAutomaticApi = typename onerut_scalar::DeduceFunction<F, onerut_scalar::ArgReal, onerut_scalar::ArgInteger>::DeducedFunction;
    // create FunctionType using ExpliciteApi (with explicit return type specification)-- just for the sake of comparison 
    using FunctionTypeExpliciteApi = onerut_scalar::Function<F, onerut_scalar::ReturnReal, onerut_scalar::ArgReal, onerut_scalar::ArgInteger>;
    // Test the Function type:
    static_assert(std::is_same<FunctionTypeAutomaticApi, FunctionTypeExpliciteApi>::value);
    using FunctionType = FunctionTypeAutomaticApi;
    using ReturnTag = typename FunctionType::ReturnTag;
    static_assert(std::is_same<ReturnTag, onerut_scalar::ReturnReal>::value);
    using ReturnOnerutBaseType = typename FunctionType::ReturnTag::OnerutBaseType;
    static_assert(std::is_same<ReturnOnerutBaseType, onerut_scalar::Real>::value);
    // Test the Function object:
    const std::shared_ptr<ReturnOnerutBaseType> r = std::make_shared<FunctionType>(function_object, r1, r2);
    const double expect = static_cast<double> (4 * 6.4 + 2 * 7);
    ASSERT_EQ(static_cast<double> (expect), r->value_real());
    ASSERT_EQ(static_cast<cx_double> (expect), r->value_complex());
}