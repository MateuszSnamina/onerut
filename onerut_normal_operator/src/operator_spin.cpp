#include<cassert>
#include<cmath>
#include<boost/cast.hpp>

#include<onerut_normal_operator/utility_spin.hpp>
#include<onerut_normal_operator/operator_spin.hpp>

namespace onerut_normal_operator {

    SpinZetOperator::SpinZetOperator(std::shared_ptr<const SpinDomain> domain) :
    domain(domain) {
        assert(domain);
    }

    std::shared_ptr<const Domain> SpinZetOperator::get_domain() const {
        return domain;
    }

    typename SpinZetOperator::AbstractIteratorPtrT
    SpinZetOperator::begin_itptr(const BraKetT& ket) const {
        const auto doubled_m = utility::_n_stars_to_doubled_m(domain->multiplicity, ket);
        const double value = boost::numeric_cast<double>(doubled_m) / 2;
        return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value, ket)));
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    SpinZetOperator::dependence() const {
        return {};
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
    SpinPlusOperator::begin_itptr(const BraKetT& ket) const {
        if (ket == 0) {
            return std::make_unique<IteratorT>(IteratorT::create_end_iterator());
        }
        const auto doubled_l = utility::_n_stars_to_doubled_m(domain->multiplicity, 0);
        const auto doubled_m = utility::_n_stars_to_doubled_m(domain->multiplicity, ket);
        const double temp = boost::numeric_cast<double>(doubled_l * (doubled_l + 2) - doubled_m * (doubled_m + 2));
        const double value = std::sqrt(temp / 4.0);
        return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value, ket - 1)));
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    SpinPlusOperator::dependence() const {
        return {};
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
    SpinMinusOperator::begin_itptr(const BraKetT& ket) const {
        if (ket == domain->multiplicity - 1) {
            return std::make_unique<IteratorT>(IteratorT::create_end_iterator());
        }
        const auto doubled_l = utility::_n_stars_to_doubled_m(domain->multiplicity, 0);
        const auto doubled_m = utility::_n_stars_to_doubled_m(domain->multiplicity, ket);
        const double temp = boost::numeric_cast<double>(doubled_l * (doubled_l + 2) - doubled_m * (doubled_m - 2));
        const double value = std::sqrt(temp / 4.0);
        return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value, ket + 1)));
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    SpinMinusOperator::dependence() const {
        return {};
    }

}

