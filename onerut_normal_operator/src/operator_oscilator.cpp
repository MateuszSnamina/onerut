#include<cassert>
#include<cmath>

#include<onerut_normal_operator/operator_oscilator.hpp>

namespace {

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

namespace onerut_normal_operator {

    OscilatorDomain::OscilatorDomain(unsigned n_max_stars) :
    Domain(_generate_state_names(n_max_stars)) {
    }

    // -------------------------------------------------------------------------

    CreationOperator::CreationOperator(std::shared_ptr<const OscilatorDomain> domain) :
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

    AnihilationOperator::AnihilationOperator(std::shared_ptr<const OscilatorDomain> domain) :
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

