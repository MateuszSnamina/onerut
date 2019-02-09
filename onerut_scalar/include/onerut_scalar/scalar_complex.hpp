#ifndef ONERUT_SCALAR_SCALAR_COMPLEX
#define ONERUT_SCALAR_SCALAR_COMPLEX

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


    // -------------------------------------------------------------------------
    // -------------- LITERAL CLASES  ------------------------------------------
    // -------------------------------------------------------------------------

    class LitComplex : public Complex {
    public:
        LitComplex(std::complex<double> value);
        std::complex<double> value_complex() const override;
        const std::complex<double> value;
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


}

#endif