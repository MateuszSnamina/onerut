#ifndef ONERUT_PARSER_RULES_FUNCTION_FACTORY_SCALAR
#define ONERUT_PARSER_RULES_FUNCTION_FACTORY_SCALAR

#include<algorithm>
#include<vector>

#include<onerut_scalar/function.hpp>
#include<onerut_scalar/utility_static_all_of.hpp>
#include<onerut_parser_rules/function_factory_abstract.hpp>
#include<onerut_parser_rules/asset_utility_concrete.hpp>

namespace onerut_parser_rules {

    // *************************************************************************
    // *********   ArgPreparator -- helper class   *****************************
    // *************************************************************************    

    template<typename T>
    class ArgPreparator {
    };

    template<>
    struct ArgPreparator<onerut_scalar::ArgInteger> {
        static bool do_match(const onerut_parser_exec::AssetDeref & arg);
        static std::shared_ptr<const onerut_scalar::Integer> extract(const onerut_parser_exec::AssetDeref & arg);
    };

    template<>
    struct ArgPreparator<onerut_scalar::ArgReal> {
        static bool do_match(const onerut_parser_exec::AssetDeref & arg);
        static std::shared_ptr<const onerut_scalar::Real> extract(const onerut_parser_exec::AssetDeref & arg);
    };

    template<>
    struct ArgPreparator<onerut_scalar::ArgComplex> {
        static bool do_match(const onerut_parser_exec::AssetDeref & arg);
        static std::shared_ptr<const onerut_scalar::Complex> extract(const onerut_parser_exec::AssetDeref & arg);
    };

    inline
    bool
    ArgPreparator<onerut_scalar::ArgInteger>::do_match(const onerut_parser_exec::AssetDeref & arg) {
        return utility::is_integer(arg);
    }

    inline
    std::shared_ptr<const onerut_scalar::Integer>
    ArgPreparator<onerut_scalar::ArgInteger>::extract(const onerut_parser_exec::AssetDeref & arg) {
        return utility::to_integer(arg);
    }

    inline
    bool
    ArgPreparator<onerut_scalar::ArgReal>::do_match(const onerut_parser_exec::AssetDeref & arg) {
        return utility::is_real_or_integer(arg);
    }

    inline
    std::shared_ptr<const onerut_scalar::Real>
    ArgPreparator<onerut_scalar::ArgReal>::extract(const onerut_parser_exec::AssetDeref & arg) {
        return utility::to_real(arg);
    }

    inline
    bool
    ArgPreparator<onerut_scalar::ArgComplex>::do_match(const onerut_parser_exec::AssetDeref & arg) {
        return utility::is_real_or_integer_or_complex(arg);
    }

    inline
    std::shared_ptr<const onerut_scalar::Complex>
    ArgPreparator<onerut_scalar::ArgComplex>::extract(const onerut_parser_exec::AssetDeref & arg) {
        return utility::to_complex(arg);
    }

    // *************************************************************************
    // *********   Low level onerut-scalar-function factories    ***************
    // *********   returning std::optional<Asset>                ***************
    // *********   (create a function or nullopt)                ***************    
    // *************************************************************************    

    // (1) For Callable being a function pointer or a function object:
    // (1a) a function (Asset) is created 
    //      if all arg_assets are either value or type.
    // (1b) nullopt is created otherwise.
    // (2) For Callable being nullptr: nullopt is created.

    template<typename Callable, typename... ArgTags>
    struct ScalarFunctionFactory {
        static std::optional<onerut_parser_exec::Asset> make_function_or_empty(
                Callable callable,
                typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, onerut_parser_exec::Asset>::type... arg_assets);
    };

    template<typename... ArgTags>
    struct ScalarFunctionFactory<std::nullptr_t, ArgTags...> {
        static std::optional<onerut_parser_exec::Asset> make_function_or_empty(
                std::nullptr_t,
                typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, onerut_parser_exec::Asset>::type... arg_assets);
    };

    // -------------------------------------------------------------------------
    // --------------  IMPLEMENTATION  -----------------------------------------
    // -------------------------------------------------------------------------

