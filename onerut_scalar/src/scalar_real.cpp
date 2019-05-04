#include<cassert>
#include<type_traits>
#include<variant>
#include<algorithm>
#include<boost/cast.hpp>

#include<onerut_scalar/utility.hpp>
#include<onerut_scalar/scalar.hpp>

namespace onerut_scalar {

    // -------------------------------------------------------------------------
    // -------------- ABSTRACT BASE CLASES -------------------------------------
    // -------------------------------------------------------------------------

    std::complex<double> Real::value_complex() const {
        return boost::numeric_cast<std::complex<double>> (value_real());
    }

    // -------------------------------------------------------------------------
    // -------------- CAST CLASES  ---------------------------------------------
    // -------------------------------------------------------------------------

    //    CastIntegerToReal::CastIntegerToReal(std::shared_ptr<Integer> arg) :
    //    arg(arg) {
    //        assert(arg);
    //    }
    //
    //    double CastIntegerToReal::value_real() const {
    //        return boost::numeric_cast<double> (arg->value_integer());
    //    }

    // -------------------------------------------------------------------------
    // -------------- LITERAL CLASES  ------------------------------------------
    // -------------------------------------------------------------------------

    LitReal::LitReal(double value) :
    value(value) {
    }

    double LitReal::value_real() const {
        return value;
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>> LitReal::dependence() const {
        return {};
    }

    // -------------------------------------------------------------------------
    // -------------- OPUNARYPLUSMINUS CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    OpUnaryPlusMinusReal::OpUnaryPlusMinusReal(
            std::shared_ptr<const Real> arg,
            char op) :
    arg(arg),
    op(op) {
        assert(arg);
        assert(op == L'+' || op == L'-');
    }

    double OpUnaryPlusMinusReal::value_real() const {
        return _OpUnaryPlusMinus<double>()(arg->value_real(), op);
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>> OpUnaryPlusMinusReal::dependence() const {
        return {};
    }

    // -------------------------------------------------------------------------
    // -------------- OPPLUSMINUS CLASES  --------------------------------------
    // -------------------------------------------------------------------------

    OpPlusMinusReal::OpPlusMinusReal(
            std::shared_ptr<const Real> first_arg,
            std::vector<std::shared_ptr<const Real>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<const Real> ptr) {
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

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>> OpPlusMinusReal::dependence() const {
        decltype(dependence()) result;
        result.reserve(1 + other_argv.size());
        result.push_back(first_arg);
        for (const auto& other_arg : other_argv) {
            result.push_back(other_arg);
        }
        return result;
    }

    // -------------------------------------------------------------------------
    // -------------- OPPRODDIV CLASES  ----------------------------------------
    // -------------------------------------------------------------------------    

    OpProdDivReal::OpProdDivReal(
            std::shared_ptr<const Real> first_arg,
            std::vector<std::shared_ptr <const Real>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<const Real> ptr) {
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

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>> OpProdDivReal::dependence() const {
        decltype(dependence()) result;
        result.reserve(1 + other_argv.size());
        result.push_back(first_arg);
        for (const auto& other_arg : other_argv) {
            result.push_back(other_arg);
        }
        return result;
    }

}

