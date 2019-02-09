#include<cassert>
#include<type_traits>
#include<variant>
#include<algorithm>
#include<boost/cast.hpp>

#include<onerut_scalar/scalar.hpp>

namespace {

    template<typename T>
    struct _OpUnaryPlusMinus {
        static_assert(std::is_arithmetic<T>::value);
        T operator()(T arg, char op) const;
    };

    template<typename T>
    T _OpUnaryPlusMinus<T>::operator()(T arg, char op) const {
        assert(op == L'+' || op == L'-');
        if (op == L'-')
            return -arg;
        return +arg;
    }

    template<typename T>
    struct _OpPlusMinus {
        static_assert(std::is_arithmetic<T>::value);
        T operator()(T first_arg, T second_arg, char op) const;
    };

    template<typename T>
    T _OpPlusMinus<T>::operator()(T first_arg, T second_arg, char op) const {
        assert(op == L'+' || op == L'-');
        if (op == L'-')
            return first_arg - second_arg;
        return first_arg + second_arg;
    }

    template<typename T>
    struct _OpProdDiv {
        static_assert(std::is_arithmetic<T>::value);
        T operator()(T first_arg, T second_arg, char op) const;
    };

    template<typename T>
    T _OpProdDiv<T>::operator()(T first_arg, T second_arg, char op) const {
        assert(op == L'*' || op == L'/');
        if (op == L'/')
            return first_arg / second_arg;
        return first_arg * second_arg;
    }

    // -------------------------------------------------------------------------

    std::variant<long, double> as_variant(std::shared_ptr<onerut_scalar::Real> d) {
        using ResultType = std::variant<long, double>;
        if (const auto & i = std::dynamic_pointer_cast<onerut_scalar::Integer>(d))
            return ResultType{std::in_place_type<long>, i->value_integer()};
        return ResultType{std::in_place_type<double>, d->value_real()};
    }

    // -------------------------------------------------------------------------

    enum class PromotionLevel {
        integer = 1,
        real = 2,
        complex = 3 // not used now!
    };

    // -------------------------------------------------------------------------

    PromotionLevel do_propotion(PromotionLevel p1, PromotionLevel p2) {
        return static_cast<PromotionLevel> (std::max(static_cast<int> (p1), static_cast<int> (p2)));
    }

    // -------------------------------------------------------------------------

    struct VariantToPromotionLevelVisitor {
        using ResultType = PromotionLevel;

        ResultType operator()(long i) const {
            return PromotionLevel::integer;
        }

        ResultType operator()(double d) const {
            return PromotionLevel::real;
        }

    };

    const VariantToPromotionLevelVisitor variant_to_promotion_level_visitor;

    PromotionLevel variant_to_promotion_level(std::variant<long, double> v) {
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
        return boost::numeric_cast<ResultType> (x);
    }

    template<typename ResultType>
    ResultType as_t(std::variant<long, double> v) {
        const AsTVisitor<ResultType> as_t_visitor;
        return std::visit(as_t_visitor, v);
    }

    // -------------------------------------------------------------------------    

    template<template <typename> class _OpFlavour, typename ResultType>
    std::variant<long, double> _op_t(
            std::variant<long, double> first_arg,
            std::variant<long, double> second_arg,
            char op) {
        static_assert(std::is_arithmetic<ResultType>::value);
        using VariantType = std::variant<long, double>;
        const ResultType first_arg_t = as_t<ResultType>(first_arg);
        const ResultType second_arg_t = as_t<ResultType>(second_arg);
        const ResultType result_t = _OpFlavour<ResultType>()(first_arg_t, second_arg_t, op);
        return VariantType{std::in_place_type<ResultType>, result_t};
    }

    template<template <typename> class _OpFlavour>
    std::variant<long, double> _op(
            std::variant<long, double> first_arg,
            std::variant<long, double> second_arg,
            char op) {
        const PromotionLevel first_arg_promotion_level = variant_to_promotion_level(first_arg);
        const PromotionLevel second_arg_promotion_level = variant_to_promotion_level(second_arg);
        const PromotionLevel op_promotion_level = do_propotion(first_arg_promotion_level, second_arg_promotion_level);
        if (op_promotion_level == PromotionLevel::integer)
            return _op_t<_OpFlavour, long>(first_arg, second_arg, op);
        return _op_t<_OpFlavour, double>(first_arg, second_arg, op);
    }

    std::variant<long, double> _op_plus_minus(
            std::variant<long, double> first_arg,
            std::variant<long, double> second_arg,
            char op) {
        return _op<_OpPlusMinus>(first_arg, second_arg, op);
    }

    std::variant<long, double> _op_prod_div(
            std::variant<long, double> first_arg,
            std::variant<long, double> second_arg,
            char op) {
        return _op<_OpProdDiv>(first_arg, second_arg, op);
    }

    // -------------------------------------------------------------------------    

    //    struct DebugPrintVisitor{
    //
    //        void operator()(long i) const {
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

    std::complex<double> Real::value_complex() const {
        return boost::numeric_cast<std::complex<double>> (value_real());
    }

    double Integer::value_real() const {
        return boost::numeric_cast<double> (value_integer());
    }

