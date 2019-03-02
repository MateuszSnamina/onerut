#include<cassert>
#include<cmath>
#include<string>

#include<onerut_normal_operator/operator_oscillator.hpp>

/*
namespace {
    // TODO : delete
    std::vector<std::string>
    _generate_state_names(unsigned n_max_stars) {
        std::vector<std::string> names;
        names.reserve(n_max_stars);
        for (unsigned i = 0; i < n_max_stars; ++i) {
            const std::string name = "nu_" + std::to_string(i);
            names.push_back(name);
        }
        return names;
    }
}
 */

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

    // -------------------------------------------------------------------------

    CreationOperator::CreationOperator(std::shared_ptr<const OscillatorDomain> domain) :
    domain(domain) {
        assert(domain);
    }

    std::shared_ptr<const Domain> CreationOperator::get_domain() const {
        return domain;
    }

    typename CreationOperator::AbstractIteratorPtrT
    CreationOperator::begin_itptr(const unsigned& ket) const {
        const double coef = std::sqrt(ket + 1);
        return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(coef, ket + 1)));
    }

    // -------------------------------------------------------------------------

    AnihilationOperator::AnihilationOperator(std::shared_ptr<const OscillatorDomain> domain) :
    domain(domain) {
        assert(domain);
    }

    std::shared_ptr<const Domain> AnihilationOperator::get_domain() const {
        return domain;
    }

    typename AnihilationOperator::AbstractIteratorPtrT
    AnihilationOperator::begin_itptr(const unsigned& ket) const {
        if (ket >= 1) {
            const double coef = std::sqrt(ket);
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(coef, ket - 1)));
        }
        return std::make_unique<IteratorT>(IteratorT::create_end_iterator());
    }


}

