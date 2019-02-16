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


        template<unsigned nary, typename CallableReal, typename CallableComplex>
        void put_nary_scalar_function_factory(
                std::string onerut_name,
                CallableReal callable_real,
                CallableComplex callable_complex);

        template<unsigned nary, typename CallableReal>
        void put_nary_real_function_factory(
                std::string onerut_name,
                CallableReal callable_real);

        template<unsigned nary, typename CallableComplex>
        void put_nary_complex_function_factory(
                std::string onerut_name,
                CallableComplex callable_complex);

    };

    // -------------------------------------------------------------------------
    // ------- template functions implementation -------------------------------
    // -------------------------------------------------------------------------

    template<unsigned nary, typename CallableReal, typename CallableComplex>
    void GlobalFunctionFactories::put_nary_scalar_function_factory(
            std::string onerut_name,
            CallableReal callable_real,
            CallableComplex callable_complex) {
        force_put(
                onerut_name,
                std::make_shared<
                OverloadScalarFunctionFactory<nary, CallableReal, CallableComplex>
                >(callable_real, callable_complex)
                );
    }

    template<unsigned nary, typename CallableReal>
    void GlobalFunctionFactories::put_nary_real_function_factory(
            std::string onerut_name,
            CallableReal callable_real) {
        put_nary_scalar_function_factory<nary>(onerut_name, callable_real, nullptr);
    }

    template<unsigned nary, typename CallableComplex>
    void GlobalFunctionFactories::put_nary_complex_function_factory(
            std::string onerut_name,
            CallableComplex callable_complex) {
        put_nary_scalar_function_factory<nary>(onerut_name, nullptr, callable_complex);
    }

}

#endif
