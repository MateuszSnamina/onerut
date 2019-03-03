#include<cassert>
#include<boost/cast.hpp>

#include<onerut_normal_operator/utility_spin.hpp>
#include<onerut_normal_operator/domain_spin.hpp>

namespace {

    std::string _doubled_halfs_to_string(int doubled_halfs) {
        if (doubled_halfs % 2 == 0)
            return std::to_string(doubled_halfs / 2);
        return std::to_string(doubled_halfs) + "/2";
    }

}

namespace onerut_normal_operator {

    SpinDomain::SpinDomain(uint32_t multiplicity) :
    multiplicity(multiplicity),
    n_max_stars(multiplicity) {
    }

    uint32_t SpinDomain::size() const {
        return n_max_stars;
    }

    std::string SpinDomain::state_name(uint32_t index) const {
        assert(index <= size());
        const auto & n_stars = index;
        const std::string name =
                _doubled_halfs_to_string(utility::_n_stars_to_doubled_m(multiplicity, 0)) +
                "," +
                _doubled_halfs_to_string(utility::_n_stars_to_doubled_m(multiplicity, n_stars));
        return name;
    }

}

