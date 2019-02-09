#ifndef ONERUT_SCALAR_SCALAR_INTEGER
#define ONERUT_SCALAR_SCALAR_INTEGER

#include<onerut_scalar/scalar_real.hpp>

#include<memory>
#include<vector>

namespace onerut_scalar {

    // -------------------------------------------------------------------------
    // -------------- ABSTRACT BASE CLASES -------------------------------------
    // -------------------------------------------------------------------------

    class Integer : public Real {
    public:
        virtual long value_integer() const = 0;
        virtual double value_real() const override;
        virtual ~Integer() = default;
    };

    // -------------------------------------------------------------------------
    // -------------- LITERAL CLASES  ------------------------------------------
    // -------------------------------------------------------------------------

    class LitInteger : public Integer {
    public:
        LitInteger(long value);
        long value_integer() const override;
        const long value;
    };

    // -------------------------------------------------------------------------
    // -------------- OPUNARYPLUSMINUS CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    class OpUnaryPlusMinusInteger : public Integer {
    public:
        OpUnaryPlusMinusInteger(
                std::shared_ptr<Integer> arg,
                char op);
        long value_integer() const override;
    private:
        const std::shared_ptr<Integer> arg;
        const char op;
    };

    // -------------------------------------------------------------------------
    // -------------- OPPLUSMINUS CLASES  --------------------------------------
    // -------------------------------------------------------------------------

    class OpPlusMinusInteger : public Integer {
    public:
        OpPlusMinusInteger(
                std::shared_ptr<Integer> first_arg,
                std::vector<std::shared_ptr<Integer>> other_argv,
                const std::vector<char>& opv);
        long value_integer() const override;
    private:
        const std::shared_ptr<Integer> first_arg;
        const std::vector<std::shared_ptr<Integer>> other_argv;
        const std::vector<char> opv;
    };

    // -------------------------------------------------------------------------
    // -------------- OPPRODDIV CLASES  ----------------------------------------
    // -------------------------------------------------------------------------    

    class OpProdDivInteger : public Integer {
    public:
        OpProdDivInteger(
                std::shared_ptr<Integer> first_arg,
                std::vector<std::shared_ptr<Integer>> other_argv,
                const std::vector<char>& opv);
        long value_integer() const override;
    private:
        const std::shared_ptr<Integer> first_arg;
        const std::vector<std::shared_ptr<Integer>> other_argv;
        const std::vector<char> opv;
    };

}

#endif