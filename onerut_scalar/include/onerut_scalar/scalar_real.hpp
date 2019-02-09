#ifndef ONERUT_SCALAR_SCALAR_REAL
#define ONERUT_SCALAR_SCALAR_REAL

#include<memory>
#include<vector>

#include<onerut_scalar/scalar_abstract_real.hpp>

namespace onerut_scalar {

    // -------------------------------------------------------------------------
    // -------------- CAST CLASES  ---------------------------------------------
    // -------------------------------------------------------------------------

    //    class CastIntegerToReal : public Real {
    //    public:
    //        CastIntegerToReal(std::shared_ptr<Integer> arg);
    //        double value_real() const override;
    //    private:
    //        const std::shared_ptr<Integer> arg;
    //    };

    // -------------------------------------------------------------------------
    // -------------- LITERAL CLASES  ------------------------------------------
    // -------------------------------------------------------------------------

    class LitReal : public Real {
    public:
        LitReal(double value);
        double value_real() const override;
        const double value;
    };

    // -------------------------------------------------------------------------
    // -------------- OPUNARYPLUSMINUS CLASES  ---------------------------------
    // -------------------------------------------------------------------------

    class OpUnaryPlusMinusReal : public Real {
    public:
        OpUnaryPlusMinusReal(
                std::shared_ptr<Real> arg,
                char op);
        double value_real() const override;
        const std::shared_ptr<Real> arg;
        const char op;
    };

    // -------------------------------------------------------------------------
    // -------------- OPPLUSMINUS CLASES  --------------------------------------
    // -------------------------------------------------------------------------
    
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

    // -------------------------------------------------------------------------
    // -------------- OPPRODDIV CLASES  ----------------------------------------
    // -------------------------------------------------------------------------    
    
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

}

#endif