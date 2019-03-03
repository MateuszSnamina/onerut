#ifndef ONERUT_NORMAL_OPERATOR_UTILITY_KRON
#define ONERUT_NORMAL_OPERATOR_UTILITY_KRON

#include<cassert>
#include<vector>

namespace onerut_normal_operator::utility {

    inline
    unsigned _get_site_intex(
            unsigned my_weight,
            unsigned next_weight,
            unsigned ket) {
        return (ket % next_weight) / my_weight;
    }

    inline
    unsigned _get_site_intex(
            const std::vector<unsigned>& weights,
            unsigned place,
            unsigned ket) {
        assert(place < weights.size() - 1);
        return _get_site_intex(weights[place + 1], weights[place], ket);
    }

}

#endif