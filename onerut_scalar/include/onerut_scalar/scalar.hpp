#ifndef ONERUT_SCALAR_SCALAR
#define ONERUT_SCALAR_SCALAR

#include<cassert>// TODO remove  when funcion impl have their file.
#include<complex>
#include<memory>
#include<vector>

namespace onerut_scalar {

    // -------------------------------------------------------------------------
    // -------------- ABSTRACT BASE CLASES -------------------------------------
    // -------------------------------------------------------------------------

    class Complex {
    public:
        virtual std::complex<double> value_complex() const = 0;
        virtual ~Complex() = default;
    };

    class Real : public Complex {
    public:
        virtual double value_real() const = 0;
        virtual std::complex<double> value_complex() const override;
        virtual ~Real() = default;
    };

    class Integer : public Real {
    public:
        virtual long value_integer() const = 0;
        virtual double value_real() const override;
        virtual ~Integer() = default;
    };

    // -------------------------------------------------------------------------
    // -------------- CAST CLASES  ---------------------------------------------
    // -------------------------------------------------------------------------

    class CastIntegerToReal : public Real {
    public:
        CastIntegerToReal(std::shared_ptr<Integer> arg);
        double value_real() const override;
    private:
        const std::shared_ptr<Integer> arg;
    };

    // -------------------------------------------------------------------------
    // -------------- LITERAL CLASES  ------------------------------------------
    // -------------------------------------------------------------------------

    class LitComplex : public Complex {
    public:
        LitComplex(std::complex<double> value);
        std::complex<double> value_complex() const override;
        const std::complex<double> value;
    };

    class LitReal : public Real {
    public:
        LitReal(double value);
        double value_real() const override;
        const double value;
    };

    class LitInteger : public Integer {
    public:
        LitInteger(long value);
        long value_integer() const override;
        const long value;
    };

    // -------------------------------------------------------------------------
    // -------------- OPUNARYPLUSMINUS CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    class OpUnaryPlusMinusComplex : public Complex {
    public:
        OpUnaryPlusMinusComplex(
                std::shared_ptr<Complex> arg,
                char op);
        std::complex<double> value_complex() const override;
        const std::shared_ptr<Complex> arg;
        const char op;
    };

    class OpUnaryPlusMinusReal : public Real {
    public:
        OpUnaryPlusMinusReal(
                std::shared_ptr<Real> arg,
                char op);
        double value_real() const override;
        const std::shared_ptr<Real> arg;
        const char op;
    };

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

    class OpPlusMinusComplex : public Complex {
    public:
        OpPlusMinusComplex(
                std::shared_ptr<Complex> first_arg,
                std::vector<std::shared_ptr<Complex>> other_argv,
                const std::vector<char>& opv);
        std::complex<double> value_complex() const override;
    private:
        const std::shared_ptr<Complex> first_arg;
        const std::vector<std::shared_ptr<Complex>> other_argv;
        const std::vector<char> opv;
    };
    
    class OpPlusMinusReal : public Real {
    public:
        OpPlusMinusReal(
                std::shared_ptr<Real> first_arg,
                std::vector<std::shared_ptr<Real>> other_argv,
                const std::vector<char>& opv);
        double value_real() const override;
    private:
        const std::shared_ptr<Real> first_arg;
        const std::vector<std::shared_ptr<Real>> other_argv;
        const std::vector<char> opv;
    };

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

    class OpProdDivComplex : public Complex {
    public:
        OpProdDivComplex(
                std::shared_ptr<Complex> first_arg,
                std::vector<std::shared_ptr<Complex>> other_argv,
                const std::vector<char>& opv);
        std::complex<double> value_complex() const override;
    private:
        const std::shared_ptr<Complex> first_arg;
        const std::vector<std::shared_ptr<Complex>> other_argv;
        const std::vector<char> opv;
    };
    
    class OpProdDivReal : public Real {
    public:
        OpProdDivReal(
                std::shared_ptr<Real> first_arg,
                std::vector<std::shared_ptr<Real>> other_argv,
                const std::vector<char>& opv);
        double value_real() const override;
    private:
        const std::shared_ptr<Real> first_arg;
        const std::vector<std::shared_ptr<Real>> other_argv;
        const std::vector<char> opv;
    };

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

    // -------------------------------------------------------------------------
    // -------------- FUNCTION CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    template<typename Callable>
    class UnaryRealFunction : public Real {
    public:
        UnaryRealFunction(Callable callable, std::shared_ptr<Real> arg);
        double value_real() const override;
    private:
        Callable callable;
        const std::shared_ptr<Real> arg;
    };

    template<typename Callable>
    UnaryRealFunction<Callable>::UnaryRealFunction(Callable callable, std::shared_ptr<Real> arg) :
    callable(callable),
    arg(arg) {
        assert(arg);
    }

    template<typename Callable>
    double UnaryRealFunction<Callable>::value_real() const {
        const double x = arg->value_real();
        const double y = callable(x);
        return y;
    }

    // -------------------------------------------------------------------------

    template<typename Callable>
    class BinaryRealFunction : public Real {
    public:
        BinaryRealFunction(Callable callable, std::shared_ptr<Real> first_arg, std::shared_ptr<Real> second_arg);
        double value_real() const override;
    private:
        Callable callable;
        const std::shared_ptr<Real> first_arg;
        const std::shared_ptr<Real> second_arg;
    };

    template<typename Callable>
    BinaryRealFunction<Callable>::BinaryRealFunction(Callable callable, std::shared_ptr<Real> first_arg, std::shared_ptr<Real> second_arg) :
    callable(callable),
    first_arg(first_arg),
    second_arg(second_arg) {
        assert(first_arg);
        assert(second_arg);
    }

    template<typename Callable>
    double BinaryRealFunction<Callable>::value_real() const {
        const double firts_x = first_arg->value_real();
        const double second_x = second_arg->value_real();
        const double y = callable(firts_x, second_x);
        return y;
    }
}

#endif