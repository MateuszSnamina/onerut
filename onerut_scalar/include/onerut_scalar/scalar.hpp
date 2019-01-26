#ifndef ONERUT_SCALAR_SCALAR
#define ONERUT_SCALAR_SCALAR

namespace onerut_scalar {

    class Double {
    public:
        virtual double value_double() const = 0;
        virtual ~Double() = default;
    };

    class Int : public Double {
    public:
        virtual double value_double() const override;
        virtual int value_int() const = 0;
        virtual ~Int() = default;
    };

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

}

#endif