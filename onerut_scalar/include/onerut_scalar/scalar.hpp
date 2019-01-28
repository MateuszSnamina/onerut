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

    class Long : public Double {
    public:
        virtual long value_long() const = 0;
        virtual double value_double() const override;
        virtual ~Long() = default;
    };

    // -------------------------------------------------------------------------
    // -------------- CAST CLASES  ---------------------------------------------
    // -------------------------------------------------------------------------

    class CastLongToDouble : public Double {
    public:
        CastLongToDouble(std::shared_ptr<Long> arg);
        double value_double() const override;
    private:
        const std::shared_ptr<Long> arg;
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

    class LitLong : public Long {
    public:
        LitLong(long value);
        long value_long() const override;
        const long value;
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

    class OpUnaryPlusMinusLong : public Long {
    public:
        OpUnaryPlusMinusLong(
                std::shared_ptr<Long> arg,
                char32_t op);
        long value_long() const override;
    private:
        const std::shared_ptr<Long> arg;
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
    private:
        const std::shared_ptr<Double> first_arg;
        const std::vector<std::shared_ptr<Double>> other_argv;
        const std::vector<char32_t> opv;
    };

    class OpPlusMinusLong : public Long {
    public:
        OpPlusMinusLong(
                std::shared_ptr<Long> first_arg,
                std::vector<std::shared_ptr<Long>> other_argv,
                const std::vector<char32_t>& opv);
        long value_long() const override;
    private:
        const std::shared_ptr<Long> first_arg;
        const std::vector<std::shared_ptr<Long>> other_argv;
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
    private:
        const std::shared_ptr<Double> first_arg;
        const std::vector<std::shared_ptr<Double>> other_argv;
        const std::vector<char32_t> opv;
    };

    class OpProdDivLong : public Long {
    public:
        OpProdDivLong(
                std::shared_ptr<Long> first_arg,
                std::vector<std::shared_ptr<Long>> other_argv,
                const std::vector<char32_t>& opv);
        long value_long() const override;
    private:
        const std::shared_ptr<Long> first_arg;
        const std::vector<std::shared_ptr<Long>> other_argv;
        const std::vector<char32_t> opv;
    };

}

#endif