    template<typename Callable, typename... ArgTags>
    std::optional<onerut_parser_exec::Asset>
    _make_function_or_empty(
            Callable callable,
            typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, onerut_parser_exec::AssetDeref>::type... arg_assets_deref) {
        static_assert(!std::is_same<Callable, std::nullptr_t>::value);
        static_assert(onerut_scalar::utility::static_all_of<typename onerut_scalar::IsArgTag<ArgTags>::type...>::value);
        (assert(arg_assets_deref.is_either_value_or_type()), ...);
        if (!(ArgPreparator<ArgTags>::do_match(arg_assets_deref) && ... && true))
            return std::nullopt;
        using OnerutScalarFunctionType = typename onerut_scalar::DeduceFunction<Callable, ArgTags...>::DeducedFunction;
        using ReturnOnerutBaseType = typename OnerutScalarFunctionType::ReturnTag::OnerutBaseType;
        return onerut_parser_exec::Asset::from_value<ReturnOnerutBaseType>(
                std::make_shared<OnerutScalarFunctionType> (callable, ArgPreparator<ArgTags>::extract(arg_assets_deref)...));
    }

    template<typename Callable, typename... ArgTags>
    std::optional<onerut_parser_exec::Asset>
    _make_function_or_empty(
            Callable callable,
            typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, onerut_parser_exec::Asset>::type... arg_assets) {
        static_assert(!std::is_same<Callable, std::nullptr_t>::value);
        static_assert(onerut_scalar::utility::static_all_of<typename onerut_scalar::IsArgTag<ArgTags>::type...>::value);
        return _make_function_or_empty<Callable, ArgTags...>(callable, arg_assets.deref()...);
    }

    template<typename Callable, typename... ArgTags>
    std::optional<onerut_parser_exec::Asset>
    ScalarFunctionFactory<Callable, ArgTags...>::make_function_or_empty(
            Callable callable,
            typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, onerut_parser_exec::Asset>::type... arg_assets) {
        return _make_function_or_empty<Callable, ArgTags...>(callable, arg_assets...);
    }

    template<typename... ArgTags>
    std::optional<onerut_parser_exec::Asset>
    ScalarFunctionFactory<std::nullptr_t, ArgTags...>::make_function_or_empty(
            std::nullptr_t,
            typename std::enable_if<onerut_scalar::IsArgTag<ArgTags>::value, onerut_parser_exec::Asset>::type... arg_assets) {
        return std::nullopt;
    }

    // *************************************************************************
    // *********   Class that provides the                           ***********
    // *********   Low level onerut-scalar-function factories type   ***********
    // *********   for functions with given n-arity                  ***********    
    // *************************************************************************       

    // Example/Usage: 
    //
    // When writing ternary real function you need:
    // ScalarFunctionFactory<CallableReal, ArgReal, ArgReal, ArgReal>
    // Instead of typig ArgReal three times you may write:
    // NaryScalarFunctionFactory<CallableReal, ArgReal, 3>::ScalarFunctionFactoryType
    // 
    // When writing a real function with given arity use:
    // NaryScalarFunctionFactory<CallableReal, ArgReal, nary>::ScalarFunctionFactoryType

    // NaryScalarFunctionFactoryImpl -- helper implementation classes:

    template<typename Callable, typename ArgTag, unsigned nary_left_to_add, typename... ArgTags>
    struct NaryScalarFunctionFactoryImpl {
        static_assert(onerut_scalar::IsArgTag<ArgTag>::value);
        using ScalarFunctionFactoryType = typename NaryScalarFunctionFactoryImpl<Callable, ArgTag, nary_left_to_add - 1, ArgTag, ArgTags...>::ScalarFunctionFactoryType;
    };

    template<typename Callable, typename ArgTag, typename... ArgTags>
    struct NaryScalarFunctionFactoryImpl<Callable, ArgTag, 0u, ArgTags...> {
        static_assert(onerut_scalar::IsArgTag<ArgTag>::value);
        using ScalarFunctionFactoryType = ScalarFunctionFactory<Callable, ArgTags...>;
    };

    // NaryScalarFunctionFactory -- public API:

    template<typename Callable, typename ArgTag, unsigned nary>
    struct NaryScalarFunctionFactory {
        static_assert(onerut_scalar::IsArgTag<ArgTag>::value);
        using ScalarFunctionFactoryType = typename NaryScalarFunctionFactoryImpl<Callable, ArgTag, nary>::ScalarFunctionFactoryType;
    };

    // *************************************************************************
    // *********   High level onerut-scalar-function factories    **************
    // *********   returning Asset                        **************
    // *********   (create a function or an error)                **************
    // *************************************************************************    
    // *********   These factories comply                         **************
    // *********   AbstractAbstracctFactory interface             **************
    // *********   and may be stored in                           **************
    // *********   FunctionFactoryContainer container              **************
    // *************************************************************************

    // Helper classes:

