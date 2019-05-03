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

    double Integer::value_real() const {
        return boost::numeric_cast<double> (value_integer());
    }

    // -------------------------------------------------------------------------
    // -------------- LITERAL CLASES  ------------------------------------------
    // -------------------------------------------------------------------------

    LitInteger::LitInteger(long value) :
    value(value) {
    }

    long LitInteger::value_integer() const {
        return value;
    }

    std::vector<std::shared_ptr<const Complex>> LitInteger::dependency() const {
        assert(0); //TODO
    }

    // -------------------------------------------------------------------------
    // -------------- OPUNARYPLUSMINUS CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    OpUnaryPlusMinusInteger::OpUnaryPlusMinusInteger(
            std::shared_ptr<const Integer> arg,
            char op) :
    arg(arg),
    op(op) {
        assert(arg);
        assert(op == L'+' || op == L'-');
    }

    long OpUnaryPlusMinusInteger::value_integer() const {
        return _OpUnaryPlusMinus<long>()(arg->value_integer(), op);
    }

    std::vector<std::shared_ptr<const Complex>> OpUnaryPlusMinusInteger::dependency() const {
        assert(0); //TODO
    }

    // -------------------------------------------------------------------------
    // -------------- OPPLUSMINUS CLASES  --------------------------------------
    // -------------------------------------------------------------------------

    OpPlusMinusInteger::OpPlusMinusInteger(
            std::shared_ptr<const Integer> first_arg,
            std::vector<std::shared_ptr<const Integer>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<const Integer> ptr) {
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

    std::vector<std::shared_ptr<const Complex>> OpPlusMinusInteger::dependency() const {
        assert(0); //TODO
    }

    // -------------------------------------------------------------------------
    // -------------- OPPRODDIV CLASES  ----------------------------------------
    // -------------------------------------------------------------------------    

    OpProdDivInteger::OpProdDivInteger(
            std::shared_ptr<const Integer> first_arg,
            std::vector<std::shared_ptr <const Integer>> other_argv,
            const std::vector<char>& opv) :
    first_arg(first_arg),
    other_argv(other_argv),
    opv(opv) {
        assert(first_arg);
        assert(std::all_of(other_argv.cbegin(), other_argv.cend(), [](std::shared_ptr<const Integer> ptr) {
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

    std::vector<std::shared_ptr<const Complex>> OpProdDivInteger::dependency() const {
        assert(0); //TODO
    }

}

