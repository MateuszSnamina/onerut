#include<cassert>

#include<onerut_normal_operator/utility_fock.hpp>
#include<onerut_normal_operator/operator_fock.hpp>

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
            // TODO a symm (-1) factor
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(/*value->value_real()*/ 666.0, bra)));
        } else if
            // Act as: cr_orbital_index_2 * an_orbital_index_1:
            (decoded[orbital_index_1->index] &&
                !decoded[orbital_index_2->index]) {
            auto decoded_cr2_an1 = decoded;
            decoded[orbital_index_1->index] = false;
            decoded[orbital_index_2->index] = true;
            const unsigned bra = utility::encode(decoded, n_particles);
            // TODO a symm (-1) factor
            return std::make_unique<IteratorT>(IteratorT::create_the_one_valid_iterator(std::make_pair(/*value->value_real()*/ 666.0, bra)));
        }
        return std::make_unique<IteratorT>(IteratorT::create_end_iterator());
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

}