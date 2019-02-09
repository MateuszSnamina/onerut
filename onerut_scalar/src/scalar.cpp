#include<cassert>
#include<type_traits>
#include<variant>
#include<algorithm>
#include<boost/cast.hpp>

#include<onerut_scalar/utility.hpp>
#include<onerut_scalar/scalar.hpp>

using Variant2T = std::variant<long, double>;
using Variant3T = std::variant<long, double, std::complex<double>>;

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

