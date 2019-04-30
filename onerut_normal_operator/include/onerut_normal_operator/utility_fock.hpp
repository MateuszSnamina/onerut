#ifndef ONERUT_NORMAL_OPERATOR_UTILITY_FOCK
#define ONERUT_NORMAL_OPERATOR_UTILITY_FOCK

#include<cassert>
#include<cstdint>
#include<vector>
//#include<onerut_normal_operator/domain_fock.hpp>

namespace {

    //    inline
    //    uint32_t _get_sub_index(
    //            uint32_t my_weight,
    //            uint32_t next_weight,
    //            uint32_t index) {
    //        return (index % next_weight) / my_weight;
    //    }

}

namespace onerut_normal_operator::utility {

    uint32_t binomial_coefficient(uint32_t n, uint32_t k) {
        assert(n >= k);
        uint32_t result = 1;
        for (uint32_t i = 0; i < n - k; ++i) {
            result *= n - i;
        };
        for (uint32_t i = 0; i < n - k; ++i) {
            result /= i + 1;
        };
        // TODO: use boost :) ...
        return result;
    }

    //    
    //    inline
    //    uint32_t get_sub_index(
    //            const KronDomain& domain,
    //            uint32_t place,
    //            uint32_t index) {
    //        assert(place < domain.subdomains.size());
    //        return _get_sub_index(domain.get_place_weight(place), domain.get_next_place_weight(place), index);
    //    }

}

#endif