#ifndef ONERUT_NORMAL_OPERATOR_UTILITY_FOCK
#define ONERUT_NORMAL_OPERATOR_UTILITY_FOCK

#include<cassert>
#include<cstdint>
#include<string>
#include<vector>
#include<algorithm>
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
        const uint32_t n_orbitals = boost::numeric_cast<uint32_t>(buffer.size());
        resut.resize(boost::numeric_cast<std::size_t>(n_orbitals));
        for (uint32_t i = 0; i < n_orbitals; ++i) {
            resut[i] = buffer[i] ? '+' : '.';
        }
        return resut;
    }

    inline
    std::vector<bool> decode(const uint32_t n_particles, const uint32_t n_orbitals, uint32_t ket) {
        assert(n_particles > 0);
        assert(ket < binomial_coefficient(n_orbitals, n_particles));
        std::vector<bool> result(n_orbitals);
        uint32_t n_particles_left = n_particles;
        for (uint32_t orbital_index_to_fill = 0; orbital_index_to_fill < n_orbitals; ++orbital_index_to_fill) {
            assert(n_particles_left > 0);
            const uint32_t n_orbitals_left = n_orbitals - orbital_index_to_fill;
            const uint32_t lower_chonk_size =
                    n_orbitals_left > n_particles_left ?
                    binomial_coefficient(n_orbitals_left - 1, n_particles_left) :
                    0;
            const uint32_t upper_chonk_size = binomial_coefficient(n_orbitals_left - 1, n_particles_left - 1);
            assert(ket < lower_chonk_size + upper_chonk_size);
            const bool is_in_upper_chunk = (ket >= lower_chonk_size);
            result[orbital_index_to_fill] = is_in_upper_chunk;
            if (is_in_upper_chunk) {
                n_particles_left--;
                ket -= lower_chonk_size;
                if (n_particles_left == 0) {
                    break;
                }
            }
        }
        assert(ket == 0);
        assert(n_particles_left == 0);
        assert(n_particles == std::count(begin(result), end(result), true));
        return result;
    }

    inline
    uint32_t encode(const std::vector<bool>& decoded, const uint32_t n_particles) {
        assert(n_particles > 0);
        assert(n_particles == std::count(begin(decoded), end(decoded), true));
        uint32_t ket = 0;
        const uint32_t n_orbitals = boost::numeric_cast<uint32_t>(decoded.size());
        uint32_t n_particles_left = n_particles;
        for (uint32_t orbital_processed = 0; orbital_processed < n_orbitals; ++orbital_processed) {
            if (decoded[orbital_processed]) {
                const uint32_t n_orbitals_left = n_orbitals - orbital_processed;
                const uint32_t lower_chonk_size =
                        n_orbitals_left > n_particles_left ?
                        binomial_coefficient(n_orbitals_left - 1, n_particles_left) :
                        0;
                ket += lower_chonk_size;
                n_particles_left--;
            }
        }
        assert(n_particles_left == 0);
        assert(ket < binomial_coefficient(n_orbitals, n_particles));
        return ket;
    }

}

#endif