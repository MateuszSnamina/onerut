#include<cassert>
#include<type_traits>
#include<variant>
#include<algorithm>
#include<boost/cast.hpp>

#include<onerut_scalar/scalar.hpp>

using Variant2T = std::variant<long, double>;
using Variant3T = std::variant<long, double, std::complex<double>>;

namespace {

    // -------------------------------------------------------------------------

    template<typename T>
    class is_onerut_scalar : public std::false_type {
    };

    template<>
    class is_onerut_scalar<long> : public std::true_type {
    };

    template<>
    class is_onerut_scalar<double> : public std::true_type {
    };

    template<>
    class is_onerut_scalar<std::complex<double>> : public std::true_type
    {
    };

    // -------------------------------------------------------------------------

    template<typename T>
    struct _OpUnaryPlusMinus {
        static_assert(is_onerut_scalar<T>::value);
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
        static_assert(is_onerut_scalar<T>::value);
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
        static_assert(is_onerut_scalar<T>::value);
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

    Variant3T as_variant(std::shared_ptr<onerut_scalar::Complex> c) {
        if (const auto & i = std::dynamic_pointer_cast<onerut_scalar::Integer>(c))
            return Variant3T{std::in_place_type<long>, i->value_integer()};
        if (const auto & r = std::dynamic_pointer_cast<onerut_scalar::Real>(c))
            return Variant3T{std::in_place_type<double>, r->value_real()};
        return Variant3T{std::in_place_type<std::complex<double>>, c->value_complex()};
    }

    Variant2T as_variant(std::shared_ptr<onerut_scalar::Real> r) {
        if (const auto & i = std::dynamic_pointer_cast<onerut_scalar::Integer>(r))
            return Variant2T{std::in_place_type<long>, i->value_integer()};
        return Variant2T{std::in_place_type<double>, r->value_real()};
    }

    // -------------------------------------------------------------------------

    enum class PromotionLevel {
        integer = 1,
        real = 2,
        complex = 3
    };

    // -------------------------------------------------------------------------

    PromotionLevel do_propotion(PromotionLevel p1, PromotionLevel p2) {
        return static_cast<PromotionLevel> (std::max(static_cast<int> (p1), static_cast<int> (p2)));
    }

    // -------------------------------------------------------------------------

    struct VariantToPromotionLevelVisitor {
        using ResultT = PromotionLevel;

        ResultT operator()(long i) const {
            return PromotionLevel::integer;
        }

        ResultT operator()(double r) const {
            return PromotionLevel::real;
        }

        ResultT operator()(std::complex<double> c) const {
            return PromotionLevel::complex;
        }
    };

    const VariantToPromotionLevelVisitor variant_to_promotion_level_visitor;

    PromotionLevel variant_to_promotion_level(Variant2T v) {
        return std::visit(variant_to_promotion_level_visitor, v);
    }

    PromotionLevel variant_to_promotion_level(Variant3T v) {
        return std::visit(variant_to_promotion_level_visitor, v);
    }
    // -------------------------------------------------------------------------        

    template<typename ToT, typename FromT>
    struct scalar_caster {
        ToT operator()(FromT x);
    };

    template<typename ToT>
    struct scalar_caster<ToT, std::complex<double> > {
        ToT operator()(std::complex<double> x);
    };

    template<>
    struct scalar_caster<std::complex<double>, std::complex<double> > {
        std::complex<double> operator()(std::complex<double> x);
    };

    template<typename ToT, typename FromT>
    ToT
    scalar_caster<ToT, FromT>::operator()(FromT x) {
        return boost::numeric_cast<ToT> (x);
    }

    template<typename ToT>
    ToT
    scalar_caster<ToT, std::complex<double>>::operator()(std::complex<double> x) {
        static_assert(!std::is_same<ToT, std::complex<double>>::value);
        return boost::numeric_cast<ToT> (x.real());
    }

    std::complex<double>
    scalar_caster<std::complex<double>, std::complex<double>>::operator()(std::complex<double> x) {
        return x;
    }

    // -------------------------------------------------------------------------        

    template<typename ResultT>
    struct AsTVisitor {
        template<typename U>
        ResultT operator()(U x) const;
    };

    template<typename ResultT>
    template<typename U>
    ResultT AsTVisitor<ResultT>::operator()(U x) const {
        return scalar_caster<ResultT, U>()(x);
    }

    template<typename ResultT>
    ResultT as_t(Variant2T v) {
        const AsTVisitor<ResultT> as_t_visitor;
        return std::visit(as_t_visitor, v);
    }

    template<typename ResultT>
    ResultT as_t(Variant3T v) {
        const AsTVisitor<ResultT> as_t_visitor;
        return std::visit(as_t_visitor, v);
    }
    // -------------------------------------------------------------------------    

    template<template <typename> class _OpFlavour, typename ResultT, typename VariantT>
    VariantT _op_t(VariantT first_arg, VariantT second_arg, char op) {
        static_assert(is_onerut_scalar<ResultT>::value);
        static_assert(std::is_same<VariantT, Variant2T>::value || std::is_same<VariantT, Variant3T>::value);
        const ResultT first_arg_t = as_t<ResultT>(first_arg);
        const ResultT second_arg_t = as_t<ResultT>(second_arg);
        const ResultT result_t = _OpFlavour<ResultT>()(first_arg_t, second_arg_t, op);
        return VariantT{std::in_place_type<ResultT>, result_t};
    }

    // -------------------------------------------------------------------------

