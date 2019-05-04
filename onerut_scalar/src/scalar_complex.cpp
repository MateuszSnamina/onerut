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

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>> LitComplex::dependence() const {
        return {};
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

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>> OpUnaryPlusMinusComplex::dependence() const {
        return {arg};
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

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>> OpPlusMinusComplex::dependence() const {
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

    OpProdDivComplex::OpProdDivComplex(
            std::shared_ptr<const Complex> first_arg,
            std::vector<std::shared_ptr <const Complex>> other_argv,
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

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>> OpProdDivComplex::dependence() const {
        decltype(dependence()) result;
        result.reserve(1 + other_argv.size());
        result.push_back(first_arg);
        for (const auto& other_arg : other_argv) {
            result.push_back(other_arg);
        }
        return result;
    }

}

