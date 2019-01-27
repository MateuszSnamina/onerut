#ifndef ONERUT_SCALAR_SCALAR
#define ONERUT_SCALAR_SCALAR

#include<memory>
#include<vector>

namespace onerut_scalar {

    // -------------------------------------------------------------------------
    // -------------- ABSTRACT BASE CLASES -------------------------------------
    // -------------------------------------------------------------------------

    class Double {
    public:
        virtual double value_double() const = 0;
        virtual ~Double() = default;
    };

    class Int : public Double {
    public:
        virtual int value_int() const = 0;
        virtual double value_double() const override;
        virtual ~Int() = default;
    };

    // -------------------------------------------------------------------------
    // -------------- LITERAL CLASES  ------------------------------------------
    // -------------------------------------------------------------------------

    class LitDouble : public Double {
    public:
        LitDouble(double value);
        double value_double() const override;
        const double value;
    };

    class LitInt : public Int {
    public:
        LitInt(int value);
        int value_int() const override;
        const int value;

    };

    // -------------------------------------------------------------------------
    // -------------- OPUNARYPLUSMINUS CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    class OpUnaryPlusMinusDouble : public Double {
    public:
        OpUnaryPlusMinusDouble(
                std::shared_ptr<Double> arg,
                char32_t op);
        double value_double() const override;
        const std::shared_ptr<Double> arg;
        const char32_t op;
    };

    class OpUnaryPlusMinusInt : public Int {
    public:
        OpUnaryPlusMinusInt(
                std::shared_ptr<Int> arg,
                char32_t op);
        int value_int() const override;
        const std::shared_ptr<Int> arg;
        const char32_t op;
    };

    // -------------------------------------------------------------------------
    // -------------- OPPLUSMINUS CLASES  --------------------------------------
    // -------------------------------------------------------------------------

    class OpPlusMinusDouble : public Double {
    public:
        OpPlusMinusDouble(
                std::shared_ptr<Double> first_arg,
                std::vector<std::shared_ptr<Double>> other_argv,
                const std::vector<char32_t>& opv);
        double value_double() const override;
        const std::shared_ptr<Double> first_arg;
        const std::vector<std::shared_ptr<Double>> other_argv;
        const std::vector<char32_t> opv;
    };

    class OpPlusMinusInt : public Int {
    public:
        OpPlusMinusInt(
                std::shared_ptr<Int> first_arg,
                std::vector<std::shared_ptr<Int>> other_argv,
                const std::vector<char32_t>& opv);
        int value_int() const override;
        const std::shared_ptr<Int> first_arg;
        const std::vector<std::shared_ptr<Int>> other_argv;
        const std::vector<char32_t> opv;
    };

    // -------------------------------------------------------------------------
    // -------------- OPPRODDIV CLASES  ----------------------------------------
    // -------------------------------------------------------------------------    

    class OpProdDivDouble : public Double {
    public:
        OpProdDivDouble(
                std::shared_ptr<Double> first_arg,
                std::vector<std::shared_ptr<Double>> other_argv,
                const std::vector<char32_t>& opv);
        double value_double() const override;
        const std::shared_ptr<Double> first_arg;
        const std::vector<std::shared_ptr<Double>> other_argv;
        const std::vector<char32_t> opv;
    };

    class OpProdDivInt : public Int {
    public:
        OpProdDivInt(
                std::shared_ptr<Int> first_arg,
                std::vector<std::shared_ptr<Int>> other_argv,
                const std::vector<char32_t>& opv);
        int value_int() const override;
        const std::shared_ptr<Int> first_arg;
        const std::vector<std::shared_ptr<Int>> other_argv;
        const std::vector<char32_t> opv;
    };

}

#endif