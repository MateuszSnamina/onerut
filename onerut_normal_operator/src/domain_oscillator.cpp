#include<cassert>
#include<string>

#include<onerut_normal_operator/domain_oscillator.hpp>

namespace onerut_normal_operator {

    OscillatorDomain::OscillatorDomain(unsigned n_max_stars) :
    n_max_stars(n_max_stars) {
    }

    unsigned OscillatorDomain::size() const {
        return n_max_stars;
    }

    std::string OscillatorDomain::state_name(unsigned index) const {
        const auto & n_stars = index;
        const std::string name = "nu_" + std::to_string(n_stars);
        return name;
    }

}

