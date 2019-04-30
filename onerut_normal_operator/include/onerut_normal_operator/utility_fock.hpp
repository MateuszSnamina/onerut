#ifndef ONERUT_NORMAL_OPERATOR_UTILITY_FOCK
#define ONERUT_NORMAL_OPERATOR_UTILITY_FOCK

#include<cassert>
#include<cstdint>
#include<string>
#include<vector>
#include<iostream>//debug TODO delete

namespace onerut_normal_operator::utility {

    inline
    uint32_t binomial_coefficient(uint32_t n, uint32_t k) {
        //std::cout << "(" << n << "over" << k << ")" << std::endl;
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

    inline
    std::string vector_of_bool_to_string(const std::vector<bool>& buffer) {
        std::string resut;
        const uint32_t size = boost::numeric_cast<uint32_t>(buffer.size());
        resut.resize(size);
        for (uint32_t i = 0; i < size; ++i) {
            resut[i] = buffer[i] ? '+' : '.';
        }
        return resut;
    }

    inline
    void _encode(
            std::vector<bool>& buffer, uint32_t index_to_fill,
            uint32_t n_particles_left, uint32_t ket) {
        //std::cout << "CALL index_to_fill=" << index_to_fill << ", n_particles_left= " << n_particles_left << ", ket= " << ket << std::endl;
        const uint32_t n_orbitals = buffer.size();
        const uint32_t n_orbitals_left = n_orbitals - index_to_fill;
        assert(n_orbitals_left > 0);
        if (index_to_fill == buffer.size()) {
            assert(0);
            return;
        }
        const uint32_t lower_chonk_size =
                n_orbitals_left > n_particles_left ?
                binomial_coefficient(n_orbitals_left - 1, n_particles_left) :
                0;
        const uint32_t upper_chonk_size = binomial_coefficient(n_orbitals_left - 1, n_particles_left - 1);
        assert(ket < lower_chonk_size + upper_chonk_size);
        if (ket < lower_chonk_size) {
            buffer[index_to_fill] = false;
            _encode(buffer, index_to_fill + 1, n_particles_left, ket);
        } else {
            buffer[index_to_fill] = true;
            if (n_particles_left > 1) {
                _encode(buffer, index_to_fill + 1, n_particles_left - 1, ket - lower_chonk_size);
            }
        }
    }

    inline
    std::vector<bool> encode(uint32_t n_particles, uint32_t n_orbitals, uint32_t ket) {
        assert(n_particles > 0);
        assert(ket < binomial_coefficient(n_orbitals, n_particles));
        std::vector<bool> result(n_orbitals);
        _encode(result, 0, n_particles, ket);
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