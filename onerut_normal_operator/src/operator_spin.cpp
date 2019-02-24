#include<cassert>
#include<cmath>
#include<string>
#include<boost/cast.hpp>

#include<onerut_normal_operator/operator_spin.hpp>

namespace {

    int _n_stars_to_doubled_m(unsigned multiplicity, unsigned n_stars) {
        return boost::numeric_cast<int>(multiplicity) - 1 - 2 * boost::numeric_cast<int>(n_stars);
    }

    std::string _doubled_halfs_to_string(int doubled_halfs) {
        if (doubled_halfs % 2 == 0)
            return std::to_string(doubled_halfs / 2);
        return std::to_string(doubled_halfs) + "/2";
    }

    int _n_stats_to_doubled_m(unsigned multiplicity, unsigned n_stars) {
        assert(multiplicity > 0);
        const unsigned doubled_l = multiplicity - 1;
        const int doubled_m = boost::numeric_cast<int>(doubled_l) - 2 * boost::numeric_cast<int>(n_stars);
        return doubled_m;
    }

    std::vector<std::string>
    _generate_state_names(unsigned multiplicity, unsigned n_max_stars) {
        std::vector<std::string> names;
        names.reserve(multiplicity);
        for (unsigned n_stars = 0; n_stars < n_max_stars; ++n_stars) {
            const std::string name =
                    _doubled_halfs_to_string(_n_stars_to_doubled_m(multiplicity, 0)) +
                    "," +
                    _doubled_halfs_to_string(_n_stars_to_doubled_m(multiplicity, n_stars));
            names.push_back(name);
        }
        return names;
    }

}

namespace onerut_normal_operator {

    SpinDomain::SpinDomain(unsigned multiplicity) :
    Domain(_generate_state_names(multiplicity, multiplicity)),
    multiplicity(multiplicity),
    n_max_stars(multiplicity) {
    }

    // -------------------------------------------------------------------------

    SpinZetOperator::SpinZetOperator(std::shared_ptr<const SpinDomain> domain) :
    domain(domain) {
        assert(domain);
    }

    std::shared_ptr<const Domain> SpinZetOperator::get_domain() const {
        return domain;
    }

    typename SpinZetOperator::AbstractIteratorPtrT
    SpinZetOperator::begin_itptr(const unsigned& ket) const {
        const int doubled_m = _n_stars_to_doubled_m(domain->multiplicity, ket);
        const double value = boost::numeric_cast<double>(doubled_m) / 2;
        return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value, ket)));
    }
    // -------------------------------------------------------------------------

    SpinPlusOperator::SpinPlusOperator(std::shared_ptr<const SpinDomain> domain) :
    domain(domain) {
        assert(domain);
    }

    std::shared_ptr<const Domain> SpinPlusOperator::get_domain() const {
        return domain;
    }

    typename SpinPlusOperator::AbstractIteratorPtrT
    SpinPlusOperator::begin_itptr(const unsigned& ket) const {
        assert(0); //TODO implement it.
        /*        
                const double coef = std::sqrt(ket + 1);
                return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(coef, ket + 1)));
         */
    }

    // -------------------------------------------------------------------------

    SpinMinusOperator::SpinMinusOperator(std::shared_ptr<const SpinDomain> domain) :
    domain(domain) {
        assert(domain);
    }

    std::shared_ptr<const Domain> SpinMinusOperator::get_domain() const {
        return domain;
    }

    typename SpinMinusOperator::AbstractIteratorPtrT
    SpinMinusOperator::begin_itptr(const unsigned& ket) const {
        assert(0); //TODO implement it.
        /*
        if (ket >= 1) {
            const double coef = std::sqrt(ket);
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(coef, ket - 1)));
        }
        return std::make_unique<IteratorT>(IteratorT::create_end_iterator());
         */
    }

}

