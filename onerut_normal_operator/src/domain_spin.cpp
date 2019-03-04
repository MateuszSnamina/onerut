#include<cassert>
#include<cmath>
#include<boost/cast.hpp>

#include<onerut_normal_operator/utility_spin.hpp>
#include<onerut_normal_operator/domain_spin.hpp>

namespace {

    std::string signed_to_string(int32_t arg) {
        std::string sign = (arg > 0 ? "+" : (arg < 0 ? "-" : " "));
        return sign + std::to_string(std::abs(arg));
    }

    std::string _doubled_halfs_to_string_doublet(int32_t doubled_halfs) {
        return (doubled_halfs > 0 ? "UUp" : "DDown");
    }

    std::string _doubled_halfs_to_string(int32_t doubled_halfs) {
        if (doubled_halfs % 2 == 0)
            return signed_to_string(doubled_halfs / 2);
        return signed_to_string(doubled_halfs) + "/2";
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
        assert(index < size());
        const auto & n_stars = index;
        if (multiplicity == 2) {
            return _doubled_halfs_to_string_doublet(utility::_n_stars_to_doubled_m(multiplicity, n_stars));
        }
        const std::string name =
                //_doubled_halfs_to_string(utility::_n_stars_to_doubled_m(multiplicity, 0)) +
                //"," +
                _doubled_halfs_to_string(utility::_n_stars_to_doubled_m(multiplicity, n_stars));
        return name;
    }

}

