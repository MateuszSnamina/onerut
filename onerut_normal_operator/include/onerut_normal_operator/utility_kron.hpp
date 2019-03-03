#ifndef ONERUT_NORMAL_OPERATOR_UTILITY_KRON
#define ONERUT_NORMAL_OPERATOR_UTILITY_KRON

#include<cassert>
#include<cstdint>
#include<vector>

namespace onerut_normal_operator::utility {

    inline
    uint32_t _get_site_intex(
            uint32_t my_weight,
            uint32_t next_weight,
            uint32_t ket) {
        return (ket % next_weight) / my_weight;
    }

    inline
    uint32_t _get_site_intex(
            const std::vector<uint32_t>& weights,
            uint32_t place,
            uint32_t ket) {
        assert(place < weights.size() - 1);
        return _get_site_intex(weights[place + 1], weights[place], ket);
    }

}

#endif