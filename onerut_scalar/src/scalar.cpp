#include<cassert>
#include<type_traits>
#include<variant>
#include<algorithm>

#include<onerut_scalar/scalar.hpp>

namespace {

    template<typename T>
    struct _OpUnaryPlusMinus {
        static_assert(std::is_arithmetic<T>::value);
        T operator()(T arg, char32_t op) const;
    };

    template<typename T>
    T _OpUnaryPlusMinus<T>::operator()(T arg, char32_t op) const {
        assert(op == L'+' || op == L'-');
        if (op == L'-')
            return -arg;
        return +arg;
    }

    template<typename T>
    struct _OpPlusMinus {
        static_assert(std::is_arithmetic<T>::value);
        T operator()(T first_arg, T second_arg, char32_t op) const;
    };

    template<typename T>
    T _OpPlusMinus<T>::operator()(T first_arg, T second_arg, char32_t op) const {
        assert(op == L'+' || op == L'-');
        if (op == L'-')
            return first_arg - second_arg;
        return first_arg + second_arg;
    }

    template<typename T>
    struct _OpProdDiv {
        static_assert(std::is_arithmetic<T>::value);
        T operator()(T first_arg, T second_arg, char32_t op) const;
    };

    template<typename T>
    T _OpProdDiv<T>::operator()(T first_arg, T second_arg, char32_t op) const {
        assert(op == L'*' || op == L'/');
        if (op == L'/')
            return first_arg / second_arg;
        return first_arg * second_arg;
    }

    // -------------------------------------------------------------------------

    std::variant<int, double> as_variant(std::shared_ptr<onerut_scalar::Double> d) {
        using ResultType = std::variant<int, double>;
        if (const auto & i = std::dynamic_pointer_cast<onerut_scalar::Int>(d))
            return ResultType{std::in_place_type<int>, i->value_int()};
        return ResultType{std::in_place_type<double>, d->value_double()};
    }

    // -------------------------------------------------------------------------

    enum class PromotionLevel {
        integer = 1,
        real = 2,
        complex = 3 // not used now!
    };

    // -------------------------------------------------------------------------

    PromotionLevel do_propotion(
            PromotionLevel p1,
            PromotionLevel p2) {
        return static_cast<PromotionLevel> (
                std::max(static_cast<int> (p1), static_cast<int> (p2))
                );
    }

    // -------------------------------------------------------------------------

    struct VariantToPromotionLevelVisitor {
        using ResultType = PromotionLevel;

        ResultType operator()(int i) const {
            return PromotionLevel::integer;
        }

        ResultType operator()(double d) const {
            return PromotionLevel::real;
        }

    };

    const VariantToPromotionLevelVisitor variant_to_promotion_level_visitor;

    PromotionLevel variant_to_promotion_level(std::variant<int, double> v) {
        return std::visit(variant_to_promotion_level_visitor, v);
    }

    // -------------------------------------------------------------------------    

    template<typename ResultType>
    struct AsTVisitor {
        template<typename U>
        ResultType operator()(U x) const;
    };

    template<typename ResultType>
    template<typename U>
    ResultType AsTVisitor<ResultType>::operator()(U x) const {
        return static_cast<ResultType> (x);
    }

    template<typename ResultType>
    ResultType as_t(std::variant<int, double> v) {
        const AsTVisitor<ResultType> as_t_visitor;
        return std::visit(as_t_visitor, v);
    }

    // -------------------------------------------------------------------------    

    template<template <typename> class _OpFlavour, typename ResultType>
    std::variant<int, double> _op_t(
            std::variant<int, double> first_arg,
            std::variant<int, double> second_arg,
            char32_t op) {
        using VariantType = std::variant<int, double>;
        const ResultType first_arg_t = as_t<ResultType>(first_arg);
        const ResultType second_arg_t = as_t<ResultType>(second_arg);
        const ResultType result_t = _OpFlavour<ResultType>()(first_arg_t, second_arg_t, op);
        return VariantType{std::in_place_type<ResultType>, result_t};
    }

    template<template <typename> class _OpFlavour>
    std::variant<int, double> _op(
            std::variant<int, double> first_arg,
            std::variant<int, double> second_arg,
            char32_t op) {
        const PromotionLevel first_arg_promotion_level = variant_to_promotion_level(first_arg);
        const PromotionLevel second_arg_promotion_level = variant_to_promotion_level(second_arg);
        const PromotionLevel op_promotion_level = do_propotion(first_arg_promotion_level, second_arg_promotion_level);
        if (op_promotion_level == PromotionLevel::integer)
            return _op_t<_OpFlavour, int>(first_arg, second_arg, op);
        return _op_t<_OpFlavour, double>(first_arg, second_arg, op);

    }

    std::variant<int, double> _op_plus_minus(
            std::variant<int, double> first_arg,
            std::variant<int, double> second_arg,
            char32_t op) {
        return _op<_OpPlusMinus>(first_arg, second_arg, op);
    }

    std::variant<int, double> _op_prod_div(
            std::variant<int, double> first_arg,
            std::variant<int, double> second_arg,
            char32_t op) {
        return _op<_OpProdDiv>(first_arg, second_arg, op);
    }

    // -------------------------------------------------------------------------    

    //    struct DebugPrintVisitor{
    //
    //        void operator()(int i) const {
    //            std::cout << "I" << i << std::endl;
    //        }
    //
    //        void operator()(double d) const {
    //            std::cout << "D" << d << std::endl;
    //        }
    //    };
    //    const DebugPrintVisitor debug_print_visitor;

}

namespace onerut_scalar {