    // -------------------------------------------------------------------------
    // -------------- CAST CLASES  ---------------------------------------------
    // -------------------------------------------------------------------------

    CastIntegerToReal::CastIntegerToReal(std::shared_ptr<Integer> arg) :
    arg(arg) {
        assert(arg);
    }

    double CastIntegerToReal::value_real() const {
        return boost::numeric_cast<double> (arg->value_integer());
    }

    // -------------------------------------------------------------------------
    // -------------- LITERAL CLASES  ------------------------------------------
    // -------------------------------------------------------------------------

    LitReal::LitReal(double value) :
    value(value) {
    }

    double LitReal::value_real() const {
        return value;
    }

    //--------------------------------------------------------------------------

    LitInteger::LitInteger(long value) :
    value(value) {
    }

    long LitInteger::value_integer() const {
        return value;
    }


    // -------------------------------------------------------------------------
    // -------------- OPUNARYPLUSMINUS CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    OpUnaryPlusMinusReal::OpUnaryPlusMinusReal(
            std::shared_ptr<Real> arg,
            char op) :
    arg(arg),
    op(op) {
        assert(arg);
        assert(op == L'+' || op == L'-');
    }

    double OpUnaryPlusMinusReal::value_real() const {
        return _OpUnaryPlusMinus<double>()(arg->value_real(), op);
    }

    // -------------------------------------------------------------------------

    OpUnaryPlusMinusInteger::OpUnaryPlusMinusInteger(
            std::shared_ptr<Integer> arg,
            char op) :
    arg(arg),
    op(op) {
        assert(arg);
        assert(op == L'+' || op == L'-');
    }

    long OpUnaryPlusMinusInteger::value_integer() const {
        return _OpUnaryPlusMinus<long>()(arg->value_integer(), op);
    }

    // -------------------------------------------------------------------------
    // -------------- OPPLUSMINUS CLASES  --------------------------------------
    // -------------------------------------------------------------------------

    OpPlusMinusReal::OpPlusMinusReal(
            std::shared_ptr<Real> first_arg,
            std::vector<std::shared_ptr<Real>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<Real> ptr) {
            return static_cast<bool> (ptr);
        }));
        assert(std::all_of(opv.cbegin(), opv.cend(), [](char op) {
            return op == L'+' || op == L'-';
        }));
        assert(other_argv.size() == opv.size());
    }

    double OpPlusMinusReal::value_real() const {
        std::variant<long, double> result = as_variant(first_arg);
        for (unsigned i = 0; i < other_argv.size(); i++) {
            const std::variant<long, double> other_arg = as_variant(other_argv[i]);
            const char op = opv[i];
            result = _op_plus_minus(result, other_arg, op);
        }
        return as_t<double>(result);
    }

    // -------------------------------------------------------------------------

    OpPlusMinusInteger::OpPlusMinusInteger(
            std::shared_ptr<Integer> first_arg,
            std::vector<std::shared_ptr<Integer>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<Integer> ptr) {
            return static_cast<bool> (ptr);
        }));
        assert(std::all_of(opv.cbegin(), opv.cend(), [](char op) {
            return op == L'+' || op == L'-';
        }));
        assert(other_argv.size() == opv.size());
    }

    long OpPlusMinusInteger::value_integer() const {
        long result = first_arg->value_integer();
        for (unsigned i = 0; i < other_argv.size(); i++) {
            result = _OpPlusMinus<long>()(result, other_argv[i]->value_integer(), opv[i]);
        }
        return result;
    }

    // -------------------------------------------------------------------------
    // -------------- OPPRODDIV CLASES  ----------------------------------------
    // -------------------------------------------------------------------------    

    OpProdDivReal::OpProdDivReal(
            std::shared_ptr<Real> first_arg,
            std::vector<std::shared_ptr < Real>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<Real> ptr) {
            return static_cast<bool> (ptr);
        }));
        assert(std::all_of(opv.cbegin(), opv.cend(), [](char op) {
            return op == L'*' || op == L'/';
        }));
        assert(other_argv.size() == opv.size());
    }

    double OpProdDivReal::value_real() const {
        std::variant<long, double> result = as_variant(first_arg);
        for (unsigned i = 0; i < other_argv.size(); i++) {
            const std::variant<long, double> other_arg = as_variant(other_argv[i]);
            const char op = opv[i];
            result = _op_prod_div(result, other_arg, op);
        }
        return as_t<double>(result);
    }

    // -------------------------------------------------------------------------

    OpProdDivInteger::OpProdDivInteger(
            std::shared_ptr<Integer> first_arg,
            std::vector<std::shared_ptr < Integer>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<Integer> ptr) {
            return static_cast<bool> (ptr);
        }));
        assert(std::all_of(opv.cbegin(), opv.cend(), [](char op) {
            return op == L'*' || op == L'/';
        }));
        assert(other_argv.size() == opv.size());
    }

    long OpProdDivInteger::value_integer() const {
        long result = first_arg->value_integer();
        for (unsigned i = 0; i < other_argv.size(); i++) {
            result = _OpProdDiv<long>()(result, other_argv[i]->value_integer(), opv[i]);
        }
        return result;
    }
}

