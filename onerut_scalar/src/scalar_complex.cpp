#include<cassert>
#include<type_traits>
#include<variant>
#include<algorithm>
#include<boost/cast.hpp>

#include<onerut_scalar/utility.hpp>
#include<onerut_scalar/scalar.hpp>

namespace onerut_scalar {

    // -------------------------------------------------------------------------
    // -------------- LITERAL CLASES  ------------------------------------------
    // -------------------------------------------------------------------------

    LitComplex::LitComplex(std::complex<double> value) :
    value(value) {
    }

    std::complex<double> LitComplex::value_complex() const {
        return value;
    }

    // -------------------------------------------------------------------------
    // -------------- OPUNARYPLUSMINUS CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    OpUnaryPlusMinusComplex::OpUnaryPlusMinusComplex(
            std::shared_ptr<const Complex> arg,
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
    // -------------- OPPLUSMINUS CLASES  --------------------------------------
    // -------------------------------------------------------------------------

    OpPlusMinusComplex::OpPlusMinusComplex(
            std::shared_ptr<const Complex> first_arg,
            std::vector<std::shared_ptr<const Complex>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<const Complex> ptr) {
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
    // -------------- OPPRODDIV CLASES  ----------------------------------------
    // -------------------------------------------------------------------------    

    OpProdDivComplex::OpProdDivComplex(
            std::shared_ptr<const Complex> first_arg,
            std::vector<std::shared_ptr <const  Complex>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<const Complex> ptr) {
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

}

