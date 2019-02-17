#ifndef ONERUT_SCALAR_UTILITY
#define ONERUT_SCALAR_UTILITY

#include<cassert>
#include<type_traits>
#include<memory>
#include<variant>
#include<boost/cast.hpp>

#include<onerut_scalar/scalar_abstract.hpp>

namespace onerut_scalar {

    using Variant2T = std::variant<long, double>;
    using Variant3T = std::variant<long, double, std::complex<double>>;

    // -------------------------------------------------------------------------

    inline
    Variant3T as_variant(std::shared_ptr<const onerut_scalar::Complex> c) {
        if (const auto & i = std::dynamic_pointer_cast<const onerut_scalar::Integer>(c))
            return Variant3T{std::in_place_type<long>, i->value_integer()};
        if (const auto & r = std::dynamic_pointer_cast<const onerut_scalar::Real>(c))
            return Variant3T{std::in_place_type<double>, r->value_real()};
        return Variant3T{std::in_place_type<std::complex<double>>, c->value_complex()};
    }

    inline
    Variant2T as_variant(std::shared_ptr<const onerut_scalar::Real> r) {
        if (const auto & i = std::dynamic_pointer_cast<const onerut_scalar::Integer>(r))
            return Variant2T{std::in_place_type<long>, i->value_integer()};
        return Variant2T{std::in_place_type<double>, r->value_real()};
    }
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

    enum class PromotionLevel {
        integer = 1,
        real = 2,
        complex = 3
    };

    inline
    PromotionLevel do_propotion(PromotionLevel p1, PromotionLevel p2) {
        return static_cast<PromotionLevel> (std::max(static_cast<int> (p1), static_cast<int> (p2)));
    }

    struct VariantToPromotionLevelVisitor {
        using ResultT = PromotionLevel;
        ResultT operator()(long i) const;
        ResultT operator()(double r) const;
        ResultT operator()(std::complex<double> c) const;
    };

    inline
    typename VariantToPromotionLevelVisitor::ResultT
    VariantToPromotionLevelVisitor::operator()(long i) const {
        return PromotionLevel::integer;
    }

    inline
    typename VariantToPromotionLevelVisitor::ResultT
    VariantToPromotionLevelVisitor::operator()(double r) const {
        return PromotionLevel::real;
    }

    inline
    typename VariantToPromotionLevelVisitor::ResultT
    VariantToPromotionLevelVisitor::operator()(std::complex<double> c) const {
        return PromotionLevel::complex;
    }

    inline
    PromotionLevel variant_to_promotion_level(Variant2T v) {
        const VariantToPromotionLevelVisitor variant_to_promotion_level_visitor;
        return std::visit(variant_to_promotion_level_visitor, v);
    }

    inline
    PromotionLevel variant_to_promotion_level(Variant3T v) {
        const VariantToPromotionLevelVisitor variant_to_promotion_level_visitor;
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

    inline
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

#endif