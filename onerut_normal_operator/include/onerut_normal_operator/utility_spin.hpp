#ifndef ONERUT_NORMAL_OPERATOR_UTILITY_SPIN
#define ONERUT_NORMAL_OPERATOR_UTILITY_SPIN

#include<cassert>
#include<boost/cast.hpp>

namespace onerut_normal_operator::utility {

    inline
    int _n_stars_to_doubled_m(uint32_t multiplicity, uint32_t n_stars) {
        assert(multiplicity > 0);
        const uint32_t doubled_l = multiplicity - 1;
        const int32_t doubled_m = boost::numeric_cast<int32_t>(doubled_l) - 2 * boost::numeric_cast<int32_t>(n_stars);
        return doubled_m;
    }

}

#endif