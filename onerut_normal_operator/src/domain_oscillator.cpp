#include<cassert>

#include<onerut_normal_operator/domain_oscillator.hpp>

namespace onerut_normal_operator {

    OscillatorDomain::OscillatorDomain(uint32_t n_max_stars) :
    n_max_stars(n_max_stars) {
    }

    uint32_t OscillatorDomain::size() const {
        return n_max_stars;
    }

    std::string OscillatorDomain::state_name(uint32_t index) const {
        assert(index < size());
        const auto & n_stars = index;
        const std::string name = "nu_" + std::to_string(n_stars);
        return name;
    }

}

