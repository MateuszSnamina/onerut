#ifndef ONERUT_NORMAL_OPERATOR_UTILITY_KRON
#define ONERUT_NORMAL_OPERATOR_UTILITY_KRON

#include<cassert>
#include<cstdint>
#include<vector>
#include<onerut_normal_operator/domain_kron.hpp>

namespace {

    inline
    uint32_t _get_sub_index(
            uint32_t my_weight,
            uint32_t next_weight,
            uint32_t index) {
        return (index % next_weight) / my_weight;
    }
    
}

namespace onerut_normal_operator::utility {
    
    inline
    uint32_t get_sub_index(
            const KronDomain& domain,
            uint32_t place,
            uint32_t index) {
        assert(place < domain.sub_domains.size());
        return _get_sub_index(domain.get_place_weight(place), domain.get_next_place_weight(place), index);
    }

}

#endif