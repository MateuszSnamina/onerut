#include<cassert>
#include<onerut_normal_operator/utility_fock.hpp>
#include<onerut_normal_operator/operator_fock.hpp>

namespace {

    bool _symm_factor(const std::vector<bool> decoded, uint32_t index_lo, uint32_t index_up) {
        const auto symm_factor_power = std::count(
                begin(decoded) + index_lo + 1,
                begin(decoded) + index_up,
                true
                );
        return symm_factor_power % 2 == 0;
        // true: no change the coef sign, false: change the coef sign
    }

    bool symm_factor(const std::vector<bool> decoded, uint32_t index_1, uint32_t index_2) {
        assert(index_1 != index_2);
        if (index_1 < index_2) {
            return _symm_factor(decoded, index_1, index_2);
        }
        return _symm_factor(decoded, index_2, index_1);
    }
}

namespace onerut_normal_operator {

    FockHopOperator::FockHopOperator(
            std::shared_ptr<const onerut_scalar::Real> value,
            std::shared_ptr<const OrbitalIndex> orbital_index_1,
            std::shared_ptr<const OrbitalIndex> orbital_index_2
            ) :
    value(value),
    orbital_index_1(orbital_index_1),
    orbital_index_2(orbital_index_2) {
        assert(value);
        assert(orbital_index_1);
        assert(orbital_index_2);
        assert(are_the_same_domains(*orbital_index_1->domain, *orbital_index_2->domain));
        assert(orbital_index_1->index != orbital_index_2->index);
    }

    std::shared_ptr<const Domain>
    FockHopOperator::get_domain() const {
        return orbital_index_1->domain;
    }

    typename FockHopOperator::AbstractIteratorPtrT
    FockHopOperator::begin_itptr(const BraKetT& ket) const {
        // Basic properties:
        const auto& n_particles = orbital_index_1->domain->n_particles;
        const auto& orbital_names = orbital_index_1->domain->orbital_names;
        const auto n_orbitals = boost::numeric_cast<uint32_t>(orbital_names.size());
        auto decoded = utility::decode(n_particles, n_orbitals, ket);
        assert(orbital_index_2->index < n_orbitals);
        assert(orbital_index_1->index < n_orbitals);
        assert(orbital_index_1->index != orbital_index_2->index);
        if (decoded[orbital_index_2->index] &&
                !decoded[orbital_index_1->index]) {
            // Act as: cr_orbital_index_1 * an_orbital_index_2:            
            auto decoded_cr1_an2 = decoded;
            decoded[orbital_index_2->index] = false;
            decoded[orbital_index_1->index] = true;
            const unsigned bra = utility::encode(decoded, n_particles);
            const auto coef =
                    symm_factor(decoded, orbital_index_1->index, orbital_index_2->index) ?
                    +value->value_real() :
                    -value->value_real();
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(coef, bra)));
        } else if
            // Act as: cr_orbital_index_2 * an_orbital_index_1:
            (decoded[orbital_index_1->index] &&
                !decoded[orbital_index_2->index]) {
            auto decoded_cr2_an1 = decoded;
            decoded[orbital_index_1->index] = false;
            decoded[orbital_index_2->index] = true;
            const unsigned bra = utility::encode(decoded, n_particles);
            const auto coef =
                    symm_factor(decoded, orbital_index_1->index, orbital_index_2->index) ?
                    +value->value_real() :
                    -value->value_real();
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(coef, bra)));
        }
        return std::make_unique<IteratorT>(IteratorT::create_end_iterator());
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    FockHopOperator::dependence() const {
        return {value};
    }

    // -------------------------------------------------------------------------

    FockParticleNumberOperator::FockParticleNumberOperator(
            std::shared_ptr<const onerut_scalar::Real> value,
            std::shared_ptr<const OrbitalIndex> orbital_index) :
    value(value),
    orbital_index(orbital_index) {
        assert(value);
        assert(orbital_index);
    }

    std::shared_ptr<const Domain>
    FockParticleNumberOperator::get_domain() const {
        return orbital_index->domain;
    }

    typename FockParticleNumberOperator::AbstractIteratorPtrT
    FockParticleNumberOperator::begin_itptr(const BraKetT& ket) const {
        const auto& n_particles = orbital_index->domain->n_particles;
        const auto& orbital_names = orbital_index->domain->orbital_names;
        const auto n_orbitals = boost::numeric_cast<uint32_t>(orbital_names.size());
        auto decoded = utility::decode(n_particles, n_orbitals, ket);
        if (decoded[orbital_index->index]) {
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(value->value_real(), ket)));
        }
        return std::make_unique<IteratorT>(IteratorT::create_end_iterator());
    }

    std::vector<std::weak_ptr<const onerut_dependence::Dependable>>
    FockParticleNumberOperator::dependence() const {
        return {value};
    }

}