#include<onerut_scalar/scalar.hpp>

//------------------------------------------------------------------------------

double Int::value_double() const {
    return static_cast<double> (value_int());
    // TODO: numeric_cast!!
}

//------------------------------------------------------------------------------

LitDouble::LitDouble(double value) :
value(value) {
}

double LitDouble::value_double() const {
    return value;
}

//------------------------------------------------------------------------------

LitInt::LitInt(int value) :
value(value) {
}

int LitInt::value_int() const {
    return value;
}

//------------------------------------------------------------------------------
