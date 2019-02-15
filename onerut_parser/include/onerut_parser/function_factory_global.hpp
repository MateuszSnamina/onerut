#ifndef ONERUT_PARSER_FUNCTION_GLOBAL
#define ONERUT_PARSER_FUNCTION_GLOBAL


#include<optional>
#include<string>
#include<map>
#include<onerut_parser/function_factory_abstract.hpp>

#include<onerut_parser/function_factory_scalar.hpp> // templates implemntation, move implementation to another header


namespace onerut_parser {

    class GlobalFunctionFactories {
    public:
        static GlobalFunctionFactories& instance();
        std::optional<std::shared_ptr<AbstractFunctionFactory>> get_or_empty(const std::string& name) const;
        bool put(const std::string& name, std::shared_ptr<AbstractFunctionFactory> function);
        void force_put(const std::string& name, std::shared_ptr<AbstractFunctionFactory> function);
        void put_cmath();
    private:
        std::map<std::string, std::shared_ptr<AbstractFunctionFactory>> functions;

        template<typename CallableReal, typename CallableComplex>
        void put_unary_scalar_function_factory(
                std::string onerut_name,
                CallableReal callable_real,
                CallableComplex callable_complex);

        template<typename CallableReal>
        void put_unary_real_function_factory(
                std::string onerut_name,
                CallableReal callable_real);

        template<typename CallableComplex>
        void put_unary_complex_function_factory(
                std::string onerut_name,
                CallableComplex callable_complex);

        template<typename CallableReal, typename CallableComplex>
        void put_binary_scalar_function_factory(
                std::string onerut_name,
                CallableReal callable_real,
                CallableComplex callable_complex);

        template<typename CallableReal>
        void put_binary_real_function_factory(
                std::string onerut_name,
                CallableReal callable_real);

        template<typename CallableComplex>
        void put_binary_complex_function_factory(
                std::string onerut_name,
                CallableComplex callable_complex);        
    };

    // -------------------------------------------------------------------------
    // ------- template functions implementation -------------------------------
    // -------------------------------------------------------------------------

    template<typename CallableReal, typename CallableComplex>
    void GlobalFunctionFactories::put_unary_scalar_function_factory(
            std::string onerut_name,
            CallableReal callable_real,
            CallableComplex callable_complex) {
        force_put(
                onerut_name,
                std::make_shared<
                OverloadScalarUnaryFunctionFactory<CallableReal, CallableComplex>
                >(callable_real, callable_complex)
                );
    }

    template<typename CallableReal>
    void GlobalFunctionFactories::put_unary_real_function_factory(
            std::string onerut_name,
            CallableReal callable_real) {
        put_unary_scalar_function_factory(onerut_name, callable_real, nullptr);
    }

    template<typename CallableComplex>
    void GlobalFunctionFactories::put_unary_complex_function_factory(
            std::string onerut_name,
            CallableComplex callable_complex) {
        put_unary_scalar_function_factory(onerut_name, nullptr, callable_complex);
    }

    template<typename CallableReal, typename CallableComplex>
    void GlobalFunctionFactories::put_binary_scalar_function_factory(
            std::string onerut_name,
            CallableReal callable_real,
            CallableComplex callable_complex) {
        force_put(
                onerut_name,
                std::make_shared<
                OverloadScalarBinaryFunctionFactory<CallableReal, CallableComplex>
                >(callable_real, callable_complex)
                );
    }

    template<typename CallableReal>
    void GlobalFunctionFactories::put_binary_real_function_factory(
            std::string onerut_name,
            CallableReal callable_real) {
        put_binary_scalar_function_factory(onerut_name, callable_real, nullptr);
    }

    template<typename CallableComplex>
    void GlobalFunctionFactories::put_binary_complex_function_factory(
            std::string onerut_name,
            CallableComplex callable_complex) {
        put_binary_scalar_function_factory(onerut_name, nullptr, callable_complex);
    }    
}

#endif
