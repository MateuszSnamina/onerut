#ifndef ONERUT_NORMAL_OPERATOR_OPERATOR_FOCK
#define ONERUT_NORMAL_OPERATOR_OPERATOR_FOCK

#include<type_traits>

#include<onerut_scalar/scalar_abstract_real.hpp>
#include<onerut_typed_operator/iterator_simple.hpp>
#include<onerut_normal_operator/operator_abstract.hpp>
#include<onerut_normal_operator/domain_fock.hpp>

namespace onerut_normal_operator {

    /*
     * Operator for:
     * cr_i an_j + h.c = cr_i an_j + cr_j an_i 
     * 
     * 
     */
    class FockHopOperator : public AbstractOperator<double> {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        FockHopOperator(
                std::shared_ptr<const onerut_scalar::Real> value,
                std::shared_ptr<const OrbitalIndex> orbital_index_1,
                std::shared_ptr<const OrbitalIndex> orbital_index_2);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const final;
        std::shared_ptr<const Domain> get_domain() const final;
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependence() const final;
    public:
        const std::shared_ptr<const onerut_scalar::Real> value;
        const std::shared_ptr<const OrbitalIndex> orbital_index_1;
        const std::shared_ptr<const OrbitalIndex> orbital_index_2;
    };

    class FockParticleNumberOperator : public AbstractOperator<double> {
    public:
        using ScalarT = double;
        using BraKetT = uint32_t;
        using AbstractOpT = AbstractOperator<ScalarT>;
        using AbstractOpPtrT = std::shared_ptr<const AbstractOpT>;
        using AbstractIteratorT = onerut_typed_operator::AbstractResultIterator<ScalarT, BraKetT>;
        using AbstractIteratorPtrT = std::unique_ptr<AbstractIteratorT>;
        using IteratorT = onerut_typed_operator::SimpleOperatorIterator<ScalarT, BraKetT>;
        static_assert(std::is_base_of<AbstractIteratorT, IteratorT>::value);
        FockParticleNumberOperator(
                std::shared_ptr<const onerut_scalar::Real> value,
                std::shared_ptr<const OrbitalIndex> orbital_index);
        AbstractIteratorPtrT begin_itptr(const BraKetT& ket) const final;
        std::shared_ptr<const Domain> get_domain() const final;
        std::vector<std::weak_ptr<const onerut_dependence::Dependable>> dependence() const final;
    public:
        const std::shared_ptr<const onerut_scalar::Real> value;
        const std::shared_ptr<const OrbitalIndex> orbital_index;
    };

}

#endif