    template<template <typename> class _OpFlavour>
    Variant3T _op(Variant3T first_arg, Variant3T second_arg, char op) {
        const PromotionLevel first_arg_promotion_level = variant_to_promotion_level(first_arg);
        const PromotionLevel second_arg_promotion_level = variant_to_promotion_level(second_arg);
        const PromotionLevel op_promotion_level = do_propotion(first_arg_promotion_level, second_arg_promotion_level);
        if (op_promotion_level == PromotionLevel::integer)
            return _op_t<_OpFlavour, long>(first_arg, second_arg, op);
        if (op_promotion_level == PromotionLevel::real)
            return _op_t<_OpFlavour, double>(first_arg, second_arg, op);
        assert(op_promotion_level == PromotionLevel::complex);
        return _op_t<_OpFlavour, std::complex<double>>(first_arg, second_arg, op);
    }

    template<template <typename> class _OpFlavour>
    Variant2T _op(Variant2T first_arg, Variant2T second_arg, char op) {
        const PromotionLevel first_arg_promotion_level = variant_to_promotion_level(first_arg);
        const PromotionLevel second_arg_promotion_level = variant_to_promotion_level(second_arg);
        const PromotionLevel op_promotion_level = do_propotion(first_arg_promotion_level, second_arg_promotion_level);
        if (op_promotion_level == PromotionLevel::integer)
            return _op_t<_OpFlavour, long>(first_arg, second_arg, op);
        assert(op_promotion_level == PromotionLevel::real);
        return _op_t<_OpFlavour, double>(first_arg, second_arg, op);
    }

    // -------------------------------------------------------------------------

    template<class VariantT>
    VariantT _op_plus_minus(VariantT first_arg, VariantT second_arg, char op) {
        static_assert(std::is_same<VariantT, Variant2T>::value || std::is_same<VariantT, Variant3T>::value);
        return _op<_OpPlusMinus>(first_arg, second_arg, op);
    }

    // -------------------------------------------------------------------------

    template<class VariantT>
    VariantT _op_prod_div(VariantT first_arg, VariantT second_arg, char op) {
        static_assert(std::is_same<VariantT, Variant2T>::value || std::is_same<VariantT, Variant3T>::value);
        return _op<_OpProdDiv>(first_arg, second_arg, op);
    }

    // -------------------------------------------------------------------------    

    //    struct DebugPrintVisitor {
    //
    //        void operator()(long i) const {
    //            std::cout << "I" << i << std::endl;
    //        }
    //
    //        void operator()(double d) const {
    //            std::cout << "D" << d << std::endl;
    //        }
    //
    //        void operator()(std::complex<double> c) const {
    //            std::cout << "C" << c << std::endl;
    //        }
    //    };
    //    const DebugPrintVisitor debug_print_visitor;
    //
    //    void print(Variant2T v) {
    //        std::cout << "V2->";
    //        std::visit(debug_print_visitor, v);
    //    }
    //
    //    void print(Variant3T v) {
    //        std::cout << "V3->";
    //        std::visit(debug_print_visitor, v);
    //    }

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

    LitComplex::LitComplex(std::complex<double> value) :
    value(value) {
    }

    std::complex<double> LitComplex::value_complex() const {
        return value;
    }

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

    OpUnaryPlusMinusComplex::OpUnaryPlusMinusComplex(
            std::shared_ptr<Complex> arg,
            char op) :
    arg(arg),
    op(op) {
        assert(arg);
        assert(op == L'+' || op == L'-');
    }

    std::complex<double> OpUnaryPlusMinusComplex::value_complex() const {
        return _OpUnaryPlusMinus<std::complex<double>>()(arg->value_complex(), op);
    }

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

    OpPlusMinusComplex::OpPlusMinusComplex(
            std::shared_ptr<Complex> first_arg,
            std::vector<std::shared_ptr<Complex>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<Complex> ptr) {
            return static_cast<bool> (ptr);
        }));
        assert(std::all_of(opv.cbegin(), opv.cend(), [](char op) {
            return op == L'+' || op == L'-';
        }));
        assert(other_argv.size() == opv.size());
    }

    std::complex<double> OpPlusMinusComplex::value_complex() const {
        Variant3T result = as_variant(first_arg);
        for (unsigned i = 0; i < other_argv.size(); i++) {
            const Variant3T other_arg = as_variant(other_argv[i]);
            const char op = opv[i];
            result = _op_plus_minus(result, other_arg, op);
        }
        return as_t<std::complex<double>>(result);
    }

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
        Variant2T result = as_variant(first_arg);
        for (unsigned i = 0; i < other_argv.size(); i++) {
            const Variant2T other_arg = as_variant(other_argv[i]);
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

    OpProdDivComplex::OpProdDivComplex(
            std::shared_ptr<Complex> first_arg,
            std::vector<std::shared_ptr < Complex>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<Complex> ptr) {
            return static_cast<bool> (ptr);
        }));
        assert(std::all_of(opv.cbegin(), opv.cend(), [](char op) {
            return op == L'*' || op == L'/';
        }));
        assert(other_argv.size() == opv.size());
    }

    std::complex<double> OpProdDivComplex::value_complex() const {
        Variant3T result = as_variant(first_arg);
        for (unsigned i = 0; i < other_argv.size(); i++) {
            const Variant3T other_arg = as_variant(other_argv[i]);
            const char op = opv[i];
            result = _op_prod_div(result, other_arg, op);
        }
        return as_t<std::complex<double>>(result);
    }

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
        Variant2T result = as_variant(first_arg);
        for (unsigned i = 0; i < other_argv.size(); i++) {
            const Variant2T other_arg = as_variant(other_argv[i]);
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

