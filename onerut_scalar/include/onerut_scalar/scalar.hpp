#ifndef ONERUT_SCALAR_SCALAR
#define ONERUT_SCALAR_SCALAR

#include<cassert>// TODO : remove when templates will have its onw file
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
                char op);
        double value_double() const override;
        const std::shared_ptr<Double> arg;
        const char op;
    };

    class OpUnaryPlusMinusLong : public Long {
    public:
        OpUnaryPlusMinusLong(
                std::shared_ptr<Long> arg,
                char op);
        long value_long() const override;
    private:
        const std::shared_ptr<Long> arg;
        const char op;
    };

    // -------------------------------------------------------------------------
    // -------------- OPPLUSMINUS CLASES  --------------------------------------
    // -------------------------------------------------------------------------

    class OpPlusMinusDouble : public Double {
    public:
        OpPlusMinusDouble(
                std::shared_ptr<Double> first_arg,
                std::vector<std::shared_ptr<Double>> other_argv,
                const std::vector<char>& opv);
        double value_double() const override;
    private:
        const std::shared_ptr<Double> first_arg;
        const std::vector<std::shared_ptr<Double>> other_argv;
        const std::vector<char> opv;
    };

    class OpPlusMinusLong : public Long {
    public:
        OpPlusMinusLong(
                std::shared_ptr<Long> first_arg,
                std::vector<std::shared_ptr<Long>> other_argv,
                const std::vector<char>& opv);
        long value_long() const override;
    private:
        const std::shared_ptr<Long> first_arg;
        const std::vector<std::shared_ptr<Long>> other_argv;
        const std::vector<char> opv;
    };

    // -------------------------------------------------------------------------
    // -------------- OPPRODDIV CLASES  ----------------------------------------
    // -------------------------------------------------------------------------    

    class OpProdDivDouble : public Double {
    public:
        OpProdDivDouble(
                std::shared_ptr<Double> first_arg,
                std::vector<std::shared_ptr<Double>> other_argv,
                const std::vector<char>& opv);
        double value_double() const override;
    private:
        const std::shared_ptr<Double> first_arg;
        const std::vector<std::shared_ptr<Double>> other_argv;
        const std::vector<char> opv;
    };

    class OpProdDivLong : public Long {
    public:
        OpProdDivLong(
                std::shared_ptr<Long> first_arg,
                std::vector<std::shared_ptr<Long>> other_argv,
                const std::vector<char>& opv);
        long value_long() const override;
    private:
        const std::shared_ptr<Long> first_arg;
        const std::vector<std::shared_ptr<Long>> other_argv;
        const std::vector<char> opv;
    };

    // -------------------------------------------------------------------------
    // -------------- FUNCTION CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    template<typename Callable>
    class UnaryDoubleFunction : public Double {
    public:
        UnaryDoubleFunction(Callable callable, std::shared_ptr<Double> arg);
        double value_double() const override;
    private:
        Callable callable;
        const std::shared_ptr<Double> arg;
    };

    template<typename Callable>
    UnaryDoubleFunction<Callable>::UnaryDoubleFunction(Callable callable, std::shared_ptr<Double> arg) :
    callable(callable),
    arg(arg) {
        assert(arg);
    }

    template<typename Callable>
    double UnaryDoubleFunction<Callable>::value_double() const {
        const double x = arg->value_double();
        const double y = callable(x);
        return y;
    }

    // -------------------------------------------------------------------------

    template<typename Callable>
    class BinaryDoubleFunction : public Double {
    public:
        BinaryDoubleFunction(Callable callable, std::shared_ptr<Double> first_arg, std::shared_ptr<Double> second_arg);
        double value_double() const override;
    private:
        Callable callable;
        const std::shared_ptr<Double> first_arg;
        const std::shared_ptr<Double> second_arg;
    };

    template<typename Callable>
    BinaryDoubleFunction<Callable>::BinaryDoubleFunction(Callable callable, std::shared_ptr<Double> first_arg, std::shared_ptr<Double> second_arg) :
    callable(callable),    
    first_arg(first_arg),
    second_arg(second_arg) {
        assert(first_arg);
        assert(second_arg);
    }

    template<typename Callable>
    double BinaryDoubleFunction<Callable>::value_double() const {
        const double firts_x = first_arg->value_double();
        const double second_x = second_arg->value_double();
        const double y = callable(firts_x, second_x);
        return y;
    }
}

#endif