    // -------------------------------------------------------------------------
    // -------------- ABSTRACT BASE CLASES -------------------------------------
    // -------------------------------------------------------------------------

    double Int::value_double() const {

        return static_cast<double> (value_int());
        // TODO: numeric_cast!!
    }

    // -------------------------------------------------------------------------
    // -------------- CAST CLASES  ---------------------------------------------
    // -------------------------------------------------------------------------

    CastIntToDouble::CastIntToDouble(std::shared_ptr<Int> arg) :
    arg(arg) {
        assert(arg);
    }

    double CastIntToDouble::value_double() const {
        return static_cast<double> (arg->value_int());
    }

    // -------------------------------------------------------------------------
    // -------------- LITERAL CLASES  ------------------------------------------
    // -------------------------------------------------------------------------

    LitDouble::LitDouble(double value) :
    value(value) {
    }

    double LitDouble::value_double() const {
        return value;
    }

    //--------------------------------------------------------------------------

    LitInt::LitInt(int value) :
    value(value) {
    }

    int LitInt::value_int() const {
        return value;
    }


    // -------------------------------------------------------------------------
    // -------------- OPUNARYPLUSMINUS CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    OpUnaryPlusMinusDouble::OpUnaryPlusMinusDouble(
            std::shared_ptr<Double> arg,
            char32_t op) :
    arg(arg),
    op(op) {
        assert(arg);
        assert(op == L'+' || op == L'-');
    }

    double OpUnaryPlusMinusDouble::value_double() const {
        return _OpUnaryPlusMinus<double>()(arg->value_double(), op);
    }

    // -------------------------------------------------------------------------

    OpUnaryPlusMinusInt::OpUnaryPlusMinusInt(
            std::shared_ptr<Int> arg,
            char32_t op) :
    arg(arg),
    op(op) {
        assert(arg);
        assert(op == L'+' || op == L'-');
    }

    int OpUnaryPlusMinusInt::value_int() const {
        return _OpUnaryPlusMinus<int>()(arg->value_int(), op);
    }

    // -------------------------------------------------------------------------
    // -------------- OPPLUSMINUS CLASES  --------------------------------------
    // -------------------------------------------------------------------------

    OpPlusMinusDouble::OpPlusMinusDouble(
            std::shared_ptr<Double> first_arg,
            std::vector<std::shared_ptr<Double>> other_argv,
            const std::vector<char32_t>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<Double> ptr) {
            return static_cast<bool> (ptr);
        }));
        assert(std::all_of(opv.cbegin(), opv.cend(), [](char32_t op) {
            return op == L'+' || op == L'-';
        }));
        assert(other_argv.size() == opv.size());
    }

    double OpPlusMinusDouble::value_double() const {
        std::variant<int, double> result = as_variant(first_arg);
        for (unsigned i = 0; i < other_argv.size(); i++) {
            const std::variant<int, double> other_arg = as_variant(other_argv[i]);
            const char32_t op = opv[i];
            result = _op_plus_minus(result, other_arg, op);
        }
        return as_t<double>(result);
    }

    // -------------------------------------------------------------------------

    OpPlusMinusInt::OpPlusMinusInt(
            std::shared_ptr<Int> first_arg,
            std::vector<std::shared_ptr<Int>> other_argv,
            const std::vector<char32_t>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<Int> ptr) {
            return static_cast<bool> (ptr);
        }));
        assert(std::all_of(opv.cbegin(), opv.cend(), [](char32_t op) {
            return op == L'+' || op == L'-';
        }));
        assert(other_argv.size() == opv.size());
    }

    int OpPlusMinusInt::value_int() const {
        int result = first_arg->value_int();
        for (unsigned i = 0; i < other_argv.size(); i++) {
            result = _OpPlusMinus<int>()(result, other_argv[i]->value_int(), opv[i]);
        }
        return result;
    }

    // -------------------------------------------------------------------------
    // -------------- OPPRODDIV CLASES  ----------------------------------------
    // -------------------------------------------------------------------------    

    OpProdDivDouble::OpProdDivDouble(
            std::shared_ptr<Double> first_arg,
            std::vector<std::shared_ptr < Double>> other_argv,
            const std::vector<char32_t>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<Double> ptr) {
            return static_cast<bool> (ptr);
        }));
        assert(std::all_of(opv.cbegin(), opv.cend(), [](char32_t op) {
            return op == L'*' || op == L'/';
        }));
        assert(other_argv.size() == opv.size());
    }

    double OpProdDivDouble::value_double() const {
        std::variant<int, double> result = as_variant(first_arg);
        for (unsigned i = 0; i < other_argv.size(); i++) {
            const std::variant<int, double> other_arg = as_variant(other_argv[i]);
            const char32_t op = opv[i];
            result = _op_prod_div(result, other_arg, op);
        }
        return as_t<double>(result);
    }

    // -------------------------------------------------------------------------

    OpProdDivInt::OpProdDivInt(
            std::shared_ptr<Int> first_arg,
            std::vector<std::shared_ptr < Int>> other_argv,
            const std::vector<char32_t>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<Int> ptr) {
            return static_cast<bool> (ptr);
        }));
        assert(std::all_of(opv.cbegin(), opv.cend(), [](char32_t op) {
            return op == L'*' || op == L'/';
        }));
        assert(other_argv.size() == opv.size());
    }

    int OpProdDivInt::value_int() const {
        int result = first_arg->value_int();
        for (unsigned i = 0; i < other_argv.size(); i++) {
            result = _OpProdDiv<int>()(result, other_argv[i]->value_int(), opv[i]);
        }
        return result;
    }
}

