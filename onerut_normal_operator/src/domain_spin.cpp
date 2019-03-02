#include<cassert>
#include<string>
#include<boost/cast.hpp>

#include<onerut_normal_operator/domain_spin.hpp>

namespace {

    std::string _doubled_halfs_to_string(int doubled_halfs) {
        if (doubled_halfs % 2 == 0)
            return std::to_string(doubled_halfs / 2);
        return std::to_string(doubled_halfs) + "/2";
    }

    int _n_stars_to_doubled_m(unsigned multiplicity, unsigned n_stars) {
        assert(multiplicity > 0);
        const unsigned doubled_l = multiplicity - 1;
        const int doubled_m = boost::numeric_cast<int>(doubled_l) - 2 * boost::numeric_cast<int>(n_stars);
        return doubled_m;
    }

}

namespace onerut_normal_operator {

    SpinDomain::SpinDomain(unsigned multiplicity) :
    multiplicity(multiplicity),
    n_max_stars(multiplicity) {
    }

    unsigned SpinDomain::size() const {
        return n_max_stars;
    }

    std::string SpinDomain::state_name(unsigned index) const {
        const auto & n_stars = index;
        const std::string name =
                _doubled_halfs_to_string(_n_stars_to_doubled_m(multiplicity, 0)) +
                "," +
                _doubled_halfs_to_string(_n_stars_to_doubled_m(multiplicity, n_stars));
        return name;
    }

}