    template<class ScalarFunctionFactory, unsigned nary, unsigned N>
    struct _NaryMakeFunctionOrEmptyInpl {
        using ArrayT = std::array<onerut_parser_exec::Asset, nary>;

        template<typename Callable, typename... Args>
        static inline std::optional<onerut_parser_exec::Asset>
        apply(const Callable & callable, const ArrayT& array, Args&&... args) {
            return _NaryMakeFunctionOrEmptyInpl<ScalarFunctionFactory, nary, N - 1 > ::apply(
                    callable,
                    array,
                    array[N - 1], std::forward<Args>(args)...);
        }
    };

    template<class ScalarFunctionFactory, unsigned nary>
    struct _NaryMakeFunctionOrEmptyInpl<ScalarFunctionFactory, nary, 0> {
        using ArrayT = std::array<onerut_parser_exec::Asset, nary>;

        template<typename Callable, typename... Args>
        static inline std::optional<onerut_parser_exec::Asset>
        apply(const Callable & callable, const ArrayT& /*array*/, Args&&... args) {
            return ScalarFunctionFactory::make_function_or_empty(callable, std::forward<Args>(args)...);
        }
    };

    // -------------------------------------------------------------------------        

    template<class ScalarFunctionFactory, unsigned nary, typename Callable>
    inline
    std::optional<onerut_parser_exec::Asset>
    _nary_make_function_or_empty(const Callable & callable, const std::array<onerut_parser_exec::Asset, nary>& array) {
        return _NaryMakeFunctionOrEmptyInpl<ScalarFunctionFactory, nary, nary>::apply(callable, array);
    }

    // -------------------------------------------------------------------------
    // --------- Public API ----------------------------------------------------
    // -------------------------------------------------------------------------

    template<unsigned nary, typename CallableReal, typename CallableComplex>
    class OverloadScalarFunctionFactory : public NaryFunctionFactory<nary> {
    public:
        OverloadScalarFunctionFactory(
                CallableReal callable_real,
                CallableComplex callable_complex);
        onerut_parser_exec::Asset make_function_otherwise_make_error(
                std::array<onerut_parser_exec::Asset, nary> args) const override;
    private:
        CallableReal callable_real;
        CallableComplex callable_complex;
    };

    template<unsigned nary, typename CallableReal, typename CallableComplex >
    OverloadScalarFunctionFactory<nary, CallableReal, CallableComplex>::OverloadScalarFunctionFactory(
            CallableReal callable_real,
            CallableComplex callable_complex) :
    callable_real(callable_real),
    callable_complex(callable_complex) {
    }

    template<unsigned nary, typename CallableReal, typename CallableComplex>
    onerut_parser_exec::Asset OverloadScalarFunctionFactory<nary, CallableReal, CallableComplex>::make_function_otherwise_make_error(
            std::array<onerut_parser_exec::Asset, nary> args_asset) const {
        std::array<onerut_parser_exec::AssetDeref, nary> args_asset_deref;
        std::transform(cbegin(args_asset), cend(args_asset), begin(args_asset_deref),
                [](const onerut_parser_exec::Asset & asset) {
                    return asset.deref();
                });
        const auto is_compile_error_fun = [](const onerut_parser_exec::AssetDeref & asset_deref) {
            return asset_deref.is_compile_error();
        };
        if (std::any_of(cbegin(args_asset_deref), cend(args_asset_deref),
                is_compile_error_fun)) {
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::CompileArgumentsError>());
        }
        const auto is_either_value_or_type_fun = [](const onerut_parser_exec::AssetDeref & asset_deref) {
            return asset_deref.is_either_value_or_type();
        };
        if (!std::all_of(cbegin(args_asset_deref), cend(args_asset_deref),
                is_either_value_or_type_fun)) {
            return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
        }
        using RealFunctionFactoryType = typename NaryScalarFunctionFactory<CallableReal, onerut_scalar::ArgReal, nary>::ScalarFunctionFactoryType;
        using ComplexFunctionFactoryType = typename NaryScalarFunctionFactory<CallableComplex, onerut_scalar::ArgComplex, nary>::ScalarFunctionFactoryType;
        if (const auto & result = _nary_make_function_or_empty<RealFunctionFactoryType, nary, CallableReal>(callable_real, args_asset))
            return *result;
        if (const auto & result = _nary_make_function_or_empty<ComplexFunctionFactoryType, nary, CallableComplex>(callable_complex, args_asset))
            return *result;
        return onerut_parser_exec::Asset::from_compile_error(std::make_shared<onerut_parser_exec::ArgumentMismatchError>());
    }
}

#endif
