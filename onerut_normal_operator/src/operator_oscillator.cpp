#include<cassert>
#include<cmath>

#include<onerut_normal_operator/operator_oscillator.hpp>

namespace onerut_normal_operator {